#pragma once
/// <summary>
/// 그래픽스 엔진 소스 코드의 무덤...
/// 2022.02.08 심승수
/// </summary>

#pragma region 과제용으로 만들었던 그리기 함수들
// 라인 56 즈음이었던 것
// 게임 오브젝트를 받아서 행렬 계산을 하는 함수였지만
// 본 프로젝트에서는 불필요해서 삭제함
// (행렬 계산하는 것도 좋지 않은 구조였다...)
    // 사각형
    //void DrawRectangleTRS_Origin(GameObj* v_gameObj);
    //void DrawRectangleTRS(GameObj* v_gameObj);
    //void DrawRectangleTRS_Pivot(GameObj* v_gameObj);
    //void DrawRectangleTRS_Hierarchy(GameObj* v_gameObj);
    // 원
    //void DrawCircle(GameObj* v_gameObj);
#pragma endregion

#pragma region 스프라이트 비트맵 그리기 함수
// 라인 69 즈음이었던 것
// Sprite 클래스를 추상화해서 삭제
    //void DrawSprite(Sprite* sprite, int dstX, int dstY);
#pragma endregion

#pragma region 비트맵 로드 관련 처리들
// ResourceManager에 비슷한 변수가 존재하므로 삭제

// 라인 62 즈음이었던 것
//    void DrawSprite(int spriteIndex, int dstX, int dstY);
//    // 시트에서 로드하는 버전
//    int LoadSpriteSheet(const char* filePath);
//    int LoadSpriteSheet(const wchar_t* filePath);
//    // 모든 스프라이트/스프라이트 시트 제거
//    void RemoveAllSprites();
//    void RemoveAllSpriteSheets();

// 라인 107 즈음이었던 것
//// 비트맵, 스프라이트 관련
//private:
//    // 파일에서 리소스를 로드한다
//    // (사용할 예정은 없음)
//    HRESULT LoadResourceBitmap(
//        ID2D1RenderTarget* pRenderTarget,
//        IWICImagingFactory* pIWICFactory,
//        PCWSTR resourceName,
//        PCWSTR resourceType,
//        UINT destinationWidth,
//        UINT destinationHeight,
//        ID2D1Bitmap** ppBitmap
//    );
//
//    // 파일에서 비트맵을 로드한다
//    HRESULT LoadBitmapFromFile(
//        ID2D1RenderTarget* pRenderTarget,
//        IWICImagingFactory* pIWICFactory,
//        PCWSTR uri,
//        UINT destinationWidth,
//        UINT destinationHeight,
//        ID2D1Bitmap** ppBitmap
//    );
//
//    // 스프라이트의 개수
//    int m_SpriteCount;
//    // 스프라이트 "시트"의 개수
//    int m_SpriteSheetCount;
//    // 스프라이트 시트
//    std::map<int, ID2D1Bitmap*> m_SpriteSheets;
#pragma endregion
