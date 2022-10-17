#include "GamePCH.h"
#include "InGameUIManager.h"
#include "StartIcon.h"
#include "OutroIcon.h"
InGameUIManager::InGameUIManager(CameraObject* _SceneCamera)
{
	m_SceneCamera = _SceneCamera;
	//Init();
}

InGameUIManager::~InGameUIManager()
{
	// ü�¹� UI �޸� ����
	m_PlayerHp.clear();

	// �޺� ����Ʈ UI �޸� ����
	m_ComboListUI.clear();
}

void InGameUIManager::Init(int _CharaInxP1 /*= 0 /*�巳*/, int _CharaInxP2 /*= 0*/, /*�巳*/ float _TimerPosX /*= 960.f*/, float _TimerPosY /*= 60.f*/)
{
	// ==================== ĳ���� ������ ���� ====================
	// Player1
	string _tmpSpriteName = "";
	switch (_CharaInxP1)
	{
		/// 0 �巳
	case 0:
		_tmpSpriteName = "Icon_P1_Drum";
		break;
		/// 1 �ŵ�
	case 1:
		_tmpSpriteName = "Icon_P1_Synth";
		break;
		/// 2 ��Ÿ
	case 2:
		_tmpSpriteName = "Icon_P1_Guitar";
		break;
		/// 3 �ƹ���
	case 3:
		_tmpSpriteName = "Icon_P1_Tambourine";
		break;
	default:
		break;
	}
	m_CharaIconP1 = new UIObject("Player1_Charater", m_SceneCamera, "0011_UI", _tmpSpriteName);
	m_CharaIconP1->SetActive(true);
	m_CharaIconP1->SetLocalTranslateVector(Vector2D(75, 80));
	GameProcess::GetGameObjectManager()->InsertObject(m_CharaIconP1);

	// Player2
	_tmpSpriteName = "";
	switch (_CharaInxP2)
	{
		/// 0 �巳
	case 0:
		_tmpSpriteName = "Icon_P2_Drum";
		break;
		/// 1 �ŵ�
	case 1:
		_tmpSpriteName = "Icon_P2_Synth";
		break;
		/// 2 ��Ÿ
	case 2:
		_tmpSpriteName = "Icon_P2_Guitar";
		break;
		/// 3 �ƹ���
	case 3:
		_tmpSpriteName = "Icon_P2_Tambourine";
		break;
	default:
		break;
	}
	m_CharaIconP2 = new UIObject("Player2_Charater", m_SceneCamera, "0011_UI", _tmpSpriteName);
	m_CharaIconP2->SetActive(true);
	m_CharaIconP2->SetLocalTranslateVector(Vector2D(1825, 80));
	GameProcess::GetGameObjectManager()->InsertObject(m_CharaIconP2);


	// ==================== ü�¹� ���� ====================
	// Player1�� HP �޺κ�
	UIObject* _tmpPlayerHpBack = new UIObject("Player1_HP", m_SceneCamera, "0011_UI", "HP_P1_Back");
	_tmpPlayerHpBack->SetLocalScaleVector(Vector2D(-1, 1));
	_tmpPlayerHpBack->SetLocalTranslateVector(Vector2D(510, 80));
	_tmpPlayerHpBack->SetLayer(0);
	_PlayerHpBack[0] = _tmpPlayerHpBack;
	// ������Ʈ �Ŵ����� Insert
	GameProcess::GetGameObjectManager()->InsertObject(_tmpPlayerHpBack);

	// Player1�� HP
	UIObject* _PlayerHp = new UIObject("Player1_HP", m_SceneCamera, "0011_UI", "HP_P1_Bar");
	_PlayerHp->SetLocalScaleVector(Vector2D(-1, 1));
	_PlayerHp->SetLocalTranslateVector(Vector2D(510, 80));
	_PlayerHp->SetLayer(1);
	m_PlayerHp.insert({ Player::player1, _PlayerHp });
	// ������Ʈ �Ŵ����� Insert
	GameProcess::GetGameObjectManager()->InsertObject(_PlayerHp);

	// Player2�� HP �޺κ�
	_tmpPlayerHpBack = new UIObject("Player2_HP", m_SceneCamera, "0011_UI", "HP_P2_Back");
	_tmpPlayerHpBack->SetLocalScaleVector(Vector2D(1, 1));
	_tmpPlayerHpBack->SetLocalTranslateVector(Vector2D(1390, 80));
	_tmpPlayerHpBack->SetLayer(0);
	_PlayerHpBack[1] = _tmpPlayerHpBack;
	// ������Ʈ �Ŵ����� Insert
	GameProcess::GetGameObjectManager()->InsertObject(_tmpPlayerHpBack);

	// Player2�� HP
	_PlayerHp = new UIObject("Player2_HP", m_SceneCamera, "0011_UI", "HP_P2_Bar");
	_PlayerHp->SetLocalScaleVector(Vector2D(1, 1));
	_PlayerHp->SetLocalTranslateVector(Vector2D(1390, 80));
	_PlayerHp->SetLayer(1);
	m_PlayerHp.insert({ Player::player2, _PlayerHp });
	// ������Ʈ �Ŵ����� Insert
	GameProcess::GetGameObjectManager()->InsertObject(_PlayerHp);


	// ü�¹� ��ǥ �κ�
	// Player1
	vector<pair<UIObject*, UIObject*>> _tmpTempoVectorP1;
	float _Interval = 139.f;
	for (int i = 0; i < 4; i++)
	{
		float _OriX = 310;
		UIObject* _tmpTempoOff = new UIObject("Tempo_P1_Off_" + to_string(i), m_SceneCamera, "0011_UI", "Tempo_P1_Off");
		_tmpTempoOff->SetActive(true);
		_tmpTempoOff->SetLocalTranslateVector(Vector2D(_OriX + _Interval * i, 80));
		_tmpTempoOff->SetLayer(2);
		// ������Ʈ �Ŵ����� Insert
		GameProcess::GetGameObjectManager()->InsertObject(_tmpTempoOff);

		UIObject* _tmpTempoOn = new UIObject("Tempo_P1_On_" + to_string(i), m_SceneCamera, "0011_UI", "Tempo_P1_On");
		_tmpTempoOn->SetActive(false);
		_tmpTempoOn->SetLocalTranslateVector(Vector2D(_OriX + _Interval * i, 80));
		_tmpTempoOn->SetLayer(2);
		// ������Ʈ �Ŵ����� Insert
		GameProcess::GetGameObjectManager()->InsertObject(_tmpTempoOn);

		_tmpTempoVectorP1.push_back({ _tmpTempoOff, _tmpTempoOn });
	}
	m_HpTempo.insert({ Player::player1, _tmpTempoVectorP1 });

	// Player2
	vector<pair<UIObject*, UIObject*>> _tmpTempoVectorP2;
	for (int i = 0; i < 4; i++)
	{
		float _OriX = 1175;
		UIObject* _tmpTempoOff = new UIObject("Tempo_P2_Off_" + to_string(i), m_SceneCamera, "0011_UI", "Tempo_P2_Off");
		_tmpTempoOff->SetActive(true);
		_tmpTempoOff->SetLocalTranslateVector(Vector2D(_OriX + _Interval * i, 80));
		_tmpTempoOff->SetLayer(2);
		// ������Ʈ �Ŵ����� Insert
		GameProcess::GetGameObjectManager()->InsertObject(_tmpTempoOff);

		UIObject* _tmpTempoOn = new UIObject("Tempo_P2_On_" + to_string(i), m_SceneCamera, "0011_UI", "Tempo_P2_On");
		_tmpTempoOn->SetActive(false);
		_tmpTempoOn->SetLocalTranslateVector(Vector2D(_OriX + _Interval * i, 80));
		_tmpTempoOn->SetLayer(2);
		// ������Ʈ �Ŵ����� Insert
		GameProcess::GetGameObjectManager()->InsertObject(_tmpTempoOn);

		_tmpTempoVectorP2.push_back({ _tmpTempoOff, _tmpTempoOn });
	}
	m_HpTempo.insert({ Player::player2, _tmpTempoVectorP2 });


	// ==================== ���� �ð� ���� ====================
	UIObject* _NumUI;
	for (int i = 0; i < 10; i++)
	{
		// ���� �ð��� 10�� �ڸ� ���� ����
		_NumUI = new UIObject(to_string(i), m_SceneCamera, "0013_Num", "Num" + to_string(i));
		_NumUI->SetActive(false);
		_NumUI->SetLocalTranslateVector(Vector2D(_TimerPosX - 27, _TimerPosY));
		m_RoundTimeUI_TenDigit[i] = _NumUI;
		GameProcess::GetGameObjectManager()->InsertObject(m_RoundTimeUI_TenDigit[i]);

		// ���� �ð��� 1�� �ڸ� ���� ����
		_NumUI = new UIObject(to_string(i), m_SceneCamera, "0013_Num", "Num" + to_string(i));
		_NumUI->SetActive(false);
		_NumUI->SetLocalTranslateVector(Vector2D(_TimerPosX + 27, _TimerPosY));
		m_RoundTimeUI_OneDigit[i] = _NumUI;
		GameProcess::GetGameObjectManager()->InsertObject(m_RoundTimeUI_OneDigit[i]);
	}

#pragma region �¸� ���� ī��Ʈ ����
	// ==================== �¸� ���� ī��Ʈ ���� ====================
	vector<UIObject*> _tmpScoreCntP1;
	vector<UIObject*> _tmpScoreCntP2;
	for (int i = 0; i < m_MaxScoreCount + 1; i++)
	{
		// Player1
		UIObject* _tmpScoreCnt = new UIObject("Score_Count_P1_" + to_string(i), m_SceneCamera, "0011_UI", "Score_Count_" + to_string(i));
		_tmpScoreCnt->SetLocalScaleVector(Vector2D(1, 1));
		_tmpScoreCnt->SetLocalTranslateVector(Vector2D(790, 160));
		// ó������ ���ھ� ���� �͸� ����
		if (i == 0) _tmpScoreCnt->SetActive(true);
		else _tmpScoreCnt->SetActive(false);
		_tmpScoreCntP1.push_back(_tmpScoreCnt);
		// ������Ʈ �Ŵ����� Insert
		GameProcess::GetGameObjectManager()->InsertObject(_tmpScoreCnt);

		// Player2
		_tmpScoreCnt = new UIObject("Score_Count_P2_" + to_string(i), m_SceneCamera, "0011_UI", "Score_Count_" + to_string(i));
		_tmpScoreCnt->SetLocalScaleVector(Vector2D(-1, 1));
		_tmpScoreCnt->SetLocalTranslateVector(Vector2D(1110, 160));
		// ó������ ���ھ� ���� �͸� ����
		if (i == 0) _tmpScoreCnt->SetActive(true);
		else _tmpScoreCnt->SetActive(false);
		_tmpScoreCntP2.push_back(_tmpScoreCnt);
		// ������Ʈ �Ŵ����� Insert
		GameProcess::GetGameObjectManager()->InsertObject(_tmpScoreCnt);
	}
	m_ScoreCountUI.insert({ Player::player1, _tmpScoreCntP1 });
	m_ScoreCountUI.insert({ Player::player2, _tmpScoreCntP2 });
#pragma endregion


#pragma region �޺� ����Ʈ UI ����
	// ==================== �޺� ����Ʈ UI ���� ====================
	UIObject* _ComboUI_Active;
	UIObject* _ComboUI_UnActive;
	// Player1 �޺� ����Ʈ UI ����
	list<pair<UIObject*, UIObject*>> _tmpListP1;
	float _X = 150;
	float _Y = 130;
	float _YInterval = 70;
	float _tmpListRatio = 0.8f;
	for (int i = 0; i < m_ComboListMax; i++)
	{
		// UI Y��ǥ ��ġ ����
		_Y += _YInterval;

		// �޺� ����Ʈ UI(��Ƽ��) ����
		_ComboUI_Active = new UIObject("P1_Combo" + to_string(i) + "_Active", m_SceneCamera, "0011_UI", "ComboList" + to_string(i + 1), 1.f, _tmpListRatio);
		_ComboUI_Active->SetActive(false);
		_ComboUI_Active->SetLocalTranslateVector(Vector2D(_X, _Y));

		// �޺� ����Ʈ UI(���Ƽ��) ����
		_ComboUI_UnActive = new UIObject("P1_Combo" + to_string(i) + "_UnActive", m_SceneCamera, "0011_UI", "ComboList" + to_string(i + 1), 0.5f, _tmpListRatio);
		_ComboUI_UnActive->SetActive(true);
		_ComboUI_UnActive->SetLocalTranslateVector(Vector2D(_X, _Y));

		// �޺� ����Ʈ UI�� Insert
		_tmpListP1.push_back({ _ComboUI_Active, _ComboUI_UnActive });
		// ������Ʈ �Ŵ����� Insert
		GameProcess::GetGameObjectManager()->InsertObject(_ComboUI_Active);
		GameProcess::GetGameObjectManager()->InsertObject(_ComboUI_UnActive);
	}
	m_ComboListUI.insert({ Player::player1, _tmpListP1 });

	// Player2 �޺� ����Ʈ UI ����
	list<pair<UIObject*, UIObject*>> _tmpListP2;
	_X = 1745;
	_Y = 130;
	for (int i = 0; i < m_ComboListMax; i++)
	{
		// UI Y��ǥ ��ġ ����
		_Y += _YInterval;

		// �޺� ����Ʈ UI(��Ƽ��) ����
		_ComboUI_Active = new UIObject("P2_Combo" + to_string(i) + "_Active", m_SceneCamera, "0011_UI", "ComboList" + to_string(i + 1), 1.f, _tmpListRatio);
		_ComboUI_Active->SetActive(false);
		_ComboUI_Active->SetLocalTranslateVector(Vector2D(_X, _Y));

		// �޺� ����Ʈ UI(���Ƽ��) ����
		_ComboUI_UnActive = new UIObject("P2_Combo" + to_string(i) + "_UnActive", m_SceneCamera, "0011_UI", "ComboList" + to_string(i + 1), 0.5f, _tmpListRatio);
		_ComboUI_UnActive->SetActive(true);
		_ComboUI_UnActive->SetLocalTranslateVector(Vector2D(_X, _Y));
		// �޺� ����Ʈ UI�� Insert
		_tmpListP2.push_back({ _ComboUI_Active, _ComboUI_UnActive });
		// ������Ʈ �Ŵ����� Insert
		GameProcess::GetGameObjectManager()->InsertObject(_ComboUI_Active);
		GameProcess::GetGameObjectManager()->InsertObject(_ComboUI_UnActive);
	}
	m_ComboListUI.insert({ Player::player2, _tmpListP2 });
#pragma endregion

#pragma region ���� ���� ���� / ���� ���� UI ����
	// ==================== ���� ���� UI UI ���� ====================
	Vector2D _tmpCurRoundUIPos = Vector2D(960, 350);
	// FIRST
	UIObject* _tmpUIObj = new UIObject("FIRST", m_SceneCamera, "0023_InGameSceneUI", "FIRST");
	_tmpUIObj->SetLayer(999);
	_tmpUIObj->SetLocalTranslateVector(_tmpCurRoundUIPos);
	_tmpUIObj->SetActive(false);
	m_CurRoundUI.push_back(_tmpUIObj);
	// ������Ʈ �Ŵ����� Insert
	GameProcess::GetGameObjectManager()->InsertObject(_tmpUIObj);

	// SECOND
	_tmpUIObj = new UIObject("SECOND", m_SceneCamera, "0023_InGameSceneUI", "SECOND");
	_tmpUIObj->SetLayer(999);
	_tmpUIObj->SetLocalTranslateVector(_tmpCurRoundUIPos);
	_tmpUIObj->SetActive(false);
	m_CurRoundUI.push_back(_tmpUIObj);
	// ������Ʈ �Ŵ����� Insert
	GameProcess::GetGameObjectManager()->InsertObject(_tmpUIObj);

	// THIRD
	_tmpUIObj = new UIObject("THIRD", m_SceneCamera, "0023_InGameSceneUI", "THIRD");
	_tmpUIObj->SetLayer(999);
	_tmpUIObj->SetLocalTranslateVector(_tmpCurRoundUIPos);
	_tmpUIObj->SetActive(false);
	m_CurRoundUI.push_back(_tmpUIObj);
	// ������Ʈ �Ŵ����� Insert
	GameProcess::GetGameObjectManager()->InsertObject(_tmpUIObj);

	// FOURTH
	_tmpUIObj = new UIObject("FOURTH", m_SceneCamera, "0023_InGameSceneUI", "FOURTH");
	_tmpUIObj->SetLayer(999);
	_tmpUIObj->SetLocalTranslateVector(_tmpCurRoundUIPos);
	_tmpUIObj->SetActive(false);
	m_CurRoundUI.push_back(_tmpUIObj);
	// ������Ʈ �Ŵ����� Insert
	GameProcess::GetGameObjectManager()->InsertObject(_tmpUIObj);

	// LAST
	_tmpUIObj = new UIObject("LAST", m_SceneCamera, "0023_InGameSceneUI", "LAST");
	_tmpUIObj->SetLayer(999);
	_tmpUIObj->SetLocalTranslateVector(_tmpCurRoundUIPos);
	_tmpUIObj->SetActive(false);
	m_CurRoundUI.push_back(_tmpUIObj);
	// ������Ʈ �Ŵ����� Insert
	GameProcess::GetGameObjectManager()->InsertObject(_tmpUIObj);


	m_RoundStartUI = new GameObject();
	m_RoundStartUI->SetLayer(100);
	m_RoundStartUI->SetActive(false);
	m_RoundStartUI->AddComponent<StartIcon>();
	m_RoundStartUI->SetLocalTranslateVector(960, 500);
	GameProcess::GetGameObjectManager()->InsertObject(m_RoundStartUI);



	m_RoundEndUI = new GameObject();
	m_RoundEndUI->SetLayer(100);
	m_RoundEndUI->SetActive(false);
	m_RoundEndUI->AddComponent<OutroIcon>();
	m_RoundEndUI->SetLocalTranslateVector(960, 500);
	GameProcess::GetGameObjectManager()->InsertObject(m_RoundEndUI);
	// ==================== ���� ����(KO ��) UI ���� ====================
	//m_RoundEndUI = new UIObject("Round_End", m_SceneCamera, "0011_UI", "0011_UI_Round_End");
	//m_RoundEndUI->SetActive(false);
	//m_RoundEndUI->SetLocalTranslateVector(Vector2D(960, 540));
	//GameProcess::GetGameObjectManager()->InsertObject(m_RoundEndUI);
#pragma endregion

}

