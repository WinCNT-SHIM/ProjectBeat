#include "D2DEngine.h"
#include "ResourceManager.h"
#include "EngineCamera.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\Output\\Debug\\Resource.lib")
#else
#pragma comment(lib, "..\\Output\\Release\\Resource.lib")
#endif // DEBUG

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

D2DEngine::D2DEngine(HWND  hWnd) :
    // 윈도우 핸들
    m_hwnd(hWnd),
    // 장치 독립 자원(팩토리 등) 관련
    m_pD2DFactory(NULL),
    m_pWICFactory(NULL),
    m_pDWriteFactory(NULL),
    // 장치 종속 자원(렌더 타겟 등) 관련
    is_DDR_OK(S_OK),
    m_pRenderTarget(NULL),
    m_pTextFormat(NULL),
    m_pTmpTxtFormat(NULL),
    m_pPathGeometry(NULL),
    m_pLinearGradientBrush(NULL),
    // 브러시 관련
    m_pBlackBrush(NULL),
    m_pRedBrush(NULL),
    m_pYellowBrush(NULL),
    m_pTmpBrush(NULL),
    m_pNowBrush(NULL),
    m_pGridPatternBitmapBrush(NULL),
    // 비트맵 관련
    m_pBitmap(NULL),
    m_pAnotherBitmap(NULL),
    m_ResourceManager(NULL),
    m_pEngineCamera(NULL)
{
    m_RenderTargetSize.width = 0;
    m_RenderTargetSize.height = 0;
}

D2DEngine::~D2DEngine()
{
    if (m_pEngineCamera != nullptr)
    {
        delete m_pEngineCamera;
        m_pEngineCamera = nullptr;
    }
    SafeRelease(&m_pD2DFactory);
    SafeRelease(&m_pWICFactory);
    SafeRelease(&m_pDWriteFactory);
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pTextFormat);
    SafeRelease(&m_pPathGeometry);
    SafeRelease(&m_pLinearGradientBrush);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pGridPatternBitmapBrush);
    SafeRelease(&m_pBitmap);
    SafeRelease(&m_pAnotherBitmap);
}

/// <summary>
/// 장치 의존적 리소스를 초기화함
/// </summary>
/// <returns></returns>
HRESULT D2DEngine::Initialize()
{
    // Initializes the COM library on the current thread and identifies the concurrency model as single-thread apartment (STA).
    // (??) COM 라이브러리를 초기화한다
    // 뭔지는 모르겠지만 일단 넣어보자
    HRESULT _hResult = CoInitialize(NULL);
    //CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    HRESULT hr;
    // Direct2D factory와 같은 device-indpendent resources를 초기화한다
    hr = CreateDeviceIndependentResources();

    // render target과 같은 device resources를 초기화한다
    if (SUCCEEDED(hr))
    {
        is_DDR_OK = CreateDeviceResources();
        hr = is_DDR_OK;
    }

    // 리소스 매니저를 초기화함
    // 기본적으로  meta json file들을 읽어와 파싱하고 관리하기 위한 객체
    // 스프라이트 시트의 직접적인 로드/관리도 담당한다
	if (SUCCEEDED(hr))
	{
		m_ResourceManager = ResourceManager::Instance();
		m_ResourceManager->Initialize(m_pRenderTarget, m_pWICFactory);
	}

    // 엔진 카메라를 초기화한다
    if (SUCCEEDED(hr))
    {
        m_pEngineCamera = new EngineCamera(0, 0, m_RenderTargetSize.width, m_RenderTargetSize.height);
    }

    return hr;
}

