#include "etc.h"
/// <summary>
/// �׷��Ƚ� ���� �ҽ� �ڵ��� ����...
/// 2022.02.08 �ɽ¼�
/// </summary>

#pragma region ���������� ������� �׸��� �Լ���
// ���� 290 �����̾��� ��
// ���� ������Ʈ�� �޾Ƽ� ��� ����� �ϴ� �Լ�����
// �� ������Ʈ������ ���ʿ��ؼ� ������

//void D2DEngine::DrawCircle(GameObj* v_gameObj)
//{
//    CircleObj* _tmp = dynamic_cast<CircleObj*>(v_gameObj);
//    if (_tmp != nullptr)
//    {
//        // ���� ��ǥ(������ ����)�� ����� ����ؼ� Render Target�� ����
//        D2D1_MATRIX_3X2_F _TRSMx = Transform::MakeTRSMx_World(_tmp);
//        SetTransform(_TRSMx);
//
//        if (_tmp->IsCollided())
//        {
//            DrawCircle(_tmp->m_Center.x, _tmp->m_Center.y, _tmp->m_radius,
//                0xFF0000, false
//            );
//        }
//        else
//        {
//            DrawCircle(_tmp->m_Center.x, _tmp->m_Center.y, _tmp->m_radius,
//                _tmp->m_LineColor, false
//            );
//        }
//
//        // �ǹ��� �׸���
//        DrawLine(_tmp->m_Pivot.x - 5, _tmp->m_Pivot.y, _tmp->m_Pivot.x + 5, _tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(_tmp->m_Pivot.x, _tmp->m_Pivot.y - 5, _tmp->m_Pivot.x, _tmp->m_Pivot.y + 5, 0xFF0000);
//        // ������� �ǵ�����(���� ���)
//        SetTransform(D2D1::Matrix3x2F::Identity());
//    }
//}

//void D2DEngine::DrawRectangleTRS_Origin(GameObj* v_gameObj)
//{
//    RectangleObj* tmp = dynamic_cast<RectangleObj*>(v_gameObj);
//    if (tmp != nullptr)
//    {
//        D2D1_MATRIX_3X2_F _TRSMx;
//        _TRSMx = Transform::MakeTranslateMx(tmp->m_TranslateFactor);
//        _TRSMx = _TRSMx * Transform::MakeRotateMx_Origin(tmp->m_RotateFactor);
//        _TRSMx = _TRSMx * Transform::MakeScaleMx_Origin(tmp->m_ScalseFactor);
//        SetTransform(_TRSMx);
//
//        if (tmp->IsCollided())
//        {
//            for (int i = 0; i < 4; i++)
//            {
//                Vector2D dest1 = tmp->m_Center + tmp->m_Dot[i];
//                Vector2D dest2 = tmp->m_Center + tmp->m_Dot[(i + 1) % 4];
//                DrawLine(dest1.x, dest1.y, dest2.x, dest2.y, 0xFF0000);
//            }
//        }
//        else
//        {
//            for (int i = 0; i < 4; i++)
//            {
//                Vector2D dest1 = tmp->m_Center + tmp->m_Dot[i];
//                Vector2D dest2 = tmp->m_Center + tmp->m_Dot[(i + 1) % 4];
//                DrawLine(dest1.x, dest1.y, dest2.x, dest2.y, tmp->m_LineColor);
//            }
//        }
//        // �ǹ��� �׸���
//        DrawLine(tmp->m_Pivot.x - 5, tmp->m_Pivot.y, tmp->m_Pivot.x + 5, tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(tmp->m_Pivot.x, tmp->m_Pivot.y - 5, tmp->m_Pivot.x, tmp->m_Pivot.y + 5, 0xFF0000);
//        // ������� �ǵ�����(���� ���)
//        SetTransform(D2D1::Matrix3x2F::Identity());
//    }
//}

