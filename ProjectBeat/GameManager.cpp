#include "GamePCH.h"
#include "GameManager.h"
#include "CharactorInfoComponent.h"
#include "Character.h"
#include "InGameUIManager.h"
#include "BeatBurstScene.h"
#include "SpecialPanel.h"
#include "InGameScene.h"
#include "IntroScene.h"
#include "EndingScene.h"

GameManager* GameManager::_instance = nullptr;

GameManager::GameManager()
{
}

GameManager::~GameManager()
{
}

GameManager* GameManager::Instance()
{
	if (_instance == nullptr)
	{
		_instance = new GameManager();
	}

	return _instance;
}

void GameManager::Release()
{
	if (_instance != nullptr)
	{
		delete _instance;
		_instance = nullptr;
	}
}

void GameManager::Init(Character* _player1, Character* _player2, InGameUIManager* _InGameUIManager, InGameScene* _NowInGameScene)
{
	/// <summary>
	/// InGameScene���� Init�Լ� ������ �� ���� ����� ��.
	/// </summary>
	m_NowInGameScene = _NowInGameScene;
	/// 
	player1 = _player1;
	player2 = _player2;
	m_InGameUIManager = _InGameUIManager;


	_currRound = 0;
	_isRoundEnd = false;
	_isGameEnd = false;
	_IsUIUpdated = false;
	_curBpm = _standardBpm;
	// ==================== �÷��� �ʱ�ȭ ====================
	bool _isRoundEnd = false;
	bool _isGameEnd = false;

	// ==================== ���ھ� �ʱ�ȭ ====================
	_playerScore[0] = 0;
	_playerScore[1] = 0;

	// ==================== UI �ʱ� ǥ��ȭ ó�� ====================
	// ü�¹� �ʱ�ȭ
	float _tmpP1MaxHp = player1->GetComponent<CharactorInfoComponent>()->getMaxHp();
	float _tmpP2MaxHp = player2->GetComponent<CharactorInfoComponent>()->getMaxHp();
	player1->GetComponent<CharactorInfoComponent>()->setHp(_tmpP1MaxHp);
	player2->GetComponent<CharactorInfoComponent>()->setHp(_tmpP2MaxHp);
	m_InGameUIManager->SetHPRatio(Player::player1, 1.f, true);
	m_InGameUIManager->SetHPRatio(Player::player2, 1.f, true);

	// �޺� ����Ʈ UI �ʱ� ǥ��
	bool _tmp[32] = { false, };
	m_InGameUIManager->SetComboList(Player::player1, _tmp);
	m_InGameUIManager->SetComboList(Player::player2, _tmp);

	SetBpm((int)_standardBpm);
}

void GameManager::SettingCharater(int playerIdx, int charaterIdx)
{
	// ĳ������ ������ (��������Ʈ ��) �ε����ְ� �÷��̾� �ε����� �´°��� ĳ���� ������Ʈ ��ġ��Ű���۾� �ʿ�
	//player1->GetComponent<CharactorInfoComponent>()->SetCharater(�÷��̾� �ε���, ĳ���� �ε���);
	//player2->GetComponent<CharactorInfoComponent>()->SetCharater(�÷��̾� �ε���, ĳ���� �ε���);
}