void InGameUIManager::SetCharaterIcon(bool _IsShow)
{
	m_CharaIconP1->SetActive(_IsShow);
	m_CharaIconP2->SetActive(_IsShow);
}

void InGameUIManager::SetHPRatio(Player _Player, float _ratio, bool _IsShow)
{
	// ü�¹� �޺κ� ǥ��
	if (_Player == Player::player1)
		_PlayerHpBack[0]->SetActive(_IsShow);
	else
		_PlayerHpBack[1]->SetActive(_IsShow);

	// ü�¹� ǥ��
	m_PlayerHp.at(_Player)->SetActive(_IsShow);
	m_PlayerHp.at(_Player)->GetUIRenderer()->SetFill(_ratio, 1.f);

	// ü�¹� ��ǥ ǥ�� �ʱ�ȭ
	for (auto item : m_HpTempo.at(_Player))
	{
		item.first->SetActive(_IsShow);
		item.second->SetActive(false);
	}

	// ü�¹� ��ǥ ����(���� ü�� ������ ���� ǥ�ð� �޶���)
	if (_ratio < 0.8f)
	{
		pair<UIObject*, UIObject*> _tmp;
		if (_Player == Player::player1) _tmp = m_HpTempo.at(_Player).at(0);
		else _tmp = m_HpTempo.at(_Player).at(3);

		_tmp.first->SetActive(false);
		_tmp.second->SetActive(true);
	}
	if (_ratio < 0.6f)
	{
		pair<UIObject*, UIObject*> _tmp;
		if (_Player == Player::player1) _tmp = m_HpTempo.at(_Player).at(1);
		else _tmp = m_HpTempo.at(_Player).at(2);

		_tmp.first->SetActive(false);
		_tmp.second->SetActive(true);
	}
	if (_ratio < 0.4f)
	{
		pair<UIObject*, UIObject*> _tmp;
		if (_Player == Player::player1) _tmp = m_HpTempo.at(_Player).at(2);
		else _tmp = m_HpTempo.at(_Player).at(1);

		_tmp.first->SetActive(false);
		_tmp.second->SetActive(true);
	}
	if (_ratio < 0.2f)
	{
		pair<UIObject*, UIObject*> _tmp;
		if (_Player == Player::player1) _tmp = m_HpTempo.at(_Player).at(3);
		else _tmp = m_HpTempo.at(_Player).at(0);

		_tmp.first->SetActive(false);
		_tmp.second->SetActive(true);
	}
}