/// <summary>
/// 어떠한 장치에도 바인딩 되지 않은 리소스를 만든다
/// (수명은 프로그램이 돌아갈 동안 효과적으로 연장됨)
/// 리소스에는 다음이 포함된다
/// D2D, DirectWrite, WIC factories, Direct2D geometry
/// DirectWrite, Text Format object(글꼴 특성을 식별하는데 사용)
/// 즉, CPU의 메모리(RAM)에 저장되는 도형이나 텍스트 리소스들을
/// 장치 독립적 리소스라고 한다
/// </summary>
/// <returns></returns>
HRESULT D2DEngine::CreateDeviceIndependentResources()
{
    try
    {
        static const WCHAR msc_fontName[] = _T("Verdana");
        static const FLOAT msc_fontSize = 50;
        HRESULT hr;

        // ID2D1Factory 인터페이스로 만들어진 객체를 얻는다
        // ID2D1Factory: Direct2D에서 사용하는 리소스를 생성할 수 있는 인터페이스를 제공한다
        // ID2D1Factory는 D2D의 핵심적인 인터페이스이다
        // 아래의 함수는 ID2D1Factory의 객체를 생성하는 함수
        // (인수 riid, *pFactoryOptions가 생략된 형태임)
        hr = D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,  // [in] 싱글 스레드 용
            &m_pD2DFactory                      // [out] ID2D1Factory
        );
        if (SUCCEEDED(hr) == false) throw _T("Factory 생성 실패!");

        // WIC 팩토리(이미지를 다루기 위한 팩토리)를 생성한다
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IWICImagingFactory,
            reinterpret_cast<void**>(&m_pWICFactory)
        );
        if (SUCCEEDED(hr) == false) throw _T("WIC 팩토리 생성 실패!");

        // DirectWrite 팩토리의 오브젝트를 생성한다
        // DirectWrite: 글꼴 처리에 사용되는 마이크로소프트사의 API
        // DirectX의 컴포넌트의 1개로, GDI/GDI+의 후속인 문자 그리기용 API이다
        // Create a DirectWrite factory.
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pDWriteFactory),
            reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
        );
        if (SUCCEEDED(hr) == false) throw _T("Direct Factory 생성 실패!");

        // Text Format 객체를 생성한다
        // => Text Format란 DirectWrite를 이용해 텍스트를 렌더링할 때
        //    필요한 정보들(폰트, 사이즈 정렬 방식 등)을 담고 있는 구조체이다
        hr = m_pDWriteFactory->CreateTextFormat(
            msc_fontName,
            nullptr,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            msc_fontSize,
            _T(""), // (??) 로케일
            &m_pTextFormat
        );
        if (SUCCEEDED(hr) == false) throw _T("TextFormat 생성 실패!");

        // Text Format에서 텍스트 정렬 방식을 설정해준다
        // 텍스트를 렌더링하는 레이아웃 박스의 좌우 정렬을 설정
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        // 텍스트를 렌더링하는 레이아웃 박스의 상하 정렬을 설정
        m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

        return hr;
    }
    catch (const TCHAR* str)
    {
        Assert(!str);
    }
}

/// <summary>
/// 특정 D3D 장치에 바인딩된 리소스를 만듭니다
/// (??) 장치 의존적 리소스란 무슨 뜻일까
/// => 그래픽카드의 메모리에 저장되는 브러시나 렌더타겟 등을
///    장치 의존적 리소스라고 한다
/// </summary>
/// <returns></returns>
HRESULT D2DEngine::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    // RenderAll Target이 없으면 만들어 준다
    if (!m_pRenderTarget)
    {
        // 윈도우의 크기를 구함
        RECT rc;
        GetClientRect(m_hwnd, &rc);
        // (??) 윈도우의 픽셀 사이즈를 얻는 처리??
        D2D1_SIZE_U size = D2D1::SizeU(
            static_cast<UINT>(rc.right - rc.left),
            static_cast<UINT>(rc.bottom - rc.top)
        );

        // RenderAll Target: Factory 객체로 생성한 리소스(이미지 등)를 그릴 대상
        // CreateHwndRenderTarget(): RenderAll Target을 윈도우의 핸들(HWND)로(?) 생성하는 함수
        // 그 외에도 ID2D1BitmapRenderTarget - 비트맵, ID2D1DCRenderTarget - HDC 등이 있다
        // 자세한 설정은 아래 참조
        // https://pang2h.tistory.com/345
        hr = m_pD2DFactory->CreateHwndRenderTarget(
            // 다음과 같은 렌더링에 필요한 정보들이 있는 구조체
            //   픽셀의 색상 형식 및 알파 모드 정보, 렌더링 대상의 렌더링 형식(소프트웨어/하드웨어),
            //   렌더링 대상의 GDI 호환여부, 하드웨어 렌더링에 필요한 Direct3D 버전의 지정, DPI 설정
            // RenderTargetProperties()는 기본값을 반환하는 함수
            D2D1::RenderTargetProperties(),
            // 윈도우 핸들을 포함해 그리기 영역의 크기, 그리기 모드를 담고 있는 구조체
            D2D1::HwndRenderTargetProperties(m_hwnd,size),
            // [out] 함수의 결과로 생성된 Hwnd RenderAll Target을 포인터를 주소로 반환
            &m_pRenderTarget
        );

        if (SUCCEEDED(hr))
        {
            // 브러시를 얻는 처리
            // 검은색
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Black),
                &m_pBlackBrush
            );
            // 빨간색
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Red),
                &m_pRedBrush
            );
            // 노란색
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Yellow),
                &m_pYellowBrush
            );
        }
    }
    else
    {
        m_RenderTargetSize = m_pRenderTarget->GetSize();
    }
    return hr;
}

