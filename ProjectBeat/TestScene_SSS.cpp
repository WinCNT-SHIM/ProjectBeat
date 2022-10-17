#include "GamePCH.h"
#include "TestScene_SSS.h"
#include "CameraComponent.h"
#include "CameraObject.h"
#include "UIObject.h"
#include "Effect.h"


TestScene_SSS::TestScene_SSS()
{
	ResourceManager* m_ResourceManager = ResourceManager::Instance();

	// 카메라 테스트
	m_SceneCamera = new CameraObject();
	GetObjManager()->InsertObject(m_SceneCamera);

	// UI 테스트
    //m_UIObject = new UIObject("Player1_HP", m_SceneCamera, "0008_ComboList", "0008_ComboList");
    m_UIObject = new UIObject("Player1_HP", m_SceneCamera, "0011_UI", "0011_UI_HP");
	m_UIObject->SetLocalScaleVector(Vector2D(-1, 1));
	m_UIObject->SetLocalTranslateVector(Vector2D(960, 540));
    GetObjManager()->InsertObject(m_UIObject);

	// 배경 테스트
	m_Background = m_ResourceManager->GetSprite("0003_BackGround_Sheet", "BackGround_Sprite");
	// 배경 테스트
	m_Background = m_ResourceManager->GetSprite("0003_BackGround_Sheet", "BackGround_Sprite");

	RECT* m_BackgroundRect = new RECT();
	m_BackgroundRect->left = m_Background->m_OriX;
	m_BackgroundRect->top = m_Background->m_OriY;
	m_BackgroundRect->right = m_Background->Width / 2;
	m_BackgroundRect->bottom = m_Background->Height / 2;
	_bg = new RectObject(Vector2D((float)m_BackgroundRect->left, (float)m_BackgroundRect->top), Vector2D((float)m_BackgroundRect->right, (float)m_BackgroundRect->bottom));

	_bg->m_tr->SetLocalTranslateVector(Vector2D((float)m_BackgroundRect->right, (float)m_BackgroundRect->bottom));

	SpriteRenderer* _spriteRenderer = _bg->AddComponent<SpriteRenderer>();
	_spriteRenderer->Init(m_Background, 1);

	_bg->SetLayer(1);
	GetObjManager()->InsertObject(_bg);

	// 그냥 사각형
	_TestRect = new RectObject(Vector2D(100, 100), Vector2D(100, 100));
	_TestRect->SetLayer(2);
	_TestRect->SetName("TestRect");
	//GetObjManager()->InsertObject(_TestRect);

	// 애니메이터
	D2DSprite* sprite;
	SpriteAnimationClip* _SpriteAniClip = new SpriteAnimationClip("Effect_Test", 10);
	sprite = m_ResourceManager-> GetSprite("0000_Effect_Test Sheet", "EFFECT1");
	_SpriteAniClip->AddSprite(sprite);
	sprite = m_ResourceManager->GetSprite("0000_Effect_Test Sheet", "EFFECT2");
	_SpriteAniClip->AddSprite(sprite);
	sprite = m_ResourceManager->GetSprite("0000_Effect_Test Sheet", "EFFECT3");
	_SpriteAniClip->AddSprite(sprite);

	// 애니메이터가 갖는 영역
    //_Test = new RectObject(Vector2D((float)(sprite->Width + 10), (float)(sprite->Height + 10)), Vector2D((float)sprite->Width, (float)sprite->Height));
    _Test = new RectObject(Vector2D(100.f, 100.f), Vector2D(200.f, 200.f));

	temp = _Test->AddComponent<SpriteAnimator>();
	temp->AddAnimationClip(_SpriteAniClip->AniClipName, _SpriteAniClip);
	temp->SetLoopPlay(true);
	// 레이어 설정
	_Test->SetLayer(2);
	// 부모 설정
	//_Test->SetParent(m_SceneCamera);
	//_Test->SetParent(_TestObj);
	GetObjManager()->InsertObject(_Test);
	//_TestObj->m_Layer = 155;
	//GetObjManager()->InsertObject(_TestObj);

}

TestScene_SSS::~TestScene_SSS()
{
	// 테스트용이라 변수의 메모리 해제는 귀찮아요
}

void TestScene_SSS::Update()
{
	GetObjManager()->Update();

	Vector2D _posTmp = _TestRect->GetLocalTranslate();
	//_posTmp.x += 10;
	//_posTmp.y += 10;
	_TestRect->SetLocalTranslateVector(_posTmp);
	//_TestRect->SetLocalRotateVector(m_deree++);


	if (KEYBORAD->KeyPress(VK_DELETE))
	{
		//Vector2D _temp = _TestRect->GetLocalScale();
		//_TestRect->SetLocalScaleVector({ _temp.x - 0.01f, _temp.y - 0.01f });
		//_TestRect->SetLocalScaleVector({ 0.5, 0.5 });
		//_TestRect->SetLocalScaleVector(_temp.x - 0.01f, _temp.y - 0.01f);
        Vector2D _temp = m_UIObject->GetLocalScale();
		m_UIObject->SetLocalScaleVector(_temp.x - 0.01f, _temp.y);
	}

	if (KEYBORAD->KeyPress(VK_UP))
	{
		CameraComponent* _tmp = m_SceneCamera->GetComponent<CameraComponent>();
		_tmp->SetPos(Vector2D((float)(_tmp->GetPos().x), (float)(_tmp->GetPos().y - 10)));
		//_TestObj->SetLocalTranslateVector(Vector2D(_TestObj->GetLocalTranslate().x, _TestObj->GetLocalTranslate().y - 10));
	}
	if (KEYBORAD->KeyPress(VK_DOWN))
	{
		CameraComponent* _tmp = m_SceneCamera->GetComponent<CameraComponent>();
		_tmp->SetPos(Vector2D((float)(_tmp->GetPos().x), (float)(_tmp->GetPos().y + 10)));
		//_TestObj->SetLocalTranslateVector(Vector2D(_TestObj->GetLocalTranslate().x, _TestObj->GetLocalTranslate().y - 10));

	}
	if (KEYBORAD->KeyPress(VK_LEFT))
	{
		CameraComponent* _tmp = m_SceneCamera->GetComponent<CameraComponent>();
		_tmp->SetPos(Vector2D((float)(_tmp->GetPos().x - 10), (float)(_tmp->GetPos().y)));
		//_TestObj->SetLocalTranslateVector(Vector2D(_TestObj->GetLocalTranslate().x, _TestObj->GetLocalTranslate().y - 10));
	}
	if (KEYBORAD->KeyPress(VK_RIGHT))
	{
		CameraComponent* _tmp = m_SceneCamera->GetComponent<CameraComponent>();
		_tmp->SetPos(Vector2D((float)(_tmp->GetPos().x + 10), (float)_tmp->GetPos().y));
		//_TestObj->SetLocalTranslateVector(Vector2D(_TestObj->GetLocalTranslate().x, _TestObj->GetLocalTranslate().y - 10));
	}
	if (KEYBORAD->KeyPress(VK_SPACE))
	{
		CameraComponent* _tmp = m_SceneCamera->GetComponent<CameraComponent>();
        //_tmp->SetZoom(Vector2D((float)(_tmp->GetZoom().x - 0.01), (float)(_tmp->GetZoom().y - 0.01)));
		//_tmp->SetRotation(m_deree--);
		// _tmp->SetPos(Vector2D(100, 100));
        //temp->SetFill(temp->GetFill().x - 0.01, temp->GetFill().y);
		SpriteRenderer* _tmpSp = m_UIObject->GetUIRenderer();
		Vector2D _tempVec = _tmpSp->GetFill();
		_tmpSp->SetFill(_tempVec.x - 0.01f, _tempVec.y - 0.01f);
		//_bg->GetComponent<SpriteRenderer>()->SetFill(_bg->GetComponent<SpriteRenderer>()->GetFill().x - 0.01, _bg->GetComponent<SpriteRenderer>()->GetFill().y);
	}
	if (KEYBORAD->KeyPress(VK_RETURN))
	{
		//temp->StopAnimation();
		CameraComponent* _tmp = m_SceneCamera->GetComponent<CameraComponent>();
		//_tmp->SetZoom(Vector2D((float)(_tmp->GetZoom().x + 0.01), (float)(_tmp->GetZoom().y + 0.01)));
		//_tmp->SetPos(Vector2D(3000 / 2, 0));
        //_tmp->SetRotation(m_deree++);
        //_tmp->SetZoom({ 2, 2 });
        //temp->SetFill(temp->GetFill().x + 0.01, temp->GetFill().y);
        SpriteRenderer* _tmpSp = m_UIObject->GetUIRenderer();
        Vector2D _tempVec = _tmpSp->GetFill();
        _tmpSp->SetFill(_tempVec.x + 0.01f, _tempVec.y + 0.01f);
        //_bg->GetComponent<SpriteRenderer>()->SetFill(_bg->GetComponent<SpriteRenderer>()->GetFill().x + 0.01, _bg->GetComponent<SpriteRenderer>()->GetFill().y);
	}
	if (KEYBORAD->KeyPress(VK_ESCAPE))
	{
		CameraComponent* _tmp = m_SceneCamera->GetComponent<CameraComponent>();
		_tmp->Init();
		_TestRect->SetLocalTranslateVector(Vector2D((float)100, (float)100));
		m_deree = 0;
	}
}

void TestScene_SSS::Render(D2DEngine* m_Engine)
{
	Vector2D a = _Test->GetWorldTranslate();
	Vector2D c = m_SceneCamera->GetWorldTranslate();
	m_Engine->DrawString((float)10, (float)10, to_string(a.x) + ", " + to_string(a.y), 24, 0xFF00FF);
	m_Engine->DrawString((float)10, (float)40, to_string(c.x) + ", " + to_string(c.y), 24, 0xFF00FF);
	GetObjManager()->Render(m_Engine);
}