void InGameUIManager::SetRoundTimeUI(int _CurRoundTime, bool _IsShow /*= true*/)
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

void InGameUIManager::SetRoundCountUI(Player _Player, int _playerScore, bool _IsShow /*= true*/)
{
	// �¸� ���� ���� �´� ��������Ʈ�� Active�Ѵ�
	int i = 0;
	for (auto item : m_ScoreCountUI.at(_Player))
	{
		if (i == _playerScore) item->SetActive(_IsShow);
		else  item->SetActive(false);
		i++;
	}
}

void InGameUIManager::SetComboList(Player _Player, bool _Combo[] /*= nullptr*/)
{
	// �޺� ��� ���� ���ڰ� null�� ����, �޺� ����Ʈ ��ü�� ǥ������ ����
	if (_Combo == nullptr)
	{
		auto _ComList = (*m_ComboListUI.find(_Player)).second;

		for (auto item : _ComList)
		{
			item.first->SetActive(false);
			item.second->SetActive(false);
		}
	}
	else
	{
		int cnt = 0;
		auto _ComList = (*m_ComboListUI.find(_Player)).second;

		for (auto item : _ComList)
		{
			// ����� �޺��� ���
			if (_Combo[cnt] == true)
			{
				item.first->SetActive(true);
				item.second->SetActive(false);
			}
			else
			{
				item.first->SetActive(false);
				item.second->SetActive(true);
			}
			cnt++;
		}
	}
}

