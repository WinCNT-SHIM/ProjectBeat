#include "GamePCH.h"
#include "InGameScene.h"
#include "testPlayer.h"
#include "TestAnimationObject.h"
#include "Character.h"
#include "UIObject.h"
#include "CharactorInfoComponent.h"
#include "IntroScene.h" // 게임 엔드 테스트용
#include "InGameUIManager.h" // 인게임의 UI 매니저
#include "BeatBurstScene.h"
#include "SpecialPanel.h"
#include "EventSystem.h"
#include "TextComponent.h"
#include "CharaterDebug.h"
#include "ParticleManager.h"
#include "Metronome.h"
#include "Pause.h"

// UI들
#include "../Engine/Slider.h"
#include "../Engine/TextComponent.h"
#include "../Engine/Button.h"

InGameScene::InGameScene() :IScene()
{
}

InGameScene::~InGameScene()
{
	//메모리 해제
	// 게임 매니저
	GameManager::Instance()->Release();

	// 인게임 UI 매니저
	if (m_InGameUIManager != nullptr)
	{
		delete m_InGameUIManager;
	}

}


void InGameScene::Init(int _Player1Index, int _Player2Index)
{
	/// 인게임 씬 플레이어 선택 데이터 넘겨주기
	/// 여기서 캐릭터 생성하면 될 듯. todo:
	/// 씬 변경시 불러줘야함. 

	/// 00 드럼
	/// 01 신디
	/// 02 기타
	/// 03탬버린


	// ==================== 캐릭터 생성 ====================
	_MainBody = new Character("Player1", 'W', 'S', 'A', 'D', 'G', 'H', _Player1Index);
	_MainBody->SetLocalTranslateVector(560, 900);

	//_MainBody2 = new Character("Player2", VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, 'J', 'K', _Player2Index);
	// 219가 [, 221이 ]
	_MainBody2 = new Character("Player2", VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, 'I', 'O', _Player2Index);
	_MainBody2->SetLocalTranslateVector(1360, 900);
	_MainBody2->SetLocalScaleVector(-1, 1);

	_MainBody->Start(_MainBody2, 1);
	_MainBody2->Start(_MainBody, 2);

	GetObjManager()->InsertObjectAll(_MainBody);
	GetObjManager()->InsertObjectAll(_MainBody2);
	// ==================== 디버그 텍스트 생성 ====================
	GameObject* debug1 = new GameObject;
	debug1->AddComponent<TextComponent>();
	debug1->AddComponent<CharaterDebug>()->Init(_MainBody);
	debug1->SetLocalTranslateVector(500, 300);
	debug1->SetLayer(1000);
	GameObject* debug2 = new GameObject;
	debug2->AddComponent<TextComponent>();
	debug2->AddComponent<CharaterDebug>()->Init(_MainBody2);
	debug2->SetLocalTranslateVector(1400, 300);
	debug2->SetLayer(1000);
	GetObjManager()->InsertObjectAll(debug1);
	GetObjManager()->InsertObjectAll(debug2);

	// ==================== 이벤트 시스템 생성 ====================
	GameObject* eventSystem = new GameObject;
	eventSystem->AddComponent<EventSystem>()->Init();
	GetObjManager()->InsertObject(eventSystem);
	// ==================== 카메라 생성 ====================
	m_SceneCamera = new CameraObject();
	GetObjManager()->InsertObject(m_SceneCamera);

	// ==================== UI 매니저 생성 ====================
	m_InGameUIManager = new InGameUIManager(m_SceneCamera);
	m_InGameUIManager->Init(_Player1Index, _Player2Index);

	// 라운드 시간 초기 표시
	m_CurRoundTime = m_MaxRoundTime;

	// ==================== 게임 매니저 생성 ====================
	GameManager::Instance()->Init(_MainBody, _MainBody2, m_InGameUIManager, this);



	//==========================
	ParticleManager::Init();

}

