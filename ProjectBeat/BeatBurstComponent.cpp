#include "GamePCH.h"
#include "BeatBurstComponent.h"
#include "InGameUIManager.h" // �ΰ����� UI �Ŵ���
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
	//������ �޾ƿͼ� � ĳ���������� ���� ȭ�鿡 �����ִ� �ʻ�� ��� �ٸ��� Ʋ���ٰ�..
	///
	///	�̱�������. ���� �ؾߵ�. SpriteObject? SpriteAnimation ������
	m_victim = victim;
	/// �޺� ������ ������� �� ����� �������� �˱�����.
	///
	/// ���߿� ġ������ SetDamage, Hit�� �Լ� ����� �߰� �ʿ�.

	_isPlayer1Input = _isPlayer1First;
	_isPlayer2Input = !_isPlayer1Input;





	m_Index = _Index;

	switch (m_Index)
	{
	case 0: //�巳
		m_SheetName = "0017_DrumBeatBurst";
		break;
	case 1: //�ŵ�
		m_SheetName = "0020_SynthesizerBeatBurst";
		break;
	case 2: //��Ÿ
		m_SheetName = "0019_GuitarBeatBurst";
		break;
	case 3: //�ƹ���
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
	case 0: //�巳
		Icon = new SpriteObject("0015_BeatBurstScene", "DRUMICON", 1.0f);
		break;
	case 1: //�ŵ�
		Icon = new SpriteObject("0015_BeatBurstScene", "SYNTHESIZERICON", 1.0f);
		break;
	case 2: //��Ÿ
		Icon = new SpriteObject("0015_BeatBurstScene", "GUITARICON", 1.0f);
		break;
	case 3: //�ƹ���
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
	case 0: //�巳
		Icon = new SpriteObject("0015_BeatBurstScene", "DRUMICON", 1.0f);
		break;
	case 1: //�ŵ�
		Icon = new SpriteObject("0015_BeatBurstScene", "SYNTHESIZERICON", 1.0f);
		break;
	case 2: //��Ÿ
		Icon = new SpriteObject("0015_BeatBurstScene", "GUITARICON", 1.0f);
		break;
	case 3: //�ƹ���
		Icon = new SpriteObject("0015_BeatBurstScene", "TAMBOURINEICON", 1.0f);
		break;
	default:
		break;
	}

	Icon->SetLayer(0);
	Icon->SetLocalTranslateVector(1770, 130);
	GameProcess::GetGameObjectManager()->InsertObject(Icon);


	/// �޺� �Է��� ���� �ڽ�
	SpriteObject* ComboBox = new SpriteObject("0015_BeatBurstScene", "COMBOBOX", 0.9f);
	ComboBox->SetLayer(0);
	ComboBox->SetLocalTranslateVector(1400, 130);
	GameProcess::GetGameObjectManager()->InsertObject(ComboBox);

	ComboBox = new SpriteObject("0015_BeatBurstScene", "COMBOBOX", 0.9f);
	ComboBox->SetLayer(0);
	ComboBox->SetLocalTranslateVector(500, 130);
	GameProcess::GetGameObjectManager()->InsertObject(ComboBox);
	//��Ʈ ����Ʈ Ŀ��Ʈ ť ����.

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


	// ����Ʈ �߰�
	GameObject* _Effect = new GameObject(Vector2D(960, 540));

	SpriteAnimationClip* _SpriteAniClip = new SpriteAnimationClip("Effect", 6);
	_SpriteAniClip->AddSprite("0001_Ball", "1");
	_SpriteAniClip->AddSprite("0001_Ball", "2");
	_SpriteAniClip->AddSprite("0001_Ball", "3");
	_SpriteAniClip->AddSprite("0001_Ball", "4");

	//�ִϸ����� Ŭ�� �߰�.
	SpriteAnimator* _SpriteAnimator = _Effect->AddComponent<SpriteAnimator>();
	_SpriteAnimator->AddAnimationClip(_SpriteAniClip->AniClipName, _SpriteAniClip);
	_SpriteAnimator->SetLoopPlay(true);
	_SpriteAnimator->Play();
	_Effect->SetLayer(2);// m_Layer = 2;

	GameProcess::GetGameObjectManager()->InsertObject(_Effect);

	GetSoundManager()->Play("Spe_Swit", IPlayMode::Effect);
	GetSoundManager()->Update();


	// ī�޶� ����
	m_SceneCamera = new CameraObject();
	GameProcess::GetGameObjectManager()->InsertObject(m_SceneCamera);
	// ==================== ����Ʈ �ð� ���� ====================
	UIObject* _NumUI;
	for (int i = 0; i < 10; i++)
	{
		// ���� �ð��� 10�� �ڸ� ���� ����
		_NumUI = new UIObject(to_string(i), m_SceneCamera, "0013_Num", "Num" + to_string(i));
		_NumUI->SetActive(false);
		_NumUI->SetLocalTranslateVector(Vector2D(965.f - 27.f, 120.f));
		m_RoundTimeUI_TenDigit[i] = _NumUI;
		GameProcess::GetGameObjectManager()->InsertObject(m_RoundTimeUI_TenDigit[i]);

		// ���� �ð��� 1�� �ڸ� ���� ����
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
			//Ű �Է��� �޴°�
			m_Player1->Update();
		}
	}
	else if (_isPlayer2Input)
	{
		_isPlayer1 = ChangeSize(m_Player1, 0.3f);
		_isPlayer2 = ChangeSize(m_Player2, 0.7f);
		if (_isPlayer1 && _isPlayer2)
		{
			//Ű �Է��� �޴°�
			m_Player2->Update();
		}
	}

	if (!_isPlayer1 || !_isPlayer2) return;
	//�ʻ�� ī��Ʈ �ٿ�.

		// ��Ÿ Ÿ�� ����
	m_DeltaTime += CTime::GetDeltaTime();
	// 1�ʸ��� ������ ī��Ʈ
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
				//�÷��̾� 1�� ��������
				if (m_Player1->CompareOther(m_Player2))
				{
					//��� ����.
					//���� ����.
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
						// �⺻ ������ ������
					}
					else
					{

						ParticleManager::Play(true, m_Player1Index, GameManager::Instance()->GetPlayer1()->GetLocalTranslate(), Particle::Effect, _Temp->getMaxHp() * 0.3f);
						// �ݰ� ������ ������
					}



					_isPlayer1Input = false;
					_isPlayer2Input = false;
					GameProcess::m_pSceneManager->PopScene();
				}
			}
			else
			{
				//�÷��̾� 2�� ���� ����
				if (m_Player2->CompareOther(m_Player1))
				{
					//��� ����.
					//���� ����.
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
						// �⺻ ������ ������
					}
					else
					{
						ParticleManager::Play(false, m_Player2Index, GameManager::Instance()->GetPlayer2()->GetLocalTranslate(), Particle::Effect, _Temp->getMaxHp() * 0.3f);
						// �ݰ� ������ ������
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

	// ���� �ð� 10�� �ڸ� ǥ��
	m_RoundTimeUI_TenDigit[_CurRoundTime / 10]->SetActive(true);
	// ���� �ð� 1�� �ڸ� ǥ��
	m_RoundTimeUI_OneDigit[_CurRoundTime % 10]->SetActive(true);
}

