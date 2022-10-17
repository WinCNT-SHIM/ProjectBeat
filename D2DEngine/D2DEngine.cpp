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
    // ������ �ڵ�
    m_hwnd(hWnd),
    // ��ġ ���� �ڿ�(���丮 ��) ����
    m_pD2DFactory(NULL),
    m_pWICFactory(NULL),
    m_pDWriteFactory(NULL),
    // ��ġ ���� �ڿ�(���� Ÿ�� ��) ����
    is_DDR_OK(S_OK),
    m_pRenderTarget(NULL),
    m_pTextFormat(NULL),
    m_pTmpTxtFormat(NULL),
    m_pPathGeometry(NULL),
    m_pLinearGradientBrush(NULL),
    // �귯�� ����
    m_pBlackBrush(NULL),
    m_pRedBrush(NULL),
    m_pYellowBrush(NULL),
    m_pTmpBrush(NULL),
    m_pNowBrush(NULL),
    m_pGridPatternBitmapBrush(NULL),
    // ��Ʈ�� ����
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
/// ��ġ ������ ���ҽ��� �ʱ�ȭ��
/// </summary>
/// <returns></returns>
HRESULT D2DEngine::Initialize()
{
    // Initializes the COM library on the current thread and identifies the concurrency model as single-thread apartment (STA).
    // (??) COM ���̺귯���� �ʱ�ȭ�Ѵ�
    // ������ �𸣰����� �ϴ� �־��
    HRESULT _hResult = CoInitialize(NULL);
    //CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    HRESULT hr;
    // Direct2D factory�� ���� device-indpendent resources�� �ʱ�ȭ�Ѵ�
    hr = CreateDeviceIndependentResources();

    // render target�� ���� device resources�� �ʱ�ȭ�Ѵ�
    if (SUCCEEDED(hr))
    {
        is_DDR_OK = CreateDeviceResources();
        hr = is_DDR_OK;
    }

    // ���ҽ� �Ŵ����� �ʱ�ȭ��
    // �⺻������  meta json file���� �о�� �Ľ��ϰ� �����ϱ� ���� ��ü
    // ��������Ʈ ��Ʈ�� �������� �ε�/������ ����Ѵ�
	if (SUCCEEDED(hr))
	{
		m_ResourceManager = ResourceManager::Instance();
		m_ResourceManager->Initialize(m_pRenderTarget, m_pWICFactory);
	}

    // ���� ī�޶� �ʱ�ȭ�Ѵ�
    if (SUCCEEDED(hr))
    {
        m_pEngineCamera = new EngineCamera(0, 0, m_RenderTargetSize.width, m_RenderTargetSize.height);
    }

    return hr;
}

/// <summary>
/// ��� ��ġ���� ���ε� ���� ���� ���ҽ��� �����
/// (������ ���α׷��� ���ư� ���� ȿ�������� �����)
/// ���ҽ����� ������ ���Եȴ�
/// D2D, DirectWrite, WIC factories, Direct2D geometry
/// DirectWrite, Text Format object(�۲� Ư���� �ĺ��ϴµ� ���)
/// ��, CPU�� �޸�(RAM)�� ����Ǵ� �����̳� �ؽ�Ʈ ���ҽ�����
/// ��ġ ������ ���ҽ���� �Ѵ�
/// </summary>
/// <returns></returns>
HRESULT D2DEngine::CreateDeviceIndependentResources()
{
    try
    {
        static const WCHAR msc_fontName[] = _T("Verdana");
        static const FLOAT msc_fontSize = 50;
        HRESULT hr;

        // ID2D1Factory �������̽��� ������� ��ü�� ��´�
        // ID2D1Factory: Direct2D���� ����ϴ� ���ҽ��� ������ �� �ִ� �������̽��� �����Ѵ�
        // ID2D1Factory�� D2D�� �ٽ����� �������̽��̴�
        // �Ʒ��� �Լ��� ID2D1Factory�� ��ü�� �����ϴ� �Լ�
        // (�μ� riid, *pFactoryOptions�� ������ ������)
        hr = D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,  // [in] �̱� ������ ��
            &m_pD2DFactory                      // [out] ID2D1Factory
        );
        if (SUCCEEDED(hr) == false) throw _T("Factory ���� ����!");

        // WIC ���丮(�̹����� �ٷ�� ���� ���丮)�� �����Ѵ�
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_IWICImagingFactory,
            reinterpret_cast<void**>(&m_pWICFactory)
        );
        if (SUCCEEDED(hr) == false) throw _T("WIC ���丮 ���� ����!");

        // DirectWrite ���丮�� ������Ʈ�� �����Ѵ�
        // DirectWrite: �۲� ó���� ���Ǵ� ����ũ�μ���Ʈ���� API
        // DirectX�� ������Ʈ�� 1����, GDI/GDI+�� �ļ��� ���� �׸���� API�̴�
        // Create a DirectWrite factory.
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pDWriteFactory),
            reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
        );
        if (SUCCEEDED(hr) == false) throw _T("Direct Factory ���� ����!");

        // Text Format ��ü�� �����Ѵ�
        // => Text Format�� DirectWrite�� �̿��� �ؽ�Ʈ�� �������� ��
        //    �ʿ��� ������(��Ʈ, ������ ���� ��� ��)�� ��� �ִ� ����ü�̴�
        hr = m_pDWriteFactory->CreateTextFormat(
            msc_fontName,
            nullptr,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            msc_fontSize,
            _T(""), // (??) ������
            &m_pTextFormat
        );
        if (SUCCEEDED(hr) == false) throw _T("TextFormat ���� ����!");

        // Text Format���� �ؽ�Ʈ ���� ����� �������ش�
        // �ؽ�Ʈ�� �������ϴ� ���̾ƿ� �ڽ��� �¿� ������ ����
        m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
        // �ؽ�Ʈ�� �������ϴ� ���̾ƿ� �ڽ��� ���� ������ ����
        m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

        return hr;
    }
    catch (const TCHAR* str)
    {
        Assert(!str);
    }
}

/// <summary>
/// Ư�� D3D ��ġ�� ���ε��� ���ҽ��� ����ϴ�
/// (??) ��ġ ������ ���ҽ��� ���� ���ϱ�
/// => �׷���ī���� �޸𸮿� ����Ǵ� �귯�ó� ����Ÿ�� ����
///    ��ġ ������ ���ҽ���� �Ѵ�
/// </summary>
/// <returns></returns>
HRESULT D2DEngine::CreateDeviceResources()
{
    HRESULT hr = S_OK;

    // RenderAll Target�� ������ ����� �ش�
    if (!m_pRenderTarget)
    {
        // �������� ũ�⸦ ����
        RECT rc;
        GetClientRect(m_hwnd, &rc);
        // (??) �������� �ȼ� ����� ��� ó��??
        D2D1_SIZE_U size = D2D1::SizeU(
            static_cast<UINT>(rc.right - rc.left),
            static_cast<UINT>(rc.bottom - rc.top)
        );

        // RenderAll Target: Factory ��ü�� ������ ���ҽ�(�̹��� ��)�� �׸� ���
        // CreateHwndRenderTarget(): RenderAll Target�� �������� �ڵ�(HWND)��(?) �����ϴ� �Լ�
        // �� �ܿ��� ID2D1BitmapRenderTarget - ��Ʈ��, ID2D1DCRenderTarget - HDC ���� �ִ�
        // �ڼ��� ������ �Ʒ� ����
        // https://pang2h.tistory.com/345
        hr = m_pD2DFactory->CreateHwndRenderTarget(
            // ������ ���� �������� �ʿ��� �������� �ִ� ����ü
            //   �ȼ��� ���� ���� �� ���� ��� ����, ������ ����� ������ ����(����Ʈ����/�ϵ����),
            //   ������ ����� GDI ȣȯ����, �ϵ���� �������� �ʿ��� Direct3D ������ ����, DPI ����
            // RenderTargetProperties()�� �⺻���� ��ȯ�ϴ� �Լ�
            D2D1::RenderTargetProperties(),
            // ������ �ڵ��� ������ �׸��� ������ ũ��, �׸��� ��带 ��� �ִ� ����ü
            D2D1::HwndRenderTargetProperties(m_hwnd,size),
            // [out] �Լ��� ����� ������ Hwnd RenderAll Target�� �����͸� �ּҷ� ��ȯ
            &m_pRenderTarget
        );

        if (SUCCEEDED(hr))
        {
            // �귯�ø� ��� ó��
            // ������
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Black),
                &m_pBlackBrush
            );
            // ������
            hr = m_pRenderTarget->CreateSolidColorBrush(
                D2D1::ColorF(D2D1::ColorF::Red),
                &m_pRedBrush
            );
            // �����
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
/// �귯���� ������ �����ϴ� �Լ�
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
            L"����",
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            fontSize,
            L"", //locale
            &m_pTmpTxtFormat
        );
    }
    // Text Format���� �ؽ�Ʈ ���� ����� �������ش�
    if (SUCCEEDED(hr))
    {
        // �ؽ�Ʈ�� �������ϴ� ���̾ƿ� �ڽ��� �¿� ������ ����
        m_pTmpTxtFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        // �ؽ�Ʈ�� �������ϴ� ���̾ƿ� �ڽ��� ���� ������ ����
        m_pTmpTxtFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
    }
}