//void D2DEngine::DrawRectangleTRS(GameObj* v_gameObj)
//{
//    RectangleObj* tmp = dynamic_cast<RectangleObj*>(v_gameObj);
//    if (tmp != nullptr)
//    {
//        D2D1_MATRIX_3X2_F _TRSMx;
//        _TRSMx = Transform::MakeTranslateMx(tmp->m_TranslateFactor);
//        _TRSMx = _TRSMx * Transform::MakeRotateMx(tmp->m_TranslateFactor, tmp->m_RotateFactor);
//        _TRSMx = _TRSMx * Transform::MakeScaleMx(tmp->m_TranslateFactor, tmp->m_ScalseFactor);
//        SetTransform(_TRSMx);
//
//        if (tmp->IsCollided())
//        {
//            for (int i = 0; i < 4; i++)
//            {
//                Vector2D dest1 = tmp->m_Center + tmp->m_Dot[i];
//                Vector2D dest2 = tmp->m_Center + tmp->m_Dot[(i + 1) % 4];
//                DrawLine(dest1.x, dest1.y, dest2.x, dest2.y, 0xFF0000);
//            }
//        }
//        else
//        {
//            for (int i = 0; i < 4; i++)
//            {
//                Vector2D dest1 = tmp->m_Center + tmp->m_Dot[i];
//                Vector2D dest2 = tmp->m_Center + tmp->m_Dot[(i + 1) % 4];
//                DrawLine(dest1.x, dest1.y, dest2.x, dest2.y, tmp->m_LineColor);
//            }
//        }
//        // �ǹ��� �׸���
//        DrawLine(tmp->m_Pivot.x - 5, tmp->m_Pivot.y, tmp->m_Pivot.x + 5, tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(tmp->m_Pivot.x, tmp->m_Pivot.y - 5, tmp->m_Pivot.x, tmp->m_Pivot.y + 5, 0xFF0000);
//        // ������� �ǵ�����(���� ���)
//        SetTransform(D2D1::Matrix3x2F::Identity());
//    }
//}

//void D2DEngine::DrawRectangleTRS_Pivot(GameObj* v_gameObj)
//{
//    RectangleObj* _tmp = dynamic_cast<RectangleObj*>(v_gameObj);
//    if (_tmp != nullptr)
//    {
//        D2D1_MATRIX_3X2_F _TRSMx;
//        _TRSMx = Transform::MakeTranslateMx(_tmp->m_TranslateFactor);
//        _TRSMx = _TRSMx * Transform::MakeRotateMx_Pivot(_tmp);
//        _TRSMx = _TRSMx * Transform::MakeScaleMx_Pivot(_tmp);
//        SetTransform(_TRSMx);
//
//        if (_tmp->IsCollided())
//        {
//            for (int i = 0; i < 4; i++)
//            {
//                Vector2D dest1 = _tmp->m_Center + _tmp->m_Dot[i];
//                Vector2D dest2 = _tmp->m_Center + _tmp->m_Dot[(i + 1) % 4];
//                DrawLine(dest1.x, dest1.y, dest2.x, dest2.y, 0xFF0000);
//            }
//        }
//        else
//        {
//            for (int i = 0; i < 4; i++)
//            {
//                Vector2D dest1 = _tmp->m_Center + _tmp->m_Dot[i];
//                Vector2D dest2 = _tmp->m_Center + _tmp->m_Dot[(i + 1) % 4];
//                DrawLine(dest1.x, dest1.y, dest2.x, dest2.y, _tmp->m_LineColor);
//            }
//        }
//        // �ǹ��� �׸���
//        DrawLine(_tmp->m_Pivot.x - 5, _tmp->m_Pivot.y, _tmp->m_Pivot.x + 5, _tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(_tmp->m_Pivot.x, _tmp->m_Pivot.y - 5, _tmp->m_Pivot.x, _tmp->m_Pivot.y + 5, 0xFF0000);
//        // ������� �ǵ�����(���� ���)
//        SetTransform(D2D1::Matrix3x2F::Identity());
//    }
//}