void GameManager::StartRound()
{
	SetBpm((int)GetStdBpm());



	_currRound++;
	_isRoundEnd = false;

	// ĳ���� ü�� ȸ��, �ִϸ��̼� ��� ����, �÷��̾� ��ġ �ٽ� ���� ���
	//player1->GetComponent<CharactorInfoComponent>()->Setting(�÷��̾� �ε���, ĳ���� �ε���);
	//player2->GetComponent<CharactorInfoComponent>()->Setting(�÷��̾� �ε���, ĳ���� �ε���);

	// todo: ��ġ �ʱ�ȭ(�ӽ�)
	player1->SetLocalTranslateVector(560, 700);
	player2->SetLocalTranslateVector(1360, 700);

	CharactorInfoComponent* _Player1Info = player1->GetComponent<CharactorInfoComponent>();
	CharactorInfoComponent* _Player2Info = player2->GetComponent<CharactorInfoComponent>();

	//  ü�� �ʱ�ȭ
	float _tmpP1MaxHp = _Player1Info->getMaxHp();
	float _tmpP2MaxHp = _Player2Info->getMaxHp();


	player1->GetComponent<StateComponent>()->ChangeState(6);

	_Player1Info->setHp(_tmpP1MaxHp);
	_Player2Info->setHp(_tmpP2MaxHp);

	_Player1Info->SetisLowHpSound(false);
	_Player2Info->SetisLowHpSound(false);



	// ==================== UI �ʱ� ǥ��ȭ ó�� ====================
	// ü�� ������
	m_InGameUIManager->SetHPRatio(Player::player1, 1.f, true);
	m_InGameUIManager->SetHPRatio(Player::player2, 1.f, true);

	// �¸� ���� ī��Ʈ
	m_InGameUIManager->SetRoundCountUI(Player::player1, _playerScore[0]);
	m_InGameUIManager->SetRoundCountUI(Player::player2, _playerScore[1]);
	m_NowInGameScene->ReStart();
}

void GameManager::EndRound(int playerIdx)
{

	if (_isGameEnd || _isRoundEnd) return;
	//gamePause = true;
	// �� �÷��̾��� �̱� �÷��̾��� ���ھ ����
	int _tmpWinPlayerIdx = 1 - (playerIdx - 1);
	_playerScore[_tmpWinPlayerIdx]++;
	GetSoundManager()->Play("Sh_Ko", IPlayMode::Effect);
	// ���� ���� UI ǥ��
	m_InGameUIManager->PlayRoundEndUI(_tmpWinPlayerIdx + 1);
	SetBpm((int)GetStdBpm());
	GetSoundManager()->Pause(IPlayMode::BGM, true);

	// �� �÷��̾��� ���ھ� ���� �ִ� ���带 ���� ���
	if (max(_playerScore[0], _playerScore[1]) >= _maxRound)
	{
		gamePause = false;
		_isGameEnd = true;
		_isRoundEnd = true;

		return;
	}
	else
	{
		gamePause = false;
		_isRoundEnd = true;
		if (playerIdx==1)
		{
			player2->GetComponent<StateComponent>()->setIdle();
			player2->GetComponent<StateComponent>()->PlayWinAnim();
		}
		else
		{
			player1->GetComponent<StateComponent>()->setIdle();
			player1->GetComponent<StateComponent>()->PlayWinAnim();
		}
		
	}



	int _Index = 0;
	string _SoundName;
	if (_tmpWinPlayerIdx == 0)
	{
		_Index = player1->GetComponent<CharactorInfoComponent>()->CharIndex;
		switch (_Index)
		{
		case 0: //�巳
			_SoundName = "Ef_Win_Drum";
			break;
		case 1: //�ŵ�
			_SoundName = "Ef_Win_Syn";

			break;
		case 2: //��Ÿ
			_SoundName = "Ef_Win_Elec";

			break;
		case 3: //�ƹ���
			_SoundName = "Ef_Win_Tam";


			break;
		default:
			break;
		}

	}
	else
	{
		_Index = player2->GetComponent<CharactorInfoComponent>()->CharIndex;

		switch (_Index)
		{
		case 0: //�巳
			_SoundName = "Ef_Win_Drum";

			break;
		case 1: //�ŵ�
			_SoundName = "Ef_Win_Syn";

			break;
		case 2: //��Ÿ
			_SoundName = "Ef_Win_Elec";

			break;
		case 3: //�ƹ���
			_SoundName = "Ef_Win_Tam";

			break;
		default:
			break;
		}

	}

	GetSoundManager()->Play(_SoundName, IPlayMode::Effect);
	GetSoundManager()->SetEffectSoundVoulume(0.5f);
}

void GameManager::EndRound()
{
	//gamePause = true;
	// ���� ���� �ð��� ������ ��� �÷��̾��� HP�� ��
	float _P1Hp = player1->GetComponent<CharactorInfoComponent>()->getHp();
	float _P2Hp = player2->GetComponent<CharactorInfoComponent>()->getHp();

	// P1�� Hp�� ���� ���
	if (_P1Hp < _P2Hp)
	{
		// P1�� �й�
		EndRound(1);

	}
	// P2�� Hp�� ���� ���
	else if (_P1Hp > _P2Hp)
	{
		// P2�� �й�
		EndRound(2);

	}
	// ü���� ������ ���
	else
	{
		// todo: ���� ��ο�� ����...�ӽ÷� ��ο�� ������ 2P �й�
		// P2�� �й�
		EndRound(2);
	}
	SetBpm((int)GetStdBpm());
}

//void GameManager::Replay()
//{
//	_currRound = 0;
//
//	_playerScore[0] = 0;
//	_playerScore[1] = 0;
//}

void GameManager::GoToEnding()
{
	// todo: ���� ���� �� ��� ���� ���� ��(������ �ӽ÷� 3�� �� ������)
	// Ȥ�� ���� ������ ��ȯ ���...
	//Sleep(3000);
	//ReturnToLobby();
	gamePause = false;
	_isGameEnd = false;
	_isRoundEnd = false;
	GetSoundManager()->Play("Ef_Fin", IPlayMode::Effect);
	int _tmpWinCharInx = 0;
	if (_playerScore[0] > _playerScore[1])
	{
		_tmpWinCharInx = player1->GetComponent<CharactorInfoComponent>()->CharIndex;
	}
	else
	{
		_tmpWinCharInx = player2->GetComponent<CharactorInfoComponent>()->CharIndex;
	}
	_playerScore[0] = 0;
	_playerScore[1] = 0;
	GameProcess::m_pSceneManager->ChangeScene<EndingScene>();
	dynamic_cast<EndingScene*>(GameProcess::m_pSceneManager->GetScene())->Init(_tmpWinCharInx);
	SetBpm((int)GetStdBpm());
}

void GameManager::SetPause(bool _Pause)
{
	gamePause = _Pause;
}

void GameManager::Pause()
{
	gamePause = true;
	GetSoundManager()->Play("Ef_Pause", IPlayMode::Effect);
	GetSoundManager()->Pause(IPlayMode::BGM, true);
	m_Option->SetActive(true);
}

void GameManager::Resume()
{
	gamePause = false;
	GetSoundManager()->Play("Ef_Resume", IPlayMode::Effect);
	GetSoundManager()->Pause(IPlayMode::BGM, false);
	m_Option->SetActive(false);
}

void GameManager::ReturnToLobby()
{
	GameProcess::m_pSceneManager->ChangeScene<IntroScene>();
}

void GameManager::SetBpm(int __bpm)
{
	_curBpm = (float)__bpm;
	player1->m_Speed = GetSpeed();
	player2->m_Speed = GetSpeed();

	player1->GetComponent<Animator>()->_speed = player1->m_Speed;
	player2->GetComponent<Animator>()->_speed = player2->m_Speed;

	::GetSoundManager()->SetSoundSpeed(_curBpm / _standardBpm, IPlayMode::BGM);
}

float GameManager::GetSpeed()
{
	return  _curBpm / _standardBpm;
}

void GameManager::SetHpUI(int playerIdx, float _ratio, bool _IsShow /*= true*/)
{
	switch (playerIdx)
	{
	case 1:
	{
		m_InGameUIManager->SetHPRatio(Player::player1, _ratio, _IsShow);
	}
	break;
	case 2:
	{
		m_InGameUIManager->SetHPRatio(Player::player2, _ratio, _IsShow);
	}
	break;
	default:
		break;
	}
}

void GameManager::SetRoundTime(int _CurRoundTime, bool _IsShow /*= true*/)
{
	m_CurRoundTime = (float)_CurRoundTime;
	m_InGameUIManager->SetRoundTimeUI((int)m_CurRoundTime);


	// ���� �ð��� 0�� �Ǹ� ���� ����� ó��
	if (_CurRoundTime <= 0)
	{
		EndRound();
	}
}

void GameManager::PlayBeatBurst(bool _isPlayer1First)
{

	/// <summary>
	/// �÷��̾� ĳ���� �ε��� ���� �̹��� �ٸ��� ���� ����� ��
	if (_isPlayer1First)
	{




		string _SpriteName;
		switch (player1->GetComponent<CharactorInfoComponent>()->CharIndex)
		{
		case 0: //�巳
			_SpriteName = "P1DRUM";
			GetSoundManager()->Play("Ef_Spe_Drum", IPlayMode::Effect);
			break;
		case 1: //�ŵ�
			_SpriteName = "P1SYNTHESIZER";
			GetSoundManager()->Play("Ef_Spe_Syn", IPlayMode::Effect);
			break;
		case 2: //��Ÿ
			_SpriteName = "P1GUITAR";
			GetSoundManager()->Play("Ef_Spe_Elec", IPlayMode::Effect);
			break;
		case 3: //�ƹ���
			_SpriteName = "P1TAMBOURINE";
			GetSoundManager()->Play("Ef_Spe_Tam", IPlayMode::Effect);
			break;
		default:
			break;
		}


		SpriteObject* _TestPanel = new SpriteObject("0021_SpecialPanel", _SpriteName, 1.0f);
		_TestPanel->AddComponent<SpecialPanel>()->Init(Vector2D(-350, 700), Vector2D(500, 700), 25, _isPlayer1First);
		_TestPanel->SetLayer(100);
		GameProcess::GetGameObjectManager()->PushBackObject(_TestPanel);
	}
	else
	{


		string _SpriteName;
		switch (player2->GetComponent<CharactorInfoComponent>()->CharIndex)
		{
		case 0: //�巳
			_SpriteName = "P2DRUM";
			GetSoundManager()->Play("Ef_Spe_Drum", IPlayMode::Effect);
			break;
		case 1: //�ŵ�
			_SpriteName = "P2SYNTHESIZER";
			GetSoundManager()->Play("Ef_Spe_Syn", IPlayMode::Effect);
			break;
		case 2: //��Ÿ
			_SpriteName = "P2GUITAR";
			GetSoundManager()->Play("Ef_Spe_Elec", IPlayMode::Effect);
			break;
		case 3: //�ƹ���
			_SpriteName = "P2TAMBOURINE";
			GetSoundManager()->Play("Ef_Spe_Tam", IPlayMode::Effect);
			break;
		default:
			break;
		}

		SpriteObject* _TestPanel2 = new SpriteObject("0021_SpecialPanel", _SpriteName, 1.0f);
		_TestPanel2->AddComponent<SpecialPanel>()->Init(Vector2D(2270, 700), Vector2D(1420, 700), 25, _isPlayer1First);
		_TestPanel2->SetLayer(100);
		GameProcess::GetGameObjectManager()->PushBackObject(_TestPanel2);
	}


}

void GameManager::ChangeBeatBurstScene(bool _isPlayer1First)
{

	int index1 = player1->GetComponent<CharactorInfoComponent>()->CharIndex;
	int index2 = player2->GetComponent<CharactorInfoComponent>()->CharIndex;

	if (_isPlayer1First) //true Player1 ����
	{
		// ���߿� �ѱ�� ���� ĳ���� �ε����� �����ؾߵ�
		GameProcess::m_pSceneManager->PushScene<BeatBurstScene>();
		dynamic_cast<BeatBurstScene*>(GameProcess::m_pSceneManager->GetScene())->init(player1, player2, _isPlayer1First, index1, index1, index2);
	}
	else
	{
		GameProcess::m_pSceneManager->PushScene<BeatBurstScene>();
		dynamic_cast<BeatBurstScene*>(GameProcess::m_pSceneManager->GetScene())->init(player2, player1, _isPlayer1First, index2, index1, index2);
	}
}
void GameManager::SetComboList(int _Player, bool _Combo[] /*= nullptr*/)
{
	if (_Player == 1)
	{
		m_InGameUIManager->SetComboList(Player::player1, _Combo);
	}
	else
	{
		m_InGameUIManager->SetComboList(Player::player2, _Combo);
	}
}

void GameManager::SetCurRoundUI(bool _IsShow /*= true*/)
{
	m_InGameUIManager->SetCurRoundUI(_currRound, _IsShow);
}

bool GameManager::GetisStart()
{
	return m_NowInGameScene->GetisStart();
}

void GameManager::SetSpecialPanel(bool _IsPlayer1, bool _IsOnOff)
{
	m_NowInGameScene->SetSpecialPanel(_IsPlayer1, _IsOnOff);
}