/// <summary>
/// ���� �׸��� �Լ�(Primitive)
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
        // ä��� ����
        if (isFill == true) m_pRenderTarget->FillEllipse(tmp, m_pTmpBrush);
        // ä��� ����
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
        // ä��� ����
        if (isFill == true) m_pRenderTarget->FillRectangle(tmp, m_pTmpBrush);
        // ä��� ����
        else m_pRenderTarget->DrawRectangle(tmp, m_pTmpBrush);
    }
}

/// <summary>
/// ���� �׸��� �Լ�
/// </summary>
/// <param name="x1">������ x��ǥ</param>
/// <param name="y1">������ y��ǥ</param>
/// <param name="x2">������ x��ǥ</param>
/// <param name="y2">������ y��ǥ</param>
/// <param name="color">����</param>
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

	// string�� ����ϴ� ó��(�����ڵ� ����)
	// �ش� ó���� �� �ϸ� �ѱ��� ������
	// http://www.dreamy.pe.kr/zbxe/CodeClip/5961
	const char* txtBuffer = str.c_str();
	BSTR bstr;
	// �����ڵ�� ��ȯ�ϱ⿡ �ռ� ���� ���ڿ��� ���̸� �˾ƾ� �Ѵ�
	int nLen = MultiByteToWideChar(CP_ACP, 0, txtBuffer, strlen(txtBuffer), NULL, NULL);
	// �� ���̸�ŭ �޸𸮸� �Ҵ��Ѵ�.
	bstr = SysAllocStringLen(NULL, nLen);
	// ���� ��ȯ�� �����Ѵ�
	MultiByteToWideChar(CP_ACP, 0, txtBuffer, strlen(txtBuffer), bstr, nLen);
	SetTransform(IdentityMtrix);

	m_pTmpTxtFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)vertical);
	m_pTmpTxtFormat->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)horizontal);
	if (bstr != nullptr)
	{
		// DrawText: IDWriteTextFormat ��ü�� ���� ������ �ؽ�Ʈ�� �׸��� �Լ�
		m_pRenderTarget->DrawText(
			bstr,                   // [in] �׸� ���ڿ�
			wcslen(bstr),           // ���ڿ��� ����
			m_pTmpTxtFormat,          // [in] �ؽ�Ʈ�� ���� ���� ����
			// ���ڿ��� �׸� ��ġ
			D2D1::RectF(x1, y1, x2, y2),
			m_pTmpBrush             // �ؽ�Ʈ�� ������ �귯��
		);
	}

	// �ʿ������  BSTR�� �����Ѵ�
	SysFreeString(bstr);

	// (??) ���� ��� �� �ؽ�Ʈ ������ �޸𸮸� �����Ϸ��� ������
	// delete�� �ϸ� ������ �߻��Ѵ�(�߸��� �޸� ���� ����...) ������ ���� �𸣰ڴ�
	// delete txtBuffer;
}

