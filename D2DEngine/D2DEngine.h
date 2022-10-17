#pragma once
#include "D2DEngineMacro.h"
#include <tchar.h>

// Ʈ������ �ִϸ��̼� ���� ���ҽ� �Ŵ��� Ŭ����
class ResourceManager;
// ��������Ʈ�� �߻� Ŭ����
class ISprite;
// ���� ���� ī�޶�
class EngineCamera;

/// <summary>
/// �׷��Ƚ� ����
/// 2022.02.08 �ɽ¼�
/// </summary>
class D2DEngine
{
public:
    D2DEngine(HWND  hWnd);
    virtual ~D2DEngine();

    HRESULT Initialize();
    void DiscardDeviceResources();

    // �ܺο��� ����� �� �ִ� 2D ������ ó��
    void BeginRender();
    void EndRender();

    // �׸��� �ɼ� ��Ʈ
    void SetBrushColor(float r, float g, float b, float a = 1.0f);
    void SetBrushColor(COLORREF fontColor);
    void SetFontSize(float fontSize);

    // �׸��� �Լ�
    void DrawCircle(float x, float y, float radius, COLORREF color, bool isFill);
    void DrawRectangle(float x1, float y1, float x2, float y2, COLORREF color, bool isFill);
    void DrawLine(float x1, float y1, float x2, float y2, COLORREF color);
    void DrawString(float x1, float y1, std::string str, float fontSize, COLORREF fontColor);
    void DrawString(float x1, float y1, float x2, float y2, std::string str, float fontSize, int vertical, int horizontal, COLORREF fontColor);
    // ��ȯ ����� ����� �׸��� �Լ�
    void SetTransform(D2D1_MATRIX_3X2_F matrix);

    // ==================== ��Ʈ�� �� ��������Ʈ �׸��� ���� ====================
    // Ʈ������ �ִϸ��̼� ���� ���ҽ� �Ŵ��� Ŭ����
    ResourceManager* m_ResourceManager;

    // ��������Ʈ(��Ʈ��)�� ����ϴ� �Լ�(Window ������)
    void DrawSprite(ISprite* _sprite, RECT _RenderingArea, float alpha = 1.0f);
    /// <summary>
    /// ��������Ʈ(��Ʈ��)�� ����ϴ� �Լ�
    /// </summary>
    /// <param name="_SheetIndex">����� ��������Ʈ ��Ʈ�� �ε���</param>
    /// <param name="_OriX">��������Ʈ ��Ʈ������ ������(X��ǥ)</param>
    /// <param name="_OriY">��������Ʈ ��Ʈ������ ������(Y��ǥ)</param>
    /// <param name="_SpriteWidth">��������Ʈ�� ����</param>
    /// <param name="_SpriteHeight">��������Ʈ�� ����</param>
    /// <param name="_Fill">��������Ʈ�� ��� ����(0~1)</param>
    void DrawSprite(int _SheetIndex, float _OriX, float _OriY, float _SpriteWidth, float _SpriteHeight,float _Width, float _Height, float _FillX = 1.0f, float _FillY = 1.0f, float alpha = 1.0f);
    void DrawSpriteR(int _SheetIndex, float _OriX, float _OriY, float _SpriteWidth, float _SpriteHeight,float _left, float _top, float _right, float _bottom, float _FillX = 1.0f, float _FillY = 1.0f, float alpha = 1.0f);

    // ==================== (����) ī�޶� ���� ====================
    /// <summary>
    /// ���� ī�޶� �����Ѵ�
    /// </summary>
    /// <param name="_PosX">ī�޶��� X��ǥ ��ġ</param>
    /// <param name="_PosY">ī�޶��� Y��ǥ ��ġ</param>
    /// <param name="_SizeX">ī�޶��� X��ǥ ũ��</param>
    /// <param name="_SizeY">ī�޶��� Y��ǥ ũ��</param>
    /// <param name="_ZoomX">ī�޶��� ���� �� ����</param>
    /// <param name="_ZoomY">ī�޶��� ���� �� ����</param>
    /// <param name="_Degree">ī�޶��� ȸ�� ����</param>
    void SetEngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY, float _ZoomX = 1, float _ZoomY = 1, float _RotX = 1, float _RotY = 0);

private:
    HRESULT CreateDeviceIndependentResources();
    HRESULT CreateDeviceResources();
    // character set�� wide character set���� �ٲٴ� �Լ�
    wchar_t* ConvertCStoWCS(const char* orig);

    // ������ �ڵ�
    HWND m_hwnd;
    // ��ġ ���� �ڿ�(���丮 ��) ����
    ID2D1Factory* m_pD2DFactory;
    IWICImagingFactory* m_pWICFactory;
    IDWriteFactory* m_pDWriteFactory;
    IDWriteTextFormat* m_pTextFormat;
    IDWriteTextFormat* m_pTmpTxtFormat;
    // ��ġ ���� �ڿ�(���� Ÿ�� ��) ����
    HRESULT is_DDR_OK;
    ID2D1HwndRenderTarget* m_pRenderTarget;
    D2D1_SIZE_F m_RenderTargetSize;
    ID2D1PathGeometry* m_pPathGeometry;
    // �귯�� ����
    ID2D1LinearGradientBrush* m_pLinearGradientBrush;
    ID2D1SolidColorBrush* m_pBlackBrush;
    ID2D1SolidColorBrush* m_pRedBrush;
    ID2D1SolidColorBrush* m_pYellowBrush;
    ID2D1SolidColorBrush* m_pTmpBrush;
    ID2D1SolidColorBrush* m_pNowBrush;
    ID2D1BitmapBrush* m_pGridPatternBitmapBrush;
    // ��Ʈ�� ����
    ID2D1Bitmap* m_pBitmap;
    ID2D1Bitmap* m_pAnotherBitmap;
    // ��ȯ ��� ����
    const D2D1::Matrix3x2F IdentityMtrix = D2D1::Matrix3x2F::Identity();

    // ���� ī�޶�
    EngineCamera* m_pEngineCamera;
};

