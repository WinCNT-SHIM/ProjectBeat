#include "GamePCH.h"
#include "ComboListScene.h"
#include "IntroScene.h"

ComboListScene::ComboListScene()
{
    m_ComboListSprite = nullptr;
}

ComboListScene::~ComboListScene()
{
}

void ComboListScene::Start()
{
    // ���ҽ� �Ŵ����� ȹ��(�̱���)
    ResourceManager* m_ResourceManager = ResourceManager::Instance();

    // Ÿ��Ʋ ȭ�鿡 ���� ��Ʈ����Ʈ�� ��´�
    string _SheetName = "0008_ComboList";
    string _SpriteName = "0008_ComboList";
    D2DSprite* _Sprite = m_ResourceManager->GetSprite(_SheetName, _SpriteName);
    // Ÿ��Ʋ ��������Ʈ ����
    m_ComboListSprite = new SpriteObject(
        _SheetName,
        _SpriteName,
        1,
        Vector2D((float)_Sprite->CenterPosX, (float)_Sprite->CenterPosY),
        Vector2D((float)(_Sprite->Width / 2), (float)(_Sprite->Height / 2))
    );
    m_ComboListSprite->GetComponent<SpriteRenderer>()->SetSprite(_SheetName, _SpriteName, 1.f);

    // ������Ʈ �Ŵ����� Insert
    GetObjManager()->InsertObject(m_ComboListSprite);
}

void ComboListScene::Update()
{
    if (KEYBORAD->KeyDonw(VK_ESCAPE)
        || KEYBORAD->XBoxPadDown(0, XBoxPadInput::Back)
        || KEYBORAD->XBoxPadDown(1, XBoxPadInput::Back))
    {
        // Ÿ��Ʋ ȭ������ �̵�
        GameProcess::m_pSceneManager->ChangeScene<IntroScene>();
    }
}

void ComboListScene::Render(D2DEngine* m_Engine)
{
    GetObjManager()->Render(m_Engine);

    string str = "ESC: Ÿ��Ʋ ȭ������";
    m_Engine->DrawString(10, 40, str, 24, 0x00FFFFFF);
}