void D2DEngine::DrawString(float x1, float y1, std::string str, float fontSize, COLORREF fontColor)
{
    m_RenderTargetSize = m_pRenderTarget->GetSize();
    m_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF(fontColor)), &m_pTmpBrush);

    SetFontSize(fontSize);
    SetBrushColor(fontColor);

    // string�� ����ϴ� ó��(�����ڵ� ����)
    // �ش� ó���� �� �ϸ� �ѱ��� ������
    // http://www.dreamy.pe.kr/zbxe/CodeClip/5961
    const char* txtBuffer = str.c_str();
    BSTR bstr;
    // �����ڵ�� ��ȯ�ϱ⿡ �ռ� ���� ���ڿ��� ���̸� �˾ƾ� �Ѵ�
    int nLen = MultiByteToWideChar(CP_ACP, 0, txtBuffer, strlen(txtBuffer), NULL, NULL);
    // �� ���̸�ŭ �޸𸮸� �Ҵ��Ѵ�.
    bstr = SysAllocStringLen(NULL, nLen);
    // ���� ��ȯ�� �����Ѵ�
    MultiByteToWideChar(CP_ACP, 0, txtBuffer, strlen(txtBuffer), bstr, nLen);
    SetTransform(IdentityMtrix);

    if (bstr != nullptr)
    {
        // DrawText: IDWriteTextFormat ��ü�� ���� ������ �ؽ�Ʈ�� �׸��� �Լ�
        m_pRenderTarget->DrawText(
            bstr,                   // [in] �׸� ���ڿ�
            wcslen(bstr),           // ���ڿ��� ����
            m_pTmpTxtFormat,          // [in] �ؽ�Ʈ�� ���� ���� ����
            // ���ڿ��� �׸� ��ġ
            D2D1::RectF(x1, y1, m_RenderTargetSize.width, m_RenderTargetSize.height),
            m_pTmpBrush             // �ؽ�Ʈ�� ������ �귯��
        );
    }

    // �ʿ������  BSTR�� �����Ѵ�
    SysFreeString(bstr);

    // (??) ���� ��� �� �ؽ�Ʈ ������ �޸𸮸� �����Ϸ��� ������
    // delete�� �ϸ� ������ �߻��Ѵ�(�߸��� �޸� ���� ����...) ������ ���� �𸣰ڴ�
    // delete txtBuffer;
}

void D2DEngine::SetTransform(D2D1_MATRIX_3X2_F matrix)
{
    // ī�޶� ����� ����
    matrix = matrix * m_pEngineCamera->GetCameraTM();
    m_pRenderTarget->SetTransform(matrix);
}

/// <summary>
/// Direct3D ��ġ�� �Ҿ��� �� �ٽ� ������ �ʿ䰡 �ִ�
/// ��ġ ���� ���ҽ����� �����ϴ� �Լ�
/// </summary>
void D2DEngine::DiscardDeviceResources()
{
    // ��ġ ���� �ڿ�(���� Ÿ�� ��) ����
    SafeRelease(&m_pRenderTarget);
    SafeRelease(&m_pPathGeometry);
    // �귯�� ����
    SafeRelease(&m_pLinearGradientBrush);
    SafeRelease(&m_pBlackBrush);
    SafeRelease(&m_pRedBrush);
    SafeRelease(&m_pYellowBrush);
    SafeRelease(&m_pTmpBrush);
    SafeRelease(&m_pNowBrush);
    SafeRelease(&m_pGridPatternBitmapBrush);
    // ��Ʈ�� ����
    SafeRelease(&m_pBitmap);
    SafeRelease(&m_pAnotherBitmap);
}