void InGameUIManager::SetCurRoundUI(int _CurRound, bool _IsShow /*= true*/)
{
	//_CurRound = _CurRound - 1; // ���� ���带 ���� ������ �°� ����

	int cnt = 0;
	for (auto item : m_CurRoundUI)
	{
		if (cnt == _CurRound) item->SetActive(_IsShow);
		else item->SetActive(false);
		cnt++;
	}
}

void InGameUIManager::SetCurRoundUI(bool _IsShow /*= true*/)
{
	for (size_t i = 0; i < m_CurRoundUI.size(); i++)
		SetCurRoundUI(i, _IsShow);
}

void InGameUIManager::PlayRoundEndUI(int _PlayerIndex)
{
	// todo: ���ҽ� ������ ����
	//m_RoundEndUI->SetActive(_IsShow);
	switch (_PlayerIndex)
	{
	case 1:
		GetSoundManager()->Play("Sh_On", IPlayMode::Effect);
		break;
	case 2:
		GetSoundManager()->Play("Sh_Tw", IPlayMode::Effect);
		break;
	default:
		break;
	}
	
	m_RoundEndUI->GetComponent<OutroIcon>()->Play(_PlayerIndex);
}

void InGameUIManager::PlayRoundStartUI()
{
	m_RoundStartUI->GetComponent<StartIcon>()->Play();
}
