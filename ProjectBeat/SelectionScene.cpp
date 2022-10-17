#include "GamePCH.h"
#include "SelectionScene.h"
#include "TestScene.h"
#include "CharSelectObject.h"
#include "SeletionComponents.h"
#include "UIObject.h"
#include "IntroScene.h"
//#include "InGameUIManager.h"	// 인게임의 UI 매니저


SelectionScene::SelectionScene() : IScene()
{

}

SelectionScene::~SelectionScene()
{
	////메모리 해제
	//// 씬 카메라 
	//if (m_SceneCamera != nullptr)
	//{
	//	delete m_SceneCamera;
	//}
}

void SelectionScene::Start()
{
	GameObject* _main = new GameObject();
	_main->AddComponent<SeletionComponents>();
	GetObjManager()->InsertObject(_main);

	// 카메라 생성
	m_SceneCamera = new CameraObject();
	GetObjManager()->InsertObject(m_SceneCamera);

	// ==================== 셀렉트 시간 생성 ====================
	UIObject* _NumUI;
	for (int i = 0; i < 10; i++)
	{
		// 라운드 시간의 10의 자리 숫자 생성
		_NumUI = new UIObject(to_string(i), m_SceneCamera, "0013_Num", "Num" + to_string(i));
		_NumUI->SetActive(false);
		_NumUI->SetLocalTranslateVector(Vector2D(965.f - 27.f, 120.f));
		m_RoundTimeUI_TenDigit[i] = _NumUI;
		GameProcess::GetGameObjectManager()->InsertObject(m_RoundTimeUI_TenDigit[i]);

		// 라운드 시간의 1의 자리 숫자 생성
		_NumUI = new UIObject(to_string(i), m_SceneCamera, "0013_Num", "Num" + to_string(i));
		_NumUI->SetActive(false);
		_NumUI->SetLocalTranslateVector(Vector2D(965.f + 27.f, 120.f));
		m_RoundTimeUI_OneDigit[i] = _NumUI;
		GameProcess::GetGameObjectManager()->InsertObject(m_RoundTimeUI_OneDigit[i]);
	}

	for (auto iter : GetObjManager()->m_vectorObjects)
	{
		SpriteRenderer* _Temp = iter->GetComponent<SpriteRenderer>();
		if (_Temp)
		{
			m_RendererList.push_back(_Temp);
			_Temp->SetAlpha(m_FadeAlpha);
		}
	}

}

void SelectionScene::Update()
{
	GetObjManager()->Update();

	if (!FadeIn()) return;
	// 델타 타임 누적
	m_DeltaTime += CTime::GetDeltaTime();
	// 1초마다 역으로 카운트
	if (m_DeltaTime > 1.f)
	{
		m_CurSelectTime--;
		m_DeltaTime = 0.f;
	}
	//m_InGameUIManager->SetRoundTimeUI(m_CurSelectTime);
	SetSelectTimeUI(m_CurSelectTime);

	if (m_CurSelectTime <= 0)
		GameProcess::m_pSceneManager->ChangeScene<IntroScene>();
}

void SelectionScene::Render(D2DEngine* m_Engine)
{
	GetObjManager()->Render(m_Engine);

	string str = "방향키와 스페이스 바로 조작";
	m_Engine->DrawString(710, 180, str, 40, 0x00FF00FF);
}

bool SelectionScene::FadeIn()
{
	if (m_FadeAlpha >= 1)
		return true;
	m_FadeAlpha += CTime::GetDeltaTime() * m_FadeSpeed;
	for (auto iter : m_RendererList)
	{
		iter->SetAlpha(m_FadeAlpha);
	}

	return false;
}
bool SelectionScene::FadeOut()
{
	if (m_FadeAlpha <= 0)
		return true;
	m_FadeAlpha -= CTime::GetDeltaTime() * m_FadeSpeed;
	for (auto iter : m_RendererList)
	{
		iter->SetAlpha(m_FadeAlpha);
	}
	return false;
}

void SelectionScene::SetSelectTimeUI(int _CurRoundTime, bool _IsShow /*= true*/)
{
	if (_CurRoundTime > 99) _CurRoundTime = 99;
	if (_CurRoundTime < 0) _CurRoundTime = 0;

	for (int i = 0; i < 10; i++)
	{
		m_RoundTimeUI_TenDigit[i]->SetActive(false);
		m_RoundTimeUI_OneDigit[i]->SetActive(false);
	}

	// 라운드 시간 10의 자리 표시
	m_RoundTimeUI_TenDigit[_CurRoundTime / 10]->SetActive(true);
	// 라운드 시간 1의 자리 표시
	m_RoundTimeUI_OneDigit[_CurRoundTime % 10]->SetActive(true);
}

