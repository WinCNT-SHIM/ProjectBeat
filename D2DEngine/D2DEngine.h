#pragma once
#include "D2DEngineMacro.h"
#include <tchar.h>

// 트랜스폼 애니메이션 전문 리소스 매니저 클래스
class ResourceManager;
// 스프라이트의 추상 클래스
class ISprite;
// 엔진 전용 카메라
class EngineCamera;

/// <summary>
/// 그래픽스 엔진
/// 2022.02.08 심승수
/// </summary>
class D2DEngine
{
public:
    D2DEngine(HWND  hWnd);
    virtual ~D2DEngine();

    HRESULT Initialize();
    void DiscardDeviceResources();

    // 외부에서 사용할 수 있는 2D 렌더링 처리
    void BeginRender();
    void EndRender();

    // 그리기 옵션 세트
    void SetBrushColor(float r, float g, float b, float a = 1.0f);
    void SetBrushColor(COLORREF fontColor);
    void SetFontSize(float fontSize);

    // 그리기 함수
    void DrawCircle(float x, float y, float radius, COLORREF color, bool isFill);
    void DrawRectangle(float x1, float y1, float x2, float y2, COLORREF color, bool isFill);
    void DrawLine(float x1, float y1, float x2, float y2, COLORREF color);
    void DrawString(float x1, float y1, std::string str, float fontSize, COLORREF fontColor);
    void DrawString(float x1, float y1, float x2, float y2, std::string str, float fontSize, int vertical, int horizontal, COLORREF fontColor);
    // 변환 행렬을 사용한 그리기 함수
    void SetTransform(D2D1_MATRIX_3X2_F matrix);

    // ==================== 비트맵 및 스프라이트 그리기 관련 ====================
    // 트랜스폼 애니메이션 전문 리소스 매니저 클래스
    ResourceManager* m_ResourceManager;

    // 스프라이트(비트맵)를 출력하는 함수(Window 종속적)
    void DrawSprite(ISprite* _sprite, RECT _RenderingArea, float alpha = 1.0f);
    /// <summary>
    /// 스프라이트(비트맵)를 출력하는 함수
    /// </summary>
    /// <param name="_SheetIndex">출력할 스프라이트 시트의 인덱스</param>
    /// <param name="_OriX">스프라이트 시트에서의 시작점(X좌표)</param>
    /// <param name="_OriY">스프라이트 시트에서의 시작점(Y좌표)</param>
    /// <param name="_SpriteWidth">스프라이트의 넓이</param>
    /// <param name="_SpriteHeight">스프라이트의 높이</param>
    /// <param name="_Fill">스프라이트의 출력 범위(0~1)</param>
    void DrawSprite(int _SheetIndex, float _OriX, float _OriY, float _SpriteWidth, float _SpriteHeight,float _Width, float _Height, float _FillX = 1.0f, float _FillY = 1.0f, float alpha = 1.0f);
    void DrawSpriteR(int _SheetIndex, float _OriX, float _OriY, float _SpriteWidth, float _SpriteHeight,float _left, float _top, float _right, float _bottom, float _FillX = 1.0f, float _FillY = 1.0f, float alpha = 1.0f);

    // ==================== (엔진) 카메라 관련 ====================
    /// <summary>
    /// 엔진 카메라를 설정한다
    /// </summary>
    /// <param name="_PosX">카메라의 X좌표 위치</param>
    /// <param name="_PosY">카메라의 Y좌표 위치</param>
    /// <param name="_SizeX">카메라의 X좌표 크기</param>
    /// <param name="_SizeY">카메라의 Y좌표 크기</param>
    /// <param name="_ZoomX">카메라의 넓이 줌 비율</param>
    /// <param name="_ZoomY">카메라의 높이 줌 비율</param>
    /// <param name="_Degree">카메라의 회전 각도</param>
    void SetEngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY, float _ZoomX = 1, float _ZoomY = 1, float _RotX = 1, float _RotY = 0);

private:
    HRESULT CreateDeviceIndependentResources();
    HRESULT CreateDeviceResources();
    // character set을 wide character set으로 바꾸는 함수
    wchar_t* ConvertCStoWCS(const char* orig);

    // 윈도우 핸들
    HWND m_hwnd;
    // 장치 독립 자원(팩토리 등) 관련
    ID2D1Factory* m_pD2DFactory;
    IWICImagingFactory* m_pWICFactory;
    IDWriteFactory* m_pDWriteFactory;
    IDWriteTextFormat* m_pTextFormat;
    IDWriteTextFormat* m_pTmpTxtFormat;
    // 장치 종속 자원(렌더 타겟 등) 관련
    HRESULT is_DDR_OK;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    D2D1_SIZE_F m_RenderTargetSize;
    ID2D1PathGeometry* m_pPathGeometry;
    // 브러시 관련
    ID2D1LinearGradientBrush* m_pLinearGradientBrush;
    ID2D1SolidColorBrush* m_pBlackBrush;
    ID2D1SolidColorBrush* m_pRedBrush;
    ID2D1SolidColorBrush* m_pYellowBrush;
    ID2D1SolidColorBrush* m_pTmpBrush;
    ID2D1SolidColorBrush* m_pNowBrush;
    ID2D1BitmapBrush* m_pGridPatternBitmapBrush;
    // 비트맵 관련
    ID2D1Bitmap* m_pBitmap;
    ID2D1Bitmap* m_pAnotherBitmap;
    // 변환 행렬 관련
    const D2D1::Matrix3x2F IdentityMtrix = D2D1::Matrix3x2F::Identity();

    // 엔진 카메라
    EngineCamera* m_pEngineCamera;
};