void InGameScene::Start()
{
	GetSoundManager()->Pause(IPlayMode::BGM, true);
	// ==================== 배경 생성 ====================
	m_Background = new SpriteObject("0003_BackGround_Sheet", "BackGround_Sprite", 1.f, Vector2D(960, 540));
	GetObjManager()->InsertObject(m_Background);

	// ==================== 바닥 생성 ====================
	RectObject* _Tile = new RectObject(Vector2D(500, 1050), Vector2D(2000, 100));
	GetObjManager()->InsertObject(_Tile);

	// ==================== 왼벽 생성 ====================
	_Tile = new RectObject(Vector2D(-100, 540), Vector2D(100, 1080));
	GetObjManager()->InsertObject(_Tile);

	// ==================== 오른벽 생성 ====================
	_Tile = new RectObject(Vector2D(2020, 540), Vector2D(100, 1080));
	GetObjManager()->InsertObject(_Tile);

	/// <summary>
	/// 메트로놈
	/// </summary>
	//GetSoundManager()->Play("Ef_Get", IPlayMode::Effect);
	m_MetroNome = new GameObject(Vector2D(960, 500));
	m_MetroNome->AddComponent<Metronome>();
	m_MetroNome->SetActive(false);
	GetObjManager()->InsertObject(m_MetroNome);

	/// <summary>
	/// 퍼즈 버튼
	/// </summary>
	m_PauseObject = new GameObject();
	m_PauseObject->AddComponent<Pause>();
	m_PauseObject->SetLocalTranslateVector(960, 540);
	m_PauseObject->SetActive(false);
	m_PauseObject->SetLayer(100);
	GetObjManager()->InsertObject(m_PauseObject);


	///필살기 On Panel
	m_P1SpecialPanel = new GameObject();
	m_P1SpecialPanel->AddComponent<SpriteRenderer>()->Init("0015_BeatBurstScene", "SPECIALCOMMAND", 1.0f);
	m_P1SpecialPanel->SetLocalTranslateVector(250, 250);
	m_P1SpecialPanel->SetLayer(10000);
	m_P1SpecialPanel->SetActive(false);
	GetObjManager()->InsertObject(m_P1SpecialPanel);

	m_P2SpecialPanel = new GameObject();
	m_P2SpecialPanel->AddComponent<SpriteRenderer>()->Init("0015_BeatBurstScene", "SPECIALCOMMAND2", 1.0f);
	m_P2SpecialPanel->SetLocalTranslateVector(1650, 250);
	m_P2SpecialPanel->SetLayer(10000);
	m_P2SpecialPanel->SetActive(false);
	GetObjManager()->InsertObject(m_P2SpecialPanel);

#pragma region Option Object

	{
		GameObject* optionPanel = new GameObject;
		SpriteRenderer* opsr = optionPanel->AddComponent<SpriteRenderer>();
		optionPanel->SetLayer(50);
		opsr->SetSprite("0032_UI_setting_Spritesheets", "BG Sprite1");
		opsr->leftTop = { -250,-200 };
		opsr->rightBot = { 250,200 };
		optionPanel->SetLocalTranslateVector(960, 540);

		GameObject* sliderBar = new GameObject;
		SpriteRenderer* s1 = sliderBar->AddComponent<SpriteRenderer>();
		s1->SetSprite("0032_UI_setting_Spritesheets", "BGMBar Sprite1");

		GameObject* sliderBarBG = new GameObject;
		SpriteRenderer* s1BG = sliderBarBG->AddComponent<SpriteRenderer>();
		s1BG->SetSprite("0032_UI_setting_Spritesheets", "BGMBarBG Sprite1");

		GameObject* slider = new GameObject;
		SpriteRenderer* s2 = slider->AddComponent<SpriteRenderer>();
		s2->SetSprite("0032_UI_setting_Spritesheets", "Icon Sprite1", 1);
		s2->leftTop = s2->leftTop * 2;
		s2->rightBot = s2->rightBot * 2;

		GameObject* parentObj = new GameObject;
		parentObj->SetLayer(51);
		parentObj->SetParent(optionPanel);
		parentObj->SetLocalTranslateVector({ 50, -70 });
		Slider* sliderCP = parentObj->AddComponent<Slider>();
		RECT rect = {
			-150, -15, 150, 15
		};
		sliderCP->Init(slider, sliderBar, sliderBarBG, rect, 1, 1);
		sliderCP->AddEvent({ nullptr,"SoundManager", "SetSoundVoulume", 0 });

		GameObject* sliderBar2 = new GameObject;
		SpriteRenderer* s12 = sliderBar2->AddComponent<SpriteRenderer>();
		s12->SetSprite("0032_UI_setting_Spritesheets", "EffectBar Sprite1");

		GameObject* sliderBarBG2 = new GameObject;
		SpriteRenderer* s1BG2 = sliderBarBG2->AddComponent<SpriteRenderer>();
		s1BG2->SetSprite("0032_UI_setting_Spritesheets", "EffectBarBG Sprite1");

		GameObject* slider2 = new GameObject;
		SpriteRenderer* s22 = slider2->AddComponent<SpriteRenderer>();
		s22->SetSprite("0032_UI_setting_Spritesheets", "Icon Sprite2", 1);
		s22->leftTop = s22->leftTop * 2;
		s22->rightBot = s22->rightBot * 2;

		GameObject* parentObj2 = new GameObject;
		parentObj2->SetLayer(51);
		parentObj2->SetParent(optionPanel);
		parentObj2->SetLocalTranslateVector({ 50, 20 });
		Slider* sliderCP2 = parentObj2->AddComponent<Slider>();
		rect = {
			-150, -15, 150, 15
		};
		sliderCP2->Init(slider2, sliderBar2, sliderBarBG2, rect, 1, 1);
		sliderCP2->AddEvent({ nullptr,"SoundManager", "SetSoundVoulume", 1 });

		GameObject* eventObj = new GameObject;
		EventSystem* es = eventObj->AddComponent<EventSystem>();
		es->AddUIObject(parentObj);
		es->AddUIObject(parentObj2);
		es->Init();

		GameObject* bgmobj = new GameObject;
		SpriteRenderer* bgmSr = bgmobj->AddComponent<SpriteRenderer>();
		bgmSr->SetSprite("0032_UI_setting_Spritesheets", "BGM Sprite1");
		bgmSr->leftTop = bgmSr->leftTop * 5;
		bgmSr->rightBot = bgmSr->rightBot * 5;
		bgmobj->SetLayer(51);
		bgmobj->SetParent(optionPanel);
		bgmobj->SetLocalTranslateVector(-170, -70);

		GameObject* effectobj = new GameObject;
		SpriteRenderer* effctSr = effectobj->AddComponent<SpriteRenderer>();
		effctSr->SetSprite("0032_UI_setting_Spritesheets", "Effect Sprite1");
		effctSr->leftTop = effctSr->leftTop * 5;
		effctSr->rightBot = effctSr->rightBot * 5;
		effectobj->SetLayer(51);
		effectobj->SetParent(optionPanel);
		effectobj->SetLocalTranslateVector(-170, 20);

		GameObject* returnToLoby = new GameObject;
		returnToLoby->SetLayer(51);
		returnToLoby->SetParent(optionPanel);
		returnToLoby->SetLocalTranslateVector({ -100, 100 });
		Button* rtlBtn = returnToLoby->AddComponent<Button>();
		rtlBtn->Init(
			{ -60,-25,60,25 },
			{ "0032_UI_setting_Spritesheets","ReturnToLobby Sprite1" },
			{ "0032_UI_setting_Spritesheets","ReturnToLobby Sprite2" }
		);
		rtlBtn->AddEvent({ nullptr, "GameManager", "ReturnToLobby" });
		es->AddUIObject(returnToLoby);

		GameObject* resume = new GameObject;
		resume->SetLayer(51);
		resume->SetParent(optionPanel);
		resume->SetLocalTranslateVector({ 100, 100 });
		Button* resumeBtn = resume->AddComponent<Button>();
		resumeBtn->Init(
			{ -60,-25,60,25 },
			{ "0032_UI_setting_Spritesheets","Resume Sprite1" },
			{ "0032_UI_setting_Spritesheets","Resume Sprite2" }
		);
		resumeBtn->AddEvent({ nullptr, "GameManager", "Resume" });
		es->AddUIObject(resume);

		GetObjManager()->InsertObject(eventObj);
		GetObjManager()->InsertObjectAll(optionPanel);
		optionPanel->SetActive(false);
		GameManager::Instance()->m_Option = optionPanel;
	}

#pragma endregion


}

void InGameScene::Update()
{
	PauseKeyUpdate();
	StartDelay();
	GetObjManager()->Update();
	if (GameManager::Instance()->GetPause() || !GetisStart()) return;
	RoundTimer();
	SpeedGimmick();
	RoundCheck();
}

void InGameScene::Render(D2DEngine* m_Engine)
{
	GetObjManager()->Render(m_Engine);
}

void InGameScene::ReStart()
{
	m_isStart = false;
	m_StartTimer = 0;
	m_isStart2 = false;
	//m_MetroNome->GetComponent<Metronome>()->Play();
	//GetSoundManager()->Play("Ef_Get", IPlayMode::Effect);
	//GameManager::Instance()->SetPause(true);
	if (!GameManager::Instance()->CheckGameEnd())
		GetSoundManager()->Play("Ef_Next", IPlayMode::Effect);

}

void InGameScene::SetSpecialPanel(bool _IsPlayer1, bool _IsOnOff)
{
	if (_IsPlayer1)
	{
		m_P1SpecialPanel->SetActive(_IsOnOff);
	}
	else
	{
		m_P2SpecialPanel->SetActive(_IsOnOff);
	}
}

void InGameScene::StartDelay()
{


	if (m_isStart2) return;



	// ==================== 게임 엔드인지 체크 ====================
	if (GameManager::Instance()->CheckGameEnd())
	{
		GameManager::Instance()->GoToEnding();
		return;
	}

	// 처음 라운드에는 대사를 외쳐야한다..!
	if (GameManager::Instance()->GetRound() == 0 && !m_isFirstRound2)
	{
		
		m_FirstRoundTimer += CTime::GetDeltaTime();
		if (!m_isFirstRound1)
		{
			int Index = _MainBody->GetComponent<CharactorInfoComponent>()->CharIndex;
			switch (Index)
			{
			case 0:
				GetSoundManager()->Play("Vo_St_Drum", IPlayMode::Effect);
				break;
			case 1:
				GetSoundManager()->Play("Vo_St_Syn", IPlayMode::Effect);
				break;
			case 2:
				GetSoundManager()->Play("Vo_St_Elec", IPlayMode::Effect);
				break;
			case 3:
				GetSoundManager()->Play("Vo_St_Tam", IPlayMode::Effect);
				break;
			default:
				break;
			}
			m_isFirstRound1 = true;
			_MainBody->GetComponent<StateComponent>()->PlayStartAnim();
			_MainBody2->GetComponent<StateComponent>()->PlayStartAnim();
			
		}
		if (m_FirstRoundTimer > 2.5f)
		{
			int Index = _MainBody2->GetComponent<CharactorInfoComponent>()->CharIndex;
			switch (Index)
			{
			case 0:
				GetSoundManager()->Play("Vo_St_Drum", IPlayMode::Effect);
				break;
			case 1:
				GetSoundManager()->Play("Vo_St_Syn", IPlayMode::Effect);
				break;
			case 2:
				GetSoundManager()->Play("Vo_St_Elec", IPlayMode::Effect);
				break;
			case 3:
				GetSoundManager()->Play("Vo_St_Tam", IPlayMode::Effect);
				break;
			default:
				break;
			}
			m_isFirstRound2 = true;
		}
		return;
	}


	m_StartTimer += CTime::GetDeltaTime();
	
	if (m_StartTimer < 2.5)
	{
		if (m_RoundShout)
		{
			switch (GameManager::Instance()->GetRound())
			{
			case 0:
				GetSoundManager()->Play("Sh_Fi", IPlayMode::Effect);
				break;
			case 1:
				GetSoundManager()->Play("Sh_Se", IPlayMode::Effect);
				break;
			case 2:
				GetSoundManager()->Play("Sh_Th", IPlayMode::Effect);
				break;
			case 3:
				GetSoundManager()->Play("Sh_Fo", IPlayMode::Effect);
				break;
			case 4:
				GetSoundManager()->Play("Sh_La", IPlayMode::Effect);
				break;
			default:
				break;
			}
			GetSoundManager()->SetEffectSoundVoulume(2);
			m_RoundShout = false;
		}
		
	
		GameManager::Instance()->SetCurRoundUI(true);
		_MainBody->GetComponent<StateComponent>()->PlayStartAnim();
		_MainBody2->GetComponent<StateComponent>()->PlayStartAnim();
	
	}
	else
	{
		GameManager::Instance()->SetCurRoundUI(false);
		
	}

	static bool _ShowMetroNome = true;
	if (m_StartTimer >= 2.5 && m_StartTimer < 4.5 && _ShowMetroNome == true)
	{
		m_MetroNome->SetActive(true);
		m_MetroNome->GetComponent<Metronome>()->Play();
		GetSoundManager()->Play("Ef_Get", IPlayMode::Effect);
		_ShowMetroNome = false;

	}

	if (m_StartTimer >= 4.5 && !m_isStart)
	{

		GameManager::Instance()->SetCurRoundUI(false);
		GetSoundManager()->Play("Sh_St", IPlayMode::Effect);
		if (GameManager::Instance()->GetRound() == 0)
		{
			GetSoundManager()->Play("BGM_Battle1", IPlayMode::BGM);
		}
		GetSoundManager()->Pause(IPlayMode::BGM, false);
		m_MetroNome->GetComponent<Metronome>()->Stop();
		m_isStart = true;
		m_InGameUIManager->PlayRoundStartUI();
	}
	if (m_StartTimer >= 5.5)
	{
		
		GameManager::Instance()->SetPause(false);
		m_isStart2 = true;
		_ShowMetroNome = true;
		m_StartTimer = 0;
		m_RoundShout = true;
		_MainBody->GetComponent<StateComponent>()->setIdle();
		_MainBody2->GetComponent<StateComponent>()->setIdle();
	}
}