//void D2DEngine::DrawRectangleTRS_Hierarchy(GameObj* v_gameObj)
//{
//    RectangleObj* _tmp = dynamic_cast<RectangleObj*>(v_gameObj);
//    if (_tmp != nullptr)
//    {
//        // �ڽ��� ��� ���
//        D2D1_MATRIX_3X2_F _TRSMx;
//        _TRSMx = Transform::MakeTranslateMx(_tmp->m_TranslateFactor);
//        _TRSMx = _TRSMx * Transform::MakeRotateMx_Pivot(_tmp);
//        _TRSMx = _TRSMx * Transform::MakeScaleMx_Pivot(_tmp);
//
//        // �θ� ���� ��� �ֻ��� �θ���� ��ĸ� ����
//        // �ֻ��� �θ��� ���� null�̹Ƿ� ���� ����
//        GameObj* _tmpParent = _tmp->GetParent();
//        while (_tmpParent != nullptr)
//        {
//            _TRSMx = _TRSMx * Transform::MakeTranslateMx(_tmpParent->m_TranslateFactor);
//            _TRSMx = _TRSMx * Transform::MakeRotateMx_Pivot(_tmpParent);
//            _TRSMx = _TRSMx * Transform::MakeScaleMx_Pivot(_tmpParent);
//
//            // �θ� ���� ������Ʈ�� �θ� ���� ���
//            // �θ��� �θ��� ��ĵ� ������� �ؼ� �ٽ� ����
//            _tmpParent = _tmpParent->GetParent();
//        }
//        SetTransform(_TRSMx);
//
//        if (_tmp->IsCollided())
//        {
//            for (int i = 0; i < 4; i++)
//            {
//                Vector2D dest1 = _tmp->m_Center + _tmp->m_Dot[i];
//                Vector2D dest2 = _tmp->m_Center + _tmp->m_Dot[(i + 1) % 4];
//                DrawLine(dest1.x, dest1.y, dest2.x, dest2.y, 0xFF0000);
//            }
//        }
//        else
//        {
//            for (int i = 0; i < 4; i++)
//            {
//                Vector2D dest1 = _tmp->m_Center + _tmp->m_Dot[i];
//                Vector2D dest2 = _tmp->m_Center + _tmp->m_Dot[(i + 1) % 4];
//                DrawLine(dest1.x, dest1.y, dest2.x, dest2.y, _tmp->m_LineColor);
//            }
//        }
//        // �ǹ��� �׸���
//        DrawLine(_tmp->m_Pivot.x - 5, _tmp->m_Pivot.y, _tmp->m_Pivot.x + 5, _tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(_tmp->m_Pivot.x, _tmp->m_Pivot.y - 5, _tmp->m_Pivot.x, _tmp->m_Pivot.y + 5, 0xFF0000);
//        // ������� �ǵ�����(���� ���)
//        SetTransform(D2D1::Matrix3x2F::Identity());
//    }
//}
#pragma endregion

#pragma region ��������Ʈ ��Ʈ�� �׸��� �Լ�
// ���� 497 �����̾��� ��
// Sprite Ŭ������ �߻�ȭ�ؼ� ����
//void D2DEngine::DrawSprite(Sprite* sprite, int dstX, int dstY)
//{
//    if (sprite != nullptr)
//    {
//        ID2D1Bitmap* _sheet = m_SpriteSheets[sprite->m_SheetIndex];
//        // �ε��� ���� ���� üũ
//        if (_sheet != nullptr)
//        {
//            m_pRenderTarget->DrawBitmap(
//                _sheet,
//                // ������ �۾��� �� ȭ���� ����
//                D2D1::RectF(
//                    (float)dstX,
//                    (float)dstY,
//                    (float)(dstX + sprite->m_Width),
//                    (float)(dstY + sprite->m_Height)
//                ),
//                // ����
//                1.0f,
//                // �̹����� ���� ���� �˰���: ������ �ȼ��� ���� ����� 4���� ��Ʈ�� �ȼ��� ���� ����
//                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//                // �׸� ��������Ʈ�� ��������Ʈ ��Ʈ������ ����(�ش� ������ �׸�)
//                D2D1::RectF(
//                    (float)sprite->m_PositionInSheet.x,
//                    (float)sprite->m_PositionInSheet.y,
//                    (float)(sprite->m_PositionInSheet.x + sprite->m_Width),
//                    (float)(sprite->m_PositionInSheet.y + sprite->m_Height)
//                )
//            );
//        }
//    }
//}
#pragma endregion

#pragma region ��Ʈ�� �ε� ���� ó����
// ResourceManager�� ����� ������ �����ϹǷ� ����

// ���� 131 �����̾��� ��
    //// ��������Ʈ�� ����
    //int m_SpriteCount;
    //// ��������Ʈ "��Ʈ"�� ����
    //int m_SpriteSheetCount;
    //// ��������Ʈ ��Ʈ
    //std::map<int, ID2D1Bitmap*> m_SpriteSheets;