void D2DEngine::BeginRender()
{
    // ��ġ ���� �ڿ��鿡 ������ ����, �����쿡 ������ ������ ������ ��
    if (SUCCEEDED(is_DDR_OK)
        && !(m_pRenderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
    {
        // ���� Ÿ���� ����� ȹ��
        m_RenderTargetSize = m_pRenderTarget->GetSize();
        // RenderTarget�� �׸��� ó�� ����
        m_pRenderTarget->BeginDraw();
        // ������ ���� ��ȯ�� �ʱ�ȭ
        m_pRenderTarget->SetTransform(IdentityMtrix);
        // ���� Ÿ���� ������ �ʱ�ȭ
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

        // ���� Ÿ���� �ڿ��� �����ؾ� �� ���
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

        // �ε��� ���� ���� üũ
        ID2D1Bitmap* _sheet = m_ResourceManager->GetImage(_tmp->m_SheetIndex);
        if (_sheet != nullptr && _tmp != _tmp)
        {
            // ������ �۾��� �� ������ ����
            D2D1_RECT_F _D2DRenderingArea;
            _D2DRenderingArea.left = (FLOAT)_RenderingArea.left;
            _D2DRenderingArea.top = (FLOAT)_RenderingArea.top;
            _D2DRenderingArea.right = (FLOAT)_RenderingArea.right;
            _D2DRenderingArea.bottom = (FLOAT)_RenderingArea.bottom;

            m_pRenderTarget->DrawBitmap(
                _sheet,
                // ������ �۾��� �� ȭ���� ����
                _D2DRenderingArea,
                // ����
                alpha,
                // �̹����� ���� ���� �˰���: ������ �ȼ��� ���� ����� 4���� ��Ʈ�� �ȼ��� ���� ����
                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
                // �׸� ��������Ʈ�� ��������Ʈ ��Ʈ������ ����(�ش� ������ �׸�)
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
    // ��������Ʈ üũ
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
        // ������ �۾��� �� ȭ���� ������ ���� �� ��(Ʈ���������� ����)
        //D2D1::RectF(-_Width, -_Height, _Width * _Fill, _Height * _Fill),
        D2D1::RectF(-_Width, -_Height, -_Width + (2 * _Width * _FillX), -_Height + (2 * _Height * _FillY)),
        // ����
        alpha,
        // �̹����� ���� ���� �˰���: ������ �ȼ��� ���� ����� 4���� ��Ʈ�� �ȼ��� ���� ����
        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
        // �׸� ��������Ʈ�� ��������Ʈ ��Ʈ������ ����(�ش� ������ �׸�)
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
	// ��������Ʈ üũ
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
		// ������ �۾��� �� ȭ���� ������ ���� �� ��(Ʈ���������� ����)
		//D2D1::RectF(-_Width, -_Height, _Width * _Fill, _Height * _Fill),
		D2D1::RectF(_left, _top, _left + (_right - _left) * _FillX, _top + (_bottom - _top) * _FillY),
		// ����
		alpha,
		// �̹����� ���� ���� �˰���: ������ �ȼ��� ���� ����� 4���� ��Ʈ�� �ȼ��� ���� ����
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		// �׸� ��������Ʈ�� ��������Ʈ ��Ʈ������ ����(�ش� ������ �׸�)
		D2D1::RectF(
		(float)_OriX, (float)_OriY,
		(float)_OriX + (_SpriteWidth * _FillX), (float)(_OriY + _SpriteHeight * _FillY)
	)
	);
}

void D2DEngine::SetEngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY, float _ZoomX /*= 1*/, float _ZoomY /*= 1*/, float _RotX /*= 1*/, float _RotY /*= 0*/)
{
    m_pEngineCamera->SetEngineCamera(_PosX, _PosY, _SizeX, _SizeY, _ZoomX, _ZoomY, _RotX, _RotY);
    // ī�޶�� ������Ʈ �Ŵ����� 0��(m_Layer�� 0)���� ������.
    // �̹� �����ӿ� ����� ī�޶� �����Ѵ�
    // ���� ī�޶� �������� �ʾ��� ���,
    // ���� ��ǥ�� �״�� ����ϵ��� �Ѵ�
    m_pEngineCamera->MakeEngineCameraTM();

}

//���� ���°� ����
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
