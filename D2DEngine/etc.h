#pragma once
/// <summary>
/// �׷��Ƚ� ���� �ҽ� �ڵ��� ����...
/// 2022.02.08 �ɽ¼�
/// </summary>

#pragma region ���������� ������� �׸��� �Լ���
// ���� 56 �����̾��� ��
// ���� ������Ʈ�� �޾Ƽ� ��� ����� �ϴ� �Լ�������
// �� ������Ʈ������ ���ʿ��ؼ� ������
// (��� ����ϴ� �͵� ���� ���� ��������...)
    // �簢��
    //void DrawRectangleTRS_Origin(GameObj* v_gameObj);
    //void DrawRectangleTRS(GameObj* v_gameObj);
    //void DrawRectangleTRS_Pivot(GameObj* v_gameObj);
    //void DrawRectangleTRS_Hierarchy(GameObj* v_gameObj);
    // ��
    //void DrawCircle(GameObj* v_gameObj);
#pragma endregion

#pragma region ��������Ʈ ��Ʈ�� �׸��� �Լ�
// ���� 69 �����̾��� ��
// Sprite Ŭ������ �߻�ȭ�ؼ� ����
    //void DrawSprite(Sprite* sprite, int dstX, int dstY);
#pragma endregion

#pragma region ��Ʈ�� �ε� ���� ó����
// ResourceManager�� ����� ������ �����ϹǷ� ����

// ���� 62 �����̾��� ��
//    void DrawSprite(int spriteIndex, int dstX, int dstY);
//    // ��Ʈ���� �ε��ϴ� ����
//    int LoadSpriteSheet(const char* filePath);
//    int LoadSpriteSheet(const wchar_t* filePath);
//    // ��� ��������Ʈ/��������Ʈ ��Ʈ ����
//    void RemoveAllSprites();
//    void RemoveAllSpriteSheets();

// ���� 107 �����̾��� ��
//// ��Ʈ��, ��������Ʈ ����
//private:
//    // ���Ͽ��� ���ҽ��� �ε��Ѵ�
//    // (����� ������ ����)
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
//    // ���Ͽ��� ��Ʈ���� �ε��Ѵ�
//    HRESULT LoadBitmapFromFile(
//        ID2D1RenderTarget* pRenderTarget,
//        IWICImagingFactory* pIWICFactory,
//        PCWSTR uri,
//        UINT destinationWidth,
//        UINT destinationHeight,
//        ID2D1Bitmap** ppBitmap
//    );
//
//    // ��������Ʈ�� ����
//    int m_SpriteCount;
//    // ��������Ʈ "��Ʈ"�� ����
//    int m_SpriteSheetCount;
//    // ��������Ʈ ��Ʈ
//    std::map<int, ID2D1Bitmap*> m_SpriteSheets;
#pragma endregion