// ���� 443 �����̾��� ��
//int D2DEngine::LoadSpriteSheet(const char* filePath)
//{
//    wchar_t* _wcstring = this->ConvertCStoWCS(filePath);
//    int _result = LoadSpriteSheet(_wcstring);
//    delete[] _wcstring;
//    return _result;
//}
//
//int D2DEngine::LoadSpriteSheet(const wchar_t* filePath)
//{
//    HRESULT hr;
//    ID2D1Bitmap* pNewBitmap;
//
//    // Create a bitmap by loading it from a file.
//    hr = LoadBitmapFromFile(
//        m_pRenderTarget,
//        m_pWICFactory,
//        filePath,
//        0,
//        0,
//        &pNewBitmap
//    );
//
//    if (SUCCEEDED(hr))
//    {
//        m_SpriteSheets.insert(std::pair<int, ID2D1Bitmap*>(m_SpriteSheetCount, pNewBitmap));
//        m_SpriteSheetCount++;
//
//        return (m_SpriteSheetCount - 1);
//    }
//    return -1;
//}

//void D2DEngine::RemoveAllSprites()
//{
//
//}
//
//void D2DEngine::RemoveAllSpriteSheets()
//{
//
//}

//void D2DEngine::DrawSprite(int spriteIndex, int dstX, int dstY)
//{
//    if (m_SpriteSheets.empty())
//    {
//        return;
//    }
//
//    ID2D1Bitmap* _sheet = m_SpriteSheets[spriteIndex];
//
//    // ������ ��ġ�� ��Ʈ���� �׸���
//    //m_pRenderTarget->SetTransform(Transform::MakeTranslateMx(Vector2D(dstX, dstY)));
//    m_pRenderTarget->DrawBitmap(_sheet);
//    // ������� �ǵ�����(���� ���)
//    SetTransform(D2D1::Matrix3x2F::Identity());
//}

// ���� 560 �����̾��� ��
///// <summary>
///// ������Ʈ�� ���ҽ����� ��Ʈ�� ������ �ε��ϴ� �Լ�
///// (??) �ҽ��� �������� ��...���ΰ� �ʿ��ϴ�
///// </summary>
//HRESULT D2DEngine::LoadResourceBitmap(
//    ID2D1RenderTarget* pRenderTarget,
//    IWICImagingFactory* pIWICFactory,
//    PCWSTR resourceName,
//    PCWSTR resourceType,
//    UINT destinationWidth,
//    UINT destinationHeight,
//    ID2D1Bitmap** ppBitmap
//)
//{
//    HRESULT hr = S_OK;
//    IWICBitmapDecoder* pDecoder = NULL;
//    IWICBitmapFrameDecode* pSource = NULL;
//    IWICStream* pStream = NULL;
//    IWICFormatConverter* pConverter = NULL;
//    IWICBitmapScaler* pScaler = NULL;
//
//    HRSRC imageResHandle = NULL;
//    HGLOBAL imageResDataHandle = NULL;
//    void* pImageFile = NULL;
//    DWORD imageFileSize = 0;
//
//    // Locate the resource.
//    imageResHandle = FindResourceW(HINST_THISCOMPONENT, resourceName, resourceType);
//
//    hr = imageResHandle ? S_OK : E_FAIL;
//    if (SUCCEEDED(hr))
//    {
//        // Load the resource.
//        imageResDataHandle = LoadResource(HINST_THISCOMPONENT, imageResHandle);
//
//        hr = imageResDataHandle ? S_OK : E_FAIL;
//    }
//    if (SUCCEEDED(hr))
//    {
//        // Lock it to get a system memory pointer.
//        pImageFile = LockResource(imageResDataHandle);
//
//        hr = pImageFile ? S_OK : E_FAIL;
//    }
//    if (SUCCEEDED(hr))
//    {
//        // Calculate the size.
//        imageFileSize = SizeofResource(HINST_THISCOMPONENT, imageResHandle);
//
//        hr = imageFileSize ? S_OK : E_FAIL;
//    }
//    if (SUCCEEDED(hr))
//    {
//        // Create a WIC stream to map onto the memory.
//        hr = pIWICFactory->CreateStream(&pStream);
//    }
//    if (SUCCEEDED(hr))
//    {
//        // Initialize the stream with the memory pointer and size.
//        hr = pStream->InitializeFromMemory(
//            reinterpret_cast<BYTE*>(pImageFile),
//            imageFileSize
//        );
//    }
//    if (SUCCEEDED(hr))
//    {
//        // Create a decoder for the stream.
//        hr = pIWICFactory->CreateDecoderFromStream(
//            pStream,
//            NULL,
//            WICDecodeMetadataCacheOnLoad,
//            &pDecoder
//        );
//    }
//    if (SUCCEEDED(hr))
//    {
//        // Create the initial frame.
//        hr = pDecoder->GetFrame(0, &pSource);
//    }
//    if (SUCCEEDED(hr))
//    {
//        // Convert the image format to 32bppPBGRA
//        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
//        hr = pIWICFactory->CreateFormatConverter(&pConverter);
//    }
//    if (SUCCEEDED(hr))
//    {
//        // If a new width or height was specified, create an
//        // IWICBitmapScaler and use it to resize the image.
//        if (destinationWidth != 0 || destinationHeight != 0)
//        {
//            UINT originalWidth, originalHeight;
//            hr = pSource->GetSize(&originalWidth, &originalHeight);
//            if (SUCCEEDED(hr))
//            {
//                if (destinationWidth == 0)
//                {
//                    FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
//                    destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
//                }
//                else if (destinationHeight == 0)
//                {
//                    FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
//                    destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
//                }
//
//                hr = pIWICFactory->CreateBitmapScaler(&pScaler);
//                if (SUCCEEDED(hr))
//                {
//                    hr = pScaler->Initialize(
//                        pSource,
//                        destinationWidth,
//                        destinationHeight,
//                        WICBitmapInterpolationModeCubic
//                    );
//                    if (SUCCEEDED(hr))
//                    {
//                        hr = pConverter->Initialize(
//                            pScaler,
//                            GUID_WICPixelFormat32bppPBGRA,
//                            WICBitmapDitherTypeNone,
//                            NULL,
//                            0.f,
//                            WICBitmapPaletteTypeMedianCut
//                        );
//                    }
//                }
//            }
//        }
//        else
//        {
//            hr = pConverter->Initialize(
//                pSource,
//                GUID_WICPixelFormat32bppPBGRA,
//                WICBitmapDitherTypeNone,
//                NULL,
//                0.f,
//                WICBitmapPaletteTypeMedianCut
//            );
//        }
//    }
//    if (SUCCEEDED(hr))
//    {
//        //create a Direct2D bitmap from the WIC bitmap.
//        hr = pRenderTarget->CreateBitmapFromWicBitmap(
//            pConverter,
//            NULL,
//            ppBitmap
//        );
//    }
//
//    SafeRelease(&pDecoder);
//    SafeRelease(&pSource);
//    SafeRelease(&pStream);
//    SafeRelease(&pConverter);
//    SafeRelease(&pScaler);
//    return hr;
//}

///// <summary>
///// ��Ʈ�� ������ �ε��ϴ� �Լ�
///// D2D���� �̹����� �аų� ������ ���� WIC�� ����Ѵ�
///// WIC: �̹���(����)�� �����ϰų� ����, ��ȯ�ϴ� ������Ʈ
///// WIC ��ü�� �̹��� ���� �о D2D�� �̹����� ��ȯ�ϰ� ����Ѵ�
///// (Wincodec.h �ʿ�)
///// </summary>
//HRESULT D2DEngine::LoadBitmapFromFile(
//    ID2D1RenderTarget* pRenderTarget,   // �̹����� �׸��� ���� Render Target
//    IWICImagingFactory* pIWICFactory,   // WIC ��ü�� �����ϱ� ���� ���丮
//    PCWSTR uri,                         // ��Ʈ�� ���� ���
//    UINT destinationWidth,
//    UINT destinationHeight,
//    ID2D1Bitmap** ppBitmap
//)
//{
//    HRESULT hr = S_OK;
//
//    // ��Ʈ�� �������� ������ �����ϴ� ���ڴ�(png���� ��)
//    IWICBitmapDecoder* pDecoder = NULL;
//    // ��Ʈ�ʿ��� Ư�� �׸��� ������ ��ü(������)
//    // (�� ���Ͽ� �������� �׸��� ���� �� �ֱ� ����)
//    IWICBitmapFrameDecode* pSource = NULL;
//    // IWICBitmap ������ ��Ʈ���� ID2D1Bitmap �������� ��ȯ�ϱ� ���� ������
//    IWICFormatConverter* pConverter = NULL;
//    // ���ڷ� ���� Width, Height�� ���� ��Ʈ���� �������� �����ϱ� ���� ����
//    IWICBitmapScaler* pScaler = NULL;
//
//    // WIC�� Factory ��ü�� ����ؼ� �̹��� ���� ������ ���� ��ü�� ����
//    hr = pIWICFactory->CreateDecoderFromFilename(
//        uri,
//        NULL,
//        GENERIC_READ,                   //���ڴ��� ���ٹ��
//        WICDecodeMetadataCacheOnLoad,   //ĳ�� ���� �ɼ�
//        &pDecoder                       //���ڴ��� ������ ������
//    );
//
//    // ���ڴ����� �������� ��´�
//    // (������: ���� �ȼ� �����͸� ������ �ִ� ��Ʈ��)
//    // ���� ���� �׸��� �ϳ��� ���Ͽ� ����Ǿ� �ִ� ���
//    // �׸��� �� � �׸��� ����� �������� ����
//    if (SUCCEEDED(hr))
//    {
//        // Create the initial frame.
//        hr = pDecoder->GetFrame(0, &pSource);
//    }
//
//    // IWICBitmap ������ ��Ʈ���� D2D ������ ��Ʈ��(ID2D1Bitmap)���� ��ȯ�Ѵ�
//    // (GetFrame���� ���� �̹����� WIC�����̶� D2D���� �ٷ� ����ϱ� �����)
//    if (SUCCEEDED(hr))
//    {
//        // Convert the image format to 32bppPBGRA
//        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
//        // IWICBitmap ������ ��Ʈ�� ID2D1Bitmap �������� ��ȯ�ϱ� ���� ��ü ����
//        hr = pIWICFactory->CreateFormatConverter(&pConverter);
//    }
//
//    // destinationWidth, destinationHeight�� ��Ʈ���� �̹��� ����, ���θ� �����Ѵ�
//    if (SUCCEEDED(hr))
//    {
//        if (destinationWidth != 0 || destinationHeight != 0)
//        {
//            // ���� �׸�(������)�� ����� ȹ��
//            UINT originalWidth, originalHeight;
//            hr = pSource->GetSize(&originalWidth, &originalHeight);
//
//            if (SUCCEEDED(hr))
//            {
//                // ���θ� �������ϴ� ���, �׿� ����� ���� ���� ����
//                if (destinationWidth == 0)
//                {
//                    FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
//                    destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
//                }
//                // ���θ� �������ϴ� ���, �׿� ����� ���� ���� ����
//                else if (destinationHeight == 0)
//                {
//                    FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
//                    destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
//                }
//
//                // ��Ʈ���� ũ�⸦ �����ϴ� �����Ϸ��� ����
//                hr = pIWICFactory->CreateBitmapScaler(&pScaler);
//                if (SUCCEEDED(hr))
//                {
//                    // ��Ʈ���� �̹����� ����
//                    hr = pScaler->Initialize(
//                        pSource,
//                        destinationWidth,
//                        destinationHeight,
//                        WICBitmapInterpolationModeCubic
//                    );
//                }
//
//                // ������ ��Ʈ���� ID2D1Bitmap �������� ��ȯ�� ���̶�� �����Ѵ�
//                if (SUCCEEDED(hr))
//                {
//                    hr = pConverter->Initialize(
//                        pScaler,
//                        GUID_WICPixelFormat32bppPBGRA,
//                        WICBitmapDitherTypeNone,
//                        NULL,
//                        0.0f,
//                        WICBitmapPaletteTypeMedianCut
//                    );
//                }
//            }
//        }
//        // �̹��� �������� ���� ��� �ٷ� ID2D1Bitmap �������� ��ȯ�� ���̶�� �����Ѵ�
//        else
//        {
//            hr = pConverter->Initialize(
//                pSource,
//                GUID_WICPixelFormat32bppPBGRA,
//                WICBitmapDitherTypeNone,
//                NULL,
//                0.0f,
//                WICBitmapPaletteTypeMedianCut
//            );
//        }
//    }
//
//    // WIC ��Ʈ�ʿ��� D2D ��Ʈ���� �����Ѵ�
//    if (SUCCEEDED(hr))
//    {
//        hr = pRenderTarget->CreateBitmapFromWicBitmap(
//            pConverter,
//            NULL,
//            ppBitmap
//        );
//    }
//
//    SafeRelease(&pDecoder);
//    SafeRelease(&pSource);
//    SafeRelease(&pConverter);
//    SafeRelease(&pScaler);
//    return hr;
//}
#pragma endregion