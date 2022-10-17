#include "GamePCH.h"
#include "BeatBurstComponent.h"
#include "InGameUIManager.h" // 인게임의 UI 매니저
#include "BeatCommandQueue.h"
#include "Character.h"
#include "BeatBurstScene.h"
#include "CharactorInfoComponent.h"
#include "ParticleManager.h"

BeatBurstComponent::BeatBurstComponent(GameObject* _GameObject) : Component(_GameObject)
{
}

BeatBurstComponent::~BeatBurstComponent()
{
	delete m_Player1;
	delete m_Player2;
}

bool BeatBurstComponent::ChangeSize(BeatCommandQueue* _Player, float _Size)
{


	if (_Player->GetSize() - _Size > 0.01f)
	{
		_Player->SetSize(_Player->GetSize() - 0.01f);
		if (_Player->GetSize() <= _Size)
			return true;
	}
	else if (_Player->GetSize() - _Size < -0.01f)
	{
		_Player->SetSize(_Player->GetSize() + 0.01f);
		if (_Player->GetSize() >= _Size)
			return true;
	}
	else
	{
		return true;
	}

	float _Time = 0;
	while (_Time > 0.1f)
	{
		_Time += CTime::GetDeltaTime();
	}
	return false;
}

void BeatBurstComponent::Init(Character* _Caster, Character* victim, bool _isPlayer1First, int _Index, int _Player1Index, int _Player2Index, int _BeatCount)
{
	m_BeatCount = _BeatCount;
	m_Caster = _Caster;
	//정보를 받아와서 어떤 캐릭터인지에 따라 화면에 보여주는 필살기 장면 다르게 틀어줄것..
	///
	///	미구현상태. 구현 해야됨. SpriteObject? SpriteAnimation 예상중
	m_victim = victim;
	/// 콤보 성공시 대미지를 줄 대상이 누구인지 알기위해.
	///
	/// 나중에 치우한테 SetDamage, Hit등 함수 물어보고 추가 필요.

	_isPlayer1Input = _isPlayer1First;
	_isPlayer2Input = !_isPlayer1Input;





	m_Index = _Index;

	switch (m_Index)
	{
	case 0: //드럼
		m_SheetName = "0017_DrumBeatBurst";
		break;
	case 1: //신디
		m_SheetName = "0020_SynthesizerBeatBurst";
		break;
	case 2: //기타
		m_SheetName = "0019_GuitarBeatBurst";
		break;
	case 3: //탬버린
		m_SheetName = "0018_TambourineBeatBurst";
		break;
	default:
		break;
	}


	m_Player1Index = _Player1Index;
	m_Player2Index = _Player2Index;



	SpriteObject* Icon = nullptr;
	switch (m_Player1Index)
	{
	case 0: //드럼
		Icon = new SpriteObject("0015_BeatBurstScene", "DRUMICON", 1.0f);
		break;
	case 1: //신디
		Icon = new SpriteObject("0015_BeatBurstScene", "SYNTHESIZERICON", 1.0f);
		break;
	case 2: //기타
		Icon = new SpriteObject("0015_BeatBurstScene", "GUITARICON", 1.0f);
		break;
	case 3: //탬버린
		Icon = new SpriteObject("0015_BeatBurstScene", "TAMBOURINEICON", 1.0f);
		break;
	default:

		break;
	}

	Icon->SetLayer(0);
	Icon->SetLocalTranslateVector(130, 130);
	GameProcess::GetGameObjectManager()->InsertObject(Icon);


	switch (m_Player2Index)
	{
	case 0: //드럼
		Icon = new SpriteObject("0015_BeatBurstScene", "DRUMICON", 1.0f);
		break;
	case 1: //신디
		Icon = new SpriteObject("0015_BeatBurstScene", "SYNTHESIZERICON", 1.0f);
		break;
	case 2: //기타
		Icon = new SpriteObject("0015_BeatBurstScene", "GUITARICON", 1.0f);
		break;
	case 3: //탬버린
		Icon = new SpriteObject("0015_BeatBurstScene", "TAMBOURINEICON", 1.0f);
		break;
	default:
		break;
	}

	Icon->SetLayer(0);
	Icon->SetLocalTranslateVector(1770, 130);
	GameProcess::GetGameObjectManager()->InsertObject(Icon);


	/// 콤보 입력이 들어가는 박스
	SpriteObject* ComboBox = new SpriteObject("0015_BeatBurstScene", "COMBOBOX", 0.9f);
	ComboBox->SetLayer(0);
	ComboBox->SetLocalTranslateVector(1400, 130);
	GameProcess::GetGameObjectManager()->InsertObject(ComboBox);

	ComboBox = new SpriteObject("0015_BeatBurstScene", "COMBOBOX", 0.9f);
	ComboBox->SetLayer(0);
	ComboBox->SetLocalTranslateVector(500, 130);
	GameProcess::GetGameObjectManager()->InsertObject(ComboBox);
	//비트 버스트 커맨트 큐 생성.

	m_Player1 = new BeatCommandQueue('G', 'H', m_SheetName, Vector2D(490, 640), m_Index, m_BeatCount, 1);
	m_Player2 = new BeatCommandQueue('I', 'O', m_SheetName, Vector2D(1440, 640), m_Index, m_BeatCount, 2);

	TextBox1 = new SpriteObject("0015_BeatBurstScene", "INPUTTEXT", 1.0f);
	TextBox1->SetLayer(0);

	TextBox2 = new SpriteObject("0015_BeatBurstScene", "INPUTTEXT2", 1.0f);
	TextBox2->SetLayer(0);

	GameProcess::GetGameObjectManager()->InsertObject(TextBox1);
	GameProcess::GetGameObjectManager()->InsertObject(TextBox2);
	if (_isPlayer1Input)
	{
		TextBox1->SetLocalTranslateVector(500, 40);
		TextBox2->SetLocalTranslateVector(1400, 40);
		m_Player1->SetSize(0.7f);
		m_Player2->SetSize(0.3f);
	}
	else
	{
		TextBox1->SetLocalTranslateVector(1400, 40);
		TextBox2->SetLocalTranslateVector(500, 40);
		m_Player1->SetSize(0.3f);
		m_Player2->SetSize(0.7f);

	}
}
void BeatBurstComponent::Start()
{

	SpriteObject* Filter = new SpriteObject("0016_Filter", "FILTER", 1.0f);
	Filter->SetLayer(0);
	Filter->SetLocalTranslateVector(960, 540);
	GameProcess::GetGameObjectManager()->InsertObject(Filter);


	SpriteObject* Timer = new SpriteObject("0015_BeatBurstScene", "TIMEBOX", 1.0f);
	Timer->SetLayer(10);
	Timer->SetLocalTranslateVector(960, 100);
	GameProcess::GetGameObjectManager()->InsertObject(Timer);


	// 이펙트 추가
	GameObject* _Effect = new GameObject(Vector2D(960, 540));

	SpriteAnimationClip* _SpriteAniClip = new SpriteAnimationClip("Effect", 6);
	_SpriteAniClip->AddSprite("0001_Ball", "1");
	_SpriteAniClip->AddSprite("0001_Ball", "2");
	_SpriteAniClip->AddSprite("0001_Ball", "3");
	_SpriteAniClip->AddSprite("0001_Ball", "4");

	//애니메이터 클립 추가.
	SpriteAnimator* _SpriteAnimator = _Effect->AddComponent<SpriteAnimator>();
	_SpriteAnimator->AddAnimationClip(_SpriteAniClip->AniClipName, _SpriteAniClip);
	_SpriteAnimator->SetLoopPlay(true);
	_SpriteAnimator->Play();
	_Effect->SetLayer(2);// m_Layer = 2;

	GameProcess::GetGameObjectManager()->InsertObject(_Effect);

	GetSoundManager()->Play("Spe_Swit", IPlayMode::Effect);
	GetSoundManager()->Update();


	// 카메라 생성
	m_SceneCamera = new CameraObject();
	GameProcess::GetGameObjectManager()->InsertObject(m_SceneCamera);
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


}

void BeatBurstComponent::Update()
{
	bool _isPlayer1 = false;
	bool _isPlayer2 = false;
	if (_isPlayer1Input)
	{
		_isPlayer1 = ChangeSize(m_Player1, 0.7f);
		_isPlayer2 = ChangeSize(m_Player2, 0.3f);

		if (_isPlayer1 && _isPlayer2)
		{
			//키 입력을 받는곳
			m_Player1->Update();
		}
	}
	else if (_isPlayer2Input)
	{
		_isPlayer1 = ChangeSize(m_Player1, 0.3f);
		_isPlayer2 = ChangeSize(m_Player2, 0.7f);
		if (_isPlayer1 && _isPlayer2)
		{
			//키 입력을 받는곳
			m_Player2->Update();
		}
	}

	if (!_isPlayer1 || !_isPlayer2) return;
	//필살기 카운트 다운.

		// 델타 타임 누적
	m_DeltaTime += CTime::GetDeltaTime();
	// 1초마다 역으로 카운트
	if (m_DeltaTime > 1.f)
	{
		m_CurSelectTime--;
		m_DeltaTime = 0.f;
	}
	SetSelectTimeUI(m_CurSelectTime);


	if (m_CurSelectTime <= 0)
	{


		m_CurSelectTime = 3;
		if (!m_isFirst)
		{
			_isPlayer1Input = !_isPlayer1Input;
			_isPlayer2Input = !_isPlayer2Input;
			m_isFirst = true;
		}
		else
		{

			if (!_isPlayer1Input)
			{
				//플레이어 1의 공격차례
				if (m_Player1->CompareOther(m_Player2))
				{
					//방어 성공.
					//공수 교대.
					_isPlayer1Input = false;
					_isPlayer2Input = false;
					GameProcess::m_pSceneManager->ChangeScene<BeatBurstScene>();
					dynamic_cast<BeatBurstScene*>(GameProcess::m_pSceneManager->GetScene())->init(m_victim, m_Caster, false, m_Index, m_Player1Index, m_Player2Index, m_BeatCount + 1);
				}
				else
				{
					CharactorInfoComponent* _Temp = m_Caster->GetComponent<CharactorInfoComponent>();

					if (_Temp->CharIndex == m_Index)
					{


						ParticleManager::Play(true, m_Player1Index, GameManager::Instance()->GetPlayer1()->GetLocalTranslate(), Particle::Effect, _Temp->getMaxHp() * 0.5f);
						// 기본 데미지 입히기
					}
					else
					{

						ParticleManager::Play(true, m_Player1Index, GameManager::Instance()->GetPlayer1()->GetLocalTranslate(), Particle::Effect, _Temp->getMaxHp() * 0.3f);
						// 반감 데미지 입히기
					}



					_isPlayer1Input = false;
					_isPlayer2Input = false;
					GameProcess::m_pSceneManager->PopScene();
				}
			}
			else
			{
				//플레이어 2의 공격 차례
				if (m_Player2->CompareOther(m_Player1))
				{
					//방어 성공.
					//공수 교대.
					_isPlayer1Input = false;
					_isPlayer2Input = false;
					GameProcess::m_pSceneManager->ChangeScene<BeatBurstScene>();
					dynamic_cast<BeatBurstScene*>(GameProcess::m_pSceneManager->GetScene())->init(m_victim, m_Caster, true, m_Index, m_Player1Index, m_Player2Index, m_BeatCount + 1);

				}
				else
				{
					CharactorInfoComponent* _Temp = m_Caster->GetComponent<CharactorInfoComponent>();
					if (_Temp->CharIndex == m_Index)
					{

						ParticleManager::Play(false, m_Player2Index, GameManager::Instance()->GetPlayer2()->GetLocalTranslate(), Particle::Effect, _Temp->getMaxHp() * 0.5f);
						// 기본 데미지 입히기
					}
					else
					{
						ParticleManager::Play(false, m_Player2Index, GameManager::Instance()->GetPlayer2()->GetLocalTranslate(), Particle::Effect, _Temp->getMaxHp() * 0.3f);
						// 반감 데미지 입히기
					}

					_isPlayer1Input = false;
					_isPlayer2Input = false;
					GameProcess::m_pSceneManager->PopScene();
				}
			}
		}

	}
}

void BeatBurstComponent::Render(D2DEngine* _pEngine)
{

}


void BeatBurstComponent::SetSelectTimeUI(int _CurRoundTime /*= true*/)
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