/// <summary>
/// 브러시의 색상을 설정하는 함수
/// </summary>
void D2DEngine::SetBrushColor(float r, float g, float b, float a)
{
    SafeRelease(&m_pNowBrush);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(r, g, b, a)), &m_pNowBrush);
}

void D2DEngine::SetBrushColor(COLORREF fontColor)
{
    SafeRelease(&m_pNowBrush);
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(fontColor)), &m_pNowBrush);
}

void D2DEngine::SetFontSize(float fontSize)
{
    HRESULT hr = S_OK;

    if (m_pDWriteFactory != nullptr)
    {
        // Create a DirectWrite text format object.
        hr = m_pDWriteFactory->CreateTextFormat(
            L"굴림",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            fontSize,
            L"", //locale
            &m_pTmpTxtFormat
        );
    }
    // Text Format에서 텍스트 정렬 방식을 설정해준다
    if (SUCCEEDED(hr))
    {
        // 텍스트를 렌더링하는 레이아웃 박스의 좌우 정렬을 설정
        m_pTmpTxtFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        // 텍스트를 렌더링하는 레이아웃 박스의 상하 정렬을 설정
        m_pTmpTxtFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    }
}

/// <summary>
/// 원을 그리는 함수(Primitive)
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="radius"></param>
/// <param name="color"></param>
void D2DEngine::DrawCircle(float x, float y, float radius, COLORREF color, bool isFill)
{
    D2D1_ELLIPSE tmp;
    tmp.point.x = x;
    tmp.point.y = y;
    tmp.radiusX = radius;
    tmp.radiusY = radius;

    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(color)), &m_pTmpBrush);
    if (m_pTmpBrush != nullptr)
    {
        // 채우기 있음
        if (isFill == true) m_pRenderTarget->FillEllipse(tmp, m_pTmpBrush);
        // 채우기 없음
        else m_pRenderTarget->DrawEllipse(tmp, m_pTmpBrush);
    }
}

void D2DEngine::DrawRectangle(float x1, float y1, float x2, float y2, COLORREF color, bool isFill)
{
    D2D1_RECT_F tmp;
    tmp.left = x1;
    tmp.top = y1;
    tmp.right = x2;
    tmp.bottom = y2;
    
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(color)), &m_pTmpBrush);
    if (m_pTmpBrush != nullptr)
    {
        // 채우기 있음
        if (isFill == true) m_pRenderTarget->FillRectangle(tmp, m_pTmpBrush);
        // 채우기 없음
        else m_pRenderTarget->DrawRectangle(tmp, m_pTmpBrush);
    }
}

/// <summary>
/// 직선 그리기 함수
/// </summary>
/// <param name="x1">시작점 x좌표</param>
/// <param name="y1">시작점 y좌표</param>
/// <param name="x2">종료점 x좌표</param>
/// <param name="y2">종료점 y좌표</param>
/// <param name="color">색상</param>
void D2DEngine::DrawLine(float x1, float y1, float x2, float y2, COLORREF color)
{
    D2D1_POINT_2F point1;
    point1.x = x1;
    point1.y = y1;
    D2D1_POINT_2F point2;
    point2.x = x2;
    point2.y = y2;

    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(color)), &m_pTmpBrush);
    if (m_pTmpBrush == nullptr)
    {
        m_pRenderTarget->DrawLine(point1, point2, m_pNowBrush);
    }
    else
    {
        m_pRenderTarget->DrawLine(point1, point2, m_pTmpBrush);
    }
}

void D2DEngine::DrawString(float x1, float y1, float x2, float y2, std::string str, float fontSize, int vertical, int horizontal, COLORREF fontColor)
{
	m_RenderTargetSize = m_pRenderTarget->GetSize();
	m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(fontColor)), &m_pTmpBrush);

	SetFontSize(fontSize);
	SetBrushColor(fontColor);

	// string을 출력하는 처리(유니코드 버전)
	// 해당 처리를 안 하면 한글은 깨진다
	// http://www.dreamy.pe.kr/zbxe/CodeClip/5961
	const char* txtBuffer = str.c_str();
	BSTR bstr;
	// 유니코드로 변환하기에 앞서 먼저 문자열의 길이를 알아야 한다
	int nLen = MultiByteToWideChar(CP_ACP, 0, txtBuffer, strlen(txtBuffer), NULL, NULL);
	// 얻어낸 길이만큼 메모리를 할당한다.
	bstr = SysAllocStringLen(NULL, nLen);
	// 이제 변환을 수행한다
	MultiByteToWideChar(CP_ACP, 0, txtBuffer, strlen(txtBuffer), bstr, nLen);
	SetTransform(IdentityMtrix);

	m_pTmpTxtFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)vertical);
	m_pTmpTxtFormat->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)horizontal);
	if (bstr != nullptr)
	{
		// DrawText: IDWriteTextFormat 객체의 형식 정보로 텍스트를 그리는 함수
		m_pRenderTarget->DrawText(
			bstr,                   // [in] 그릴 문자열
			wcslen(bstr),           // 문자열의 길이
			m_pTmpTxtFormat,          // [in] 텍스트의 세부 서식 정보
			// 문자열을 그릴 위치
			D2D1::RectF(x1, y1, x2, y2),
			m_pTmpBrush             // 텍스트에 적용할 브러시
		);
	}

	// 필요없어진  BSTR를 제거한다
	SysFreeString(bstr);

	// (??) 문자 출력 후 텍스트 버퍼의 메모리를 해제하려고 했지만
	// delete를 하면 에러가 발생한다(잘못된 메모리 접근 같은...) 이유는 아직 모르겠다
	// delete txtBuffer;
}

void D2DEngine::DrawString(float x1, float y1, std::string str, float fontSize, COLORREF fontColor)
{
    m_RenderTargetSize = m_pRenderTarget->GetSize();
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(fontColor)), &m_pTmpBrush);

    SetFontSize(fontSize);
    SetBrushColor(fontColor);

    // string을 출력하는 처리(유니코드 버전)
    // 해당 처리를 안 하면 한글은 깨진다
    // http://www.dreamy.pe.kr/zbxe/CodeClip/5961
    const char* txtBuffer = str.c_str();
    BSTR bstr;
    // 유니코드로 변환하기에 앞서 먼저 문자열의 길이를 알아야 한다
    int nLen = MultiByteToWideChar(CP_ACP, 0, txtBuffer, strlen(txtBuffer), NULL, NULL);
    // 얻어낸 길이만큼 메모리를 할당한다.
    bstr = SysAllocStringLen(NULL, nLen);
    // 이제 변환을 수행한다
    MultiByteToWideChar(CP_ACP, 0, txtBuffer, strlen(txtBuffer), bstr, nLen);
    SetTransform(IdentityMtrix);

    if (bstr != nullptr)
    {
        // DrawText: IDWriteTextFormat 객체의 형식 정보로 텍스트를 그리는 함수
        m_pRenderTarget->DrawText(
            bstr,                   // [in] 그릴 문자열
            wcslen(bstr),           // 문자열의 길이
            m_pTmpTxtFormat,          // [in] 텍스트의 세부 서식 정보
            // 문자열을 그릴 위치
            D2D1::RectF(x1, y1, m_RenderTargetSize.width, m_RenderTargetSize.height),
            m_pTmpBrush             // 텍스트에 적용할 브러시
        );
    }

    // 필요없어진  BSTR를 제거한다
    SysFreeString(bstr);

    // (??) 문자 출력 후 텍스트 버퍼의 메모리를 해제하려고 했지만
    // delete를 하면 에러가 발생한다(잘못된 메모리 접근 같은...) 이유는 아직 모르겠다
    // delete txtBuffer;
}

void D2DEngine::SetTransform(D2D1_MATRIX_3X2_F matrix)
{
    // 카메라 행렬을 적용
    matrix = matrix * m_pEngineCamera->GetCameraTM();
    m_pRenderTarget->SetTransform(matrix);
}

/// <summary>
/// Direct3D 장치를 잃었을 때 다시 생성할 필요가 있는
/// 장치 의존 리소스들을 제거하는 함수
/// </summary>
void D2DEngine::DiscardDeviceResources()
{
    // 장치 종속 자원(렌더 타겟 등) 관련
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pPathGeometry);
    // 브러시 관련
    SafeRelease(&m_pLinearGradientBrush);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pRedBrush);
    SafeRelease(&m_pYellowBrush);
    SafeRelease(&m_pTmpBrush);
    SafeRelease(&m_pNowBrush);
    SafeRelease(&m_pGridPatternBitmapBrush);
    // 비트맵 관련
    SafeRelease(&m_pBitmap);
    SafeRelease(&m_pAnotherBitmap);
}

void D2DEngine::BeginRender()
{
    // 장치 종족 자원들에 문제가 없고, 윈도우에 렌더링 가능한 상태일 때
    if (SUCCEEDED(is_DDR_OK)
        && !(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
    {
        // 렌더 타겟의 사이즈를 획득
        m_RenderTargetSize = m_pRenderTarget->GetSize();
        // RenderTarget에 그리기 처리 시작
        m_pRenderTarget->BeginDraw();
        // 렌더링 전에 변환을 초기화
        m_pRenderTarget->SetTransform(IdentityMtrix);
        // 렌더 타겟의 배경색을 초기화
        m_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
    }
    else
    {
        CreateDeviceResources();
    }
    
}

void D2DEngine::EndRender()
{
    if (SUCCEEDED(is_DDR_OK)
        && !(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
    {
        HRESULT hr = m_pRenderTarget->EndDraw();

        // 렌더 타겟의 자원을 복구해야 할 경우
        if (hr == D2DERR_RECREATE_TARGET)
        {
            hr = S_OK;
            DiscardDeviceResources();
        }
    }
}

void D2DEngine::DrawSprite(ISprite* _sprite, RECT _RenderingArea, float alpha)
{
    if (_sprite != nullptr)
    {
        D2DSprite* _tmp = dynamic_cast<D2DSprite*>(_sprite);

        // 인덱스 접근 실패 체크
        ID2D1Bitmap* _sheet = m_ResourceManager->GetImage(_tmp->m_SheetIndex);
        if (_sheet != nullptr && _tmp != _tmp)
        {
            // 렌더링 작업을 할 영역을 설정
            D2D1_RECT_F _D2DRenderingArea;
            _D2DRenderingArea.left = (FLOAT)_RenderingArea.left;
            _D2DRenderingArea.top = (FLOAT)_RenderingArea.top;
            _D2DRenderingArea.right = (FLOAT)_RenderingArea.right;
            _D2DRenderingArea.bottom = (FLOAT)_RenderingArea.bottom;

            m_pRenderTarget->DrawBitmap(
                _sheet,
                // 렌더링 작업을 할 화면의 영역
                _D2DRenderingArea,
                // 투명도
                alpha,
                // 이미지의 조정 시의 알고리즘: 렌더링 픽셀에 가장 가까운 4개의 비트맵 픽셀로 색상 보간
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                // 그릴 스프라이트의 스프라이트 시트에서의 범위(해당 범위만 그림)
                D2D1::RectF(
                    (float)_sprite->CenterPosX,
                    (float)_sprite->CenterPosY,
                    (float)(_sprite->CenterPosX + _sprite->Width),
                    (float)(_sprite->CenterPosY + _sprite->Height)
                )
            );
        }
    }
}

void D2DEngine::DrawSprite(int _SheetIndex, float _OriX, float _OriY, float _SpriteWidth, float _SpriteHeight, float _Width, float _Height, float _FillX /*= 1.0f*/, float _FillY /*= 1.0f*/, float alpha)
{
    ID2D1Bitmap* _sheet = nullptr;
    _sheet = m_ResourceManager->GetImage(_SheetIndex);
    // 스프라이트 체크
    if (_sheet == nullptr)
    {
        return;
    }

    if (_FillX < 0) _FillX = 0;
    if (_FillX > 1) _FillX = 1;
    if (_FillY < 0) _FillY = 0;
    if (_FillY > 1) _FillY = 1;

    m_pRenderTarget->DrawBitmap(
        _sheet,
        // 렌더링 작업을 할 화면의 영역은 설정 안 함(트랜스폼으로 지정)
        //D2D1::RectF(-_Width, -_Height, _Width * _Fill, _Height * _Fill),
        D2D1::RectF(-_Width, -_Height, -_Width + (2 * _Width * _FillX), -_Height + (2 * _Height * _FillY)),
        // 투명도
        alpha,
        // 이미지의 조정 시의 알고리즘: 렌더링 픽셀에 가장 가까운 4개의 비트맵 픽셀로 색상 보간
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        // 그릴 스프라이트의 스프라이트 시트에서의 범위(해당 범위만 그림)
        D2D1::RectF(
            (float)_OriX, (float)_OriY,
            (float)_OriX + (_SpriteWidth * _FillX), (float)(_OriY + _SpriteHeight * _FillY)
        )
    );

}

void D2DEngine::DrawSpriteR(int _SheetIndex, float _OriX, float _OriY, float _SpriteWidth, float _SpriteHeight, float _left, float _top, float _right, float _bottom, float _FillX, float _FillY, float alpha)
{
	ID2D1Bitmap* _sheet = nullptr;
	_sheet = m_ResourceManager->GetImage(_SheetIndex);
	// 스프라이트 체크
	if (_sheet == nullptr)
	{
		return;
	}

	if (_FillX < 0) _FillX = 0;
	if (_FillX > 1) _FillX = 1;
	if (_FillY < 0) _FillY = 0;
	if (_FillY > 1) _FillY = 1;

	m_pRenderTarget->DrawBitmap(
		_sheet,
		// 렌더링 작업을 할 화면의 영역은 설정 안 함(트랜스폼으로 지정)
		//D2D1::RectF(-_Width, -_Height, _Width * _Fill, _Height * _Fill),
		D2D1::RectF(_left, _top, _left + (_right - _left) * _FillX, _top + (_bottom - _top) * _FillY),
		// 투명도
		alpha,
		// 이미지의 조정 시의 알고리즘: 렌더링 픽셀에 가장 가까운 4개의 비트맵 픽셀로 색상 보간
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		// 그릴 스프라이트의 스프라이트 시트에서의 범위(해당 범위만 그림)
		D2D1::RectF(
		(float)_OriX, (float)_OriY,
		(float)_OriX + (_SpriteWidth * _FillX), (float)(_OriY + _SpriteHeight * _FillY)
	)
	);
}

void D2DEngine::SetEngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY, float _ZoomX /*= 1*/, float _ZoomY /*= 1*/, float _RotX /*= 1*/, float _RotY /*= 0*/)
{
    m_pEngineCamera->SetEngineCamera(_PosX, _PosY, _SizeX, _SizeY, _ZoomX, _ZoomY, _RotX, _RotY);
    // 카메라는 오브젝트 매니저에 0번(m_Layer도 0)으로 넣을것.
    // 이번 프레임에 적용될 카메라를 설정한다
    // 엔진 카메라를 설정하지 않았을 경우,
    // 월드 좌표를 그대로 출력하도록 한다
    m_pEngineCamera->MakeEngineCameraTM();

}

//아직 쓰는곳 없음
wchar_t* D2DEngine::ConvertCStoWCS(const char* orig)
{
    // newsize describes the length of the
    // wchar_t string called wcstring in terms of the number
    // of wide characters, not the number of bytes.
    size_t newsize = strlen(orig) + 1;

    // The following creates a buffer large enough to contain
    // the exact number of characters in the original string
    // in the new format. If you want to add more characters
    // to the end of the string, increase the value of newsize
    // to increase the size of the buffer.
    wchar_t* wcstring = new wchar_t[newsize];

    // Convert char* string to a wchar_t* string.
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wcstring, newsize, orig, _TRUNCATE);

    return wcstring;
}
