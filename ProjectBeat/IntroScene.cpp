#include "GamePCH.h"
#include "IntroScene.h"
#include "SelectionScene.h"
#include "ComboListScene.h"
#include "CreditScene.h"
#include "IntroCtrl.h"


IntroScene::IntroScene() : IScene()
{

}

IntroScene::~IntroScene()
{
    //EventSystem::Instance()->Release(); 
}

void IntroScene::Start()
{
    //// 리소스 매니저를 획득(싱글톤)
    //ResourceManager* m_ResourceManager = ResourceManager::Instance();

    //// 타이틀 화면에 대한 스트라이트를 얻는다
    //string _SheetName = "0004_Title";
    //string _SpriteName = "0004_Title";
    //D2DSprite* _Sprite = m_ResourceManager->GetSprite(_SheetName, _SpriteName);
    //// 타이틀 스프라이트 생성
    //m_Title = new SpriteObject(
    //    _SheetName,
    //    _SpriteName,
    //    1,
    //    Vector2D(_Sprite->CenterPosX, _Sprite->CenterPosY),
    //    Vector2D((float)(_Sprite->Width / 2), (float)(_Sprite->Height / 2))
    //);
    //m_Title->GetComponent<SpriteRenderer>()->SetSprite(_SheetName, _SpriteName, 1.f);

    // 오브젝트 매니저에 Insert
   // GetObjManager()->InsertObject(m_Title);

    // 타이틀 화면의 커서에 대한 스트라이트를 얻는다

	string _SheetName;
	string _SpriteName;
	D2DSprite* _Sprite;
    GameObject* introObj, *creditObj, *comboObj, *cursorObj;
    Vector2D cursorPos;
    // introObj
    {
        _SheetName = "0004_Title";
		_SpriteName = "0004_Title";
        _Sprite = ResourceManager::Instance()->GetSprite(_SheetName, _SpriteName);
		introObj = new SpriteObject(
			_SheetName,
			_SpriteName,
			1,
			Vector2D((float)_Sprite->CenterPosX, (float)_Sprite->CenterPosY),
			Vector2D((float)(_Sprite->Width / 2), (float)(_Sprite->Height / 2))
		);
		introObj->GetComponent<SpriteRenderer>()->SetSprite(_SheetName, _SpriteName, 1.f);
        introObj->GetComponent<SpriteRenderer>()->SetAlpha(0.f);

		GetObjManager()->InsertObject(introObj);
    }

    // creditObj
    {
		
		_SheetName = "0009_Credit";
		_SpriteName = "0009_Credit";
		_Sprite = ResourceManager::Instance()->GetSprite(_SheetName, _SpriteName);
        creditObj = new SpriteObject(
			_SheetName,
			_SpriteName,
			1,
			Vector2D((float)_Sprite->CenterPosX, (float)_Sprite->CenterPosY),
			Vector2D((float)(_Sprite->Width / 2), (float)(_Sprite->Height / 2))
		);
		creditObj->GetComponent<SpriteRenderer>()->SetSprite(_SheetName, _SpriteName, 1.f);
		creditObj->GetComponent<SpriteRenderer>()->SetAlpha(0.f);
        creditObj->SetActive(false);

		// 오브젝트 매니저에 Insert
		GetObjManager()->InsertObject(creditObj);
    }

    // comboObj
    {
		_SheetName = "0008_ComboList";
		_SpriteName = "0008_ComboList";
		_Sprite = ResourceManager::Instance()->GetSprite(_SheetName, _SpriteName);
        comboObj = new SpriteObject(
			_SheetName,
			_SpriteName,
			1,
			Vector2D((float)_Sprite->CenterPosX, (float)_Sprite->CenterPosY),
			Vector2D((float)(_Sprite->Width / 2), (float)(_Sprite->Height / 2))
		);
		comboObj->GetComponent<SpriteRenderer>()->SetSprite(_SheetName, _SpriteName, 1.f);
		comboObj->GetComponent<SpriteRenderer>()->SetAlpha(0.f);
        comboObj->SetActive(false);

		// 오브젝트 매니저에 Insert
		GetObjManager()->InsertObject(comboObj);
    }

    // cursorObj
    {
		_SheetName = "0007_TitleCursor";
		_SpriteName = "0007_TitleCursor";
		_Sprite = ResourceManager::Instance()->GetSprite(_SheetName, _SpriteName);

        cursorPos = { 777.f - (_Sprite->Width / 2), 640.0f - (_Sprite->Height / 2) };

		cursorObj = new SpriteObject(
			_SheetName,
			_SpriteName,
			1,
            cursorPos,
			Vector2D((float)(_Sprite->Width / 2), (float)(_Sprite->Height / 2))
		);
        cursorObj->GetComponent<SpriteRenderer>()->SetSprite(_SheetName, _SpriteName, 1.f);
        cursorObj->SetActive(false);
		// 커서 좌표 초기화

		// 오브젝트 매니저에 Insert
		GetObjManager()->InsertObject(cursorObj);
    }


    GameObject* introCtrl = new GameObject;
    introCtrl->AddComponent<IntroCtrl>()->Init(introObj, creditObj, comboObj, cursorObj, cursorPos);
    GetObjManager()->InsertObject(introCtrl);
    // BGM 출력
    GameProcess::m_pSoundManager->Play("BGM_Title", IPlayMode::BGM);

}

void IntroScene::Update()
{
    GetObjManager()->Update();

}

void IntroScene::Render(D2DEngine* m_Engine)
{
	GetObjManager()->Render(m_Engine);
}

