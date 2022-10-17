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
    // 리소스 매니저를 획득(싱글톤)
    ResourceManager* m_ResourceManager = ResourceManager::Instance();

    // 타이틀 화면에 대한 스트라이트를 얻는다
    string _SheetName = "0008_ComboList";
    string _SpriteName = "0008_ComboList";
    D2DSprite* _Sprite = m_ResourceManager->GetSprite(_SheetName, _SpriteName);
    // 타이틀 스프라이트 생성
    m_ComboListSprite = new SpriteObject(
        _SheetName,
        _SpriteName,
        1,
        Vector2D((float)_Sprite->CenterPosX, (float)_Sprite->CenterPosY),
        Vector2D((float)(_Sprite->Width / 2), (float)(_Sprite->Height / 2))
    );
    m_ComboListSprite->GetComponent<SpriteRenderer>()->SetSprite(_SheetName, _SpriteName, 1.f);

    // 오브젝트 매니저에 Insert
    GetObjManager()->InsertObject(m_ComboListSprite);
}

void ComboListScene::Update()
{
    if (KEYBORAD->KeyDonw(VK_ESCAPE)
        || KEYBORAD->XBoxPadDown(0, XBoxPadInput::Back)
        || KEYBORAD->XBoxPadDown(1, XBoxPadInput::Back))
    {
        // 타이틀 화면으로 이동
        GameProcess::m_pSceneManager->ChangeScene<IntroScene>();
    }
}

void ComboListScene::Render(D2DEngine* m_Engine)
{
    GetObjManager()->Render(m_Engine);

    string str = "ESC: 타이틀 화면으로";
    m_Engine->DrawString(10, 40, str, 24, 0x00FFFFFF);
}
