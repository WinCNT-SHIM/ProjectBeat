#include "etc.h"
/// <summary>
/// 그래픽스 엔진 소스 코드의 무덤...
/// 2022.02.08 심승수
/// </summary>

#pragma region 과제용으로 만들었던 그리기 함수들
// 라인 290 즈음이었던 것
// 게임 오브젝트를 받아서 행렬 계산을 하는 함수지만
// 본 프로젝트에서는 불필요해서 삭제함

//void D2DEngine::DrawCircle(GameObj* v_gameObj)
//{
//    CircleObj* _tmp = dynamic_cast<CircleObj*>(v_gameObj);
//    if (_tmp != nullptr)
//    {
//        // 월드 좌표(계층도 포함)의 행렬을 계산해서 Render Target에 설정
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
//        // 피벗도 그리기
//        DrawLine(_tmp->m_Pivot.x - 5, _tmp->m_Pivot.y, _tmp->m_Pivot.x + 5, _tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(_tmp->m_Pivot.x, _tmp->m_Pivot.y - 5, _tmp->m_Pivot.x, _tmp->m_Pivot.y + 5, 0xFF0000);
//        // 원래대로 되돌리기(기준 행렬)
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
//        // 피벗도 그리기
//        DrawLine(tmp->m_Pivot.x - 5, tmp->m_Pivot.y, tmp->m_Pivot.x + 5, tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(tmp->m_Pivot.x, tmp->m_Pivot.y - 5, tmp->m_Pivot.x, tmp->m_Pivot.y + 5, 0xFF0000);
//        // 원래대로 되돌리기(기준 행렬)
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
//        // 피벗도 그리기
//        DrawLine(tmp->m_Pivot.x - 5, tmp->m_Pivot.y, tmp->m_Pivot.x + 5, tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(tmp->m_Pivot.x, tmp->m_Pivot.y - 5, tmp->m_Pivot.x, tmp->m_Pivot.y + 5, 0xFF0000);
//        // 원래대로 되돌리기(기준 행렬)
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
//        // 피벗도 그리기
//        DrawLine(_tmp->m_Pivot.x - 5, _tmp->m_Pivot.y, _tmp->m_Pivot.x + 5, _tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(_tmp->m_Pivot.x, _tmp->m_Pivot.y - 5, _tmp->m_Pivot.x, _tmp->m_Pivot.y + 5, 0xFF0000);
//        // 원래대로 되돌리기(기준 행렬)
//        SetTransform(D2D1::Matrix3x2F::Identity());
//    }
//}

//void D2DEngine::DrawRectangleTRS_Hierarchy(GameObj* v_gameObj)
//{
//    RectangleObj* _tmp = dynamic_cast<RectangleObj*>(v_gameObj);
//    if (_tmp != nullptr)
//    {
//        // 자식의 행렬 계산
//        D2D1_MATRIX_3X2_F _TRSMx;
//        _TRSMx = Transform::MakeTranslateMx(_tmp->m_TranslateFactor);
//        _TRSMx = _TRSMx * Transform::MakeRotateMx_Pivot(_tmp);
//        _TRSMx = _TRSMx * Transform::MakeScaleMx_Pivot(_tmp);
//
//        // 부모가 있을 경우 최상위 부모까지 행렬를 곱함
//        // 최상위 부모인 경우는 null이므로 루프 종료
//        GameObj* _tmpParent = _tmp->GetParent();
//        while (_tmpParent != nullptr)
//        {
//            _TRSMx = _TRSMx * Transform::MakeTranslateMx(_tmpParent->m_TranslateFactor);
//            _TRSMx = _TRSMx * Transform::MakeRotateMx_Pivot(_tmpParent);
//            _TRSMx = _TRSMx * Transform::MakeScaleMx_Pivot(_tmpParent);
//
//            // 부모 게임 오브젝트에 부모가 있을 경우
//            // 부모의 부모의 행렬도 곱해줘야 해서 다시 설정
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
//        // 피벗도 그리기
//        DrawLine(_tmp->m_Pivot.x - 5, _tmp->m_Pivot.y, _tmp->m_Pivot.x + 5, _tmp->m_Pivot.y, 0xFF0000);
//        DrawLine(_tmp->m_Pivot.x, _tmp->m_Pivot.y - 5, _tmp->m_Pivot.x, _tmp->m_Pivot.y + 5, 0xFF0000);
//        // 원래대로 되돌리기(기준 행렬)
//        SetTransform(D2D1::Matrix3x2F::Identity());
//    }
//}
#pragma endregion

#pragma region 스프라이트 비트맵 그리기 함수
// 라인 497 즈음이었던 것
// Sprite 클래스를 추상화해서 삭제
//void D2DEngine::DrawSprite(Sprite* sprite, int dstX, int dstY)
//{
//    if (sprite != nullptr)
//    {
//        ID2D1Bitmap* _sheet = m_SpriteSheets[sprite->m_SheetIndex];
//        // 인덱스 접근 실패 체크
//        if (_sheet != nullptr)
//        {
//            m_pRenderTarget->DrawBitmap(
//                _sheet,
//                // 렌더링 작업을 할 화면의 영역
//                D2D1::RectF(
//                    (float)dstX,
//                    (float)dstY,
//                    (float)(dstX + sprite->m_Width),
//                    (float)(dstY + sprite->m_Height)
//                ),
//                // 투명도
//                1.0f,
//                // 이미지의 조정 시의 알고리즘: 렌더링 픽셀에 가장 가까운 4개의 비트맵 픽셀로 색상 보간
//                D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
//                // 그릴 스프라이트의 스프라이트 시트에서의 범위(해당 범위만 그림)
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

#pragma region 비트맵 로드 관련 처리들
// ResourceManager에 비슷한 변수가 존재하므로 삭제

// 라인 131 즈음이었던 것
    //// 스프라이트의 개수
    //int m_SpriteCount;
    //// 스프라이트 "시트"의 개수
    //int m_SpriteSheetCount;
    //// 스프라이트 시트
    //std::map<int, ID2D1Bitmap*> m_SpriteSheets;


// 라인 443 즈음이었던 것
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
//    // 지정된 위치에 비트맵을 그린다
//    //m_pRenderTarget->SetTransform(Transform::MakeTranslateMx(Vector2D(dstX, dstY)));
//    m_pRenderTarget->DrawBitmap(_sheet);
//    // 원래대로 되돌리기(기준 행렬)
//    SetTransform(D2D1::Matrix3x2F::Identity());
//}

// 라인 560 즈음이었던 것
///// <summary>
///// 프로젝트의 리소스에서 비트맵 파일을 로드하는 함수
///// (??) 소스를 복사했을 뿐...공부가 필요하다
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
///// 비트맵 파일을 로드하는 함수
///// D2D에서 이미지를 읽거나 저장할 때는 WIC를 사용한다
///// WIC: 이미지(영상)를 압축하거나 해제, 변환하는 컴포넌트
///// WIC 객체로 이미지 파일 읽어서 D2D용 이미지로 변환하고 사용한다
///// (Wincodec.h 필요)
///// </summary>
//HRESULT D2DEngine::LoadBitmapFromFile(
//    ID2D1RenderTarget* pRenderTarget,   // 이미지를 그리기 위한 Render Target
//    IWICImagingFactory* pIWICFactory,   // WIC 객체를 생성하기 위한 팩토리
//    PCWSTR uri,                         // 비트맵 파일 경로
//    UINT destinationWidth,
//    UINT destinationHeight,
//    ID2D1Bitmap** ppBitmap
//)
//{
//    HRESULT hr = S_OK;
//
//    // 비트맵 형식으로 압축을 해제하는 디코더(png파일 등)
//    IWICBitmapDecoder* pDecoder = NULL;
//    // 비트맵에서 특정 그림을 선택한 객체(프레임)
//    // (한 파일에 여러개의 그림이 있을 수 있기 때문)
//    IWICBitmapFrameDecode* pSource = NULL;
//    // IWICBitmap 형식의 비트맵을 ID2D1Bitmap 형식으로 변환하기 위한 컨버터
//    IWICFormatConverter* pConverter = NULL;
//    // 인자로 받은 Width, Height를 비교해 비트맵의 스케일을 조정하기 위한 변수
//    IWICBitmapScaler* pScaler = NULL;
//
//    // WIC용 Factory 객체를 사용해서 이미지 압축 해제를 위한 객체를 생성
//    hr = pIWICFactory->CreateDecoderFromFilename(
//        uri,
//        NULL,
//        GENERIC_READ,                   //디코더에 접근방법
//        WICDecodeMetadataCacheOnLoad,   //캐시 관련 옵션
//        &pDecoder                       //디코더를 저장할 포인터
//    );
//
//    // 디코더에서 프레임을 얻는다
//    // (프레임: 실제 픽셀 데이터를 가지고 있는 비트맵)
//    // 여러 개의 그림이 하나의 파일에 저장되어 있는 경우
//    // 그림들 중 어떤 그림을 사용할 것인지를 선택
//    if (SUCCEEDED(hr))
//    {
//        // Create the initial frame.
//        hr = pDecoder->GetFrame(0, &pSource);
//    }
//
//    // IWICBitmap 형식의 비트맵을 D2D 형식의 비트맵(ID2D1Bitmap)으로 변환한다
//    // (GetFrame에서 얻은 이미지는 WIC형식이라 D2D에서 바로 사용하기 어려움)
//    if (SUCCEEDED(hr))
//    {
//        // Convert the image format to 32bppPBGRA
//        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
//        // IWICBitmap 형식의 비트맵 ID2D1Bitmap 형식으로 변환하기 위한 객체 생성
//        hr = pIWICFactory->CreateFormatConverter(&pConverter);
//    }
//
//    // destinationWidth, destinationHeight로 비트맵의 이미지 가로, 세로를 조절한다
//    if (SUCCEEDED(hr))
//    {
//        if (destinationWidth != 0 || destinationHeight != 0)
//        {
//            // 원래 그림(프레임)의 사이즈를 획득
//            UINT originalWidth, originalHeight;
//            hr = pSource->GetSize(&originalWidth, &originalHeight);
//
//            if (SUCCEEDED(hr))
//            {
//                // 가로만 스케일하는 경우, 그에 비례한 세로 축을 구함
//                if (destinationWidth == 0)
//                {
//                    FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
//                    destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
//                }
//                // 세로만 스케일하는 경우, 그에 비례한 가로 축을 구함
//                else if (destinationHeight == 0)
//                {
//                    FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
//                    destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
//                }
//
//                // 비트맵의 크기를 조절하는 스케일러를 생성
//                hr = pIWICFactory->CreateBitmapScaler(&pScaler);
//                if (SUCCEEDED(hr))
//                {
//                    // 비트맵의 이미지를 조절
//                    hr = pScaler->Initialize(
//                        pSource,
//                        destinationWidth,
//                        destinationHeight,
//                        WICBitmapInterpolationModeCubic
//                    );
//                }
//
//                // 조절된 비트맵을 ID2D1Bitmap 형식으로 변환할 것이라고 설정한다
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
//        // 이미지 스케일이 없을 경우 바로 ID2D1Bitmap 형식으로 변환할 것이라고 설정한다
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
//    // WIC 비트맵에서 D2D 비트맵을 생성한다
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