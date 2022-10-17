#include "GamePCH.h"
#include "CreditScene.h"
#include "IntroScene.h"

CreditScene::CreditScene()
{

}

CreditScene::~CreditScene()
{

}

void CreditScene::Start()
{
    // ���ҽ� �Ŵ����� ȹ��(�̱���)
    ResourceManager* m_ResourceManager = ResourceManager::Instance();

    // Ÿ��Ʋ ȭ�鿡 ���� ��Ʈ����Ʈ�� ��´�
    string _SheetName = "0009_Credit";
    string _SpriteName = "0009_Credit";
    D2DSprite* _Sprite = m_ResourceManager->GetSprite(_SheetName, _SpriteName);
    // Ÿ��Ʋ ��������Ʈ ����
    m_CreditSprite = new SpriteObject(
        _SheetName,
        _SpriteName,
        1,
        Vector2D((float)_Sprite->CenterPosX, (float)_Sprite->CenterPosY),
        Vector2D((float)(_Sprite->Width / 2), (float)(_Sprite->Height / 2))
    );
    m_CreditSprite->GetComponent<SpriteRenderer>()->SetSprite(_SheetName, _SpriteName, 1.f);

    // ������Ʈ �Ŵ����� Insert
    GetObjManager()->InsertObject(m_CreditSprite);
}

void CreditScene::Update()
{
    if (KEYBORAD->KeyDonw(VK_ESCAPE)
        || KEYBORAD->XBoxPadDown(0, XBoxPadInput::Back)
        || KEYBORAD->XBoxPadDown(1, XBoxPadInput::Back))
    {
        // Ÿ��Ʋ ȭ������ �̵�
        GameProcess::m_pSceneManager->ChangeScene<IntroScene>();
    }
}

void CreditScene::Render(D2DEngine* m_Engine)
{
    GetObjManager()->Render(m_Engine);

    string str = "ESC: Ÿ��Ʋ ȭ������";
    m_Engine->DrawString(10, 40, str, 24, 0x00FFFFFF);
}