void InGameScene::PauseKeyUpdate()
{
	//========================Pause==============================
	if (KEYBORAD->KeyDonw(VK_ESCAPE) && m_isStart && m_isStart2)
	{
		//GameManager::Instance()->SetPause(!GameManager::Instance()->GetPause());
		if (!GameManager::Instance()->GetPause())
		{
			GameManager::Instance()->Pause();
			/*GetSoundManager()->Play("Ef_Pause", IPlayMode::Effect);
			GetSoundManager()->Pause(IPlayMode::BGM, true);
			m_PauseObject->SetActive(true);*/
		}
		else
		{
			GameManager::Instance()->Resume();
			/*GetSoundManager()->Play("Ef_Resume", IPlayMode::Effect);
			GetSoundManager()->Pause(IPlayMode::BGM, false);
			m_PauseObject->SetActive(false);*/
		}
	}
}



void InGameScene::RoundTimer()
{
	// ==================== 라운드 시간 ====================
		// 델타 타임 누적
	m_DeltaTime += CTime::GetDeltaTime();
	// 1초마다 역으로 카운트
	if (m_DeltaTime > 1.f)
	{
		m_CurRoundTime--;
		m_DeltaTime = 0.f;
	}
	GameManager::Instance()->SetRoundTime(m_CurRoundTime);
}

void InGameScene::SpeedGimmick()
{

	switch (GameManager::Instance()->GetRound())
	{
	case 0: //1라운드

		if ((float)m_CurRoundTime / m_MaxRoundTime < 0.5)
		{
			GameManager::Instance()->SetBpm((int)(GameManager::Instance()->GetStdBpm() * 1.3f));
		}
		break;
	case 1: //2라운드
		if ((float)m_CurRoundTime / m_MaxRoundTime < 0.5)
		{
			GameManager::Instance()->SetBpm((int)(GameManager::Instance()->GetStdBpm() * 0.8f));
		}
		break;
	case 2: //3라운드
		if ((float)m_CurRoundTime / m_MaxRoundTime < 0.5)
		{
			GameManager::Instance()->SetBpm((int)(GameManager::Instance()->GetStdBpm() * 1.3f));
		}
		break;
	case 3: //4라운드
		if ((float)m_CurRoundTime / m_MaxRoundTime < 0.5)
		{
			GameManager::Instance()->SetBpm((int)(GameManager::Instance()->GetStdBpm() * 0.8f));
		}
		break;
	case 4: //5라운드
		if ((float)m_CurRoundTime / m_MaxRoundTime < 0.5)
		{
			GameManager::Instance()->SetBpm((int)(GameManager::Instance()->GetStdBpm() * 1.3f));
		}
		break;
	default:
		break;
	}

}

void InGameScene::RoundCheck()
{

	// ==================== 라운드 엔드인지 체크 ====================
	if (GameManager::Instance()->CheckRoundEnd())
	{
		m_EndRoundTimer += CTime::GetDeltaTime();
		if (m_EndRoundTimer < 8.0f) return;


		m_CurRoundTime = m_MaxRoundTime;
		GameManager::Instance()->StartRound();
		m_EndRoundTimer = 0;
	}

}