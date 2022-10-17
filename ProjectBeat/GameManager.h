#pragma once

//using GAMEMANAGER = GameManager::Instance()

class Character;
class InGameUIManager;
class InGameScene;
/// <summary>
/// �̿��� 22.02.19
/// ���� �Ŵ���
/// ���� ���� �̺�Ʈ ���� ó������ �Ŵ���
/// </summary>
class GameManager
{
public:
	GameManager();
	~GameManager();

private:
	static GameManager* _instance;

public:
	static GameManager* Instance();
	static void Release();

private:
	/// <summary>
	/// ���� ���� ����
	/// ���� �ߴܿ� ������ �ް� ���� ��� ������Ʈ�� ������Ʈ��
	/// �̰��� ���̸� �����ϵ��� �߰�
	/// </summary>
	bool gamePause = false;

private:
	// �̴ֶ� ĳ���� ���� Ȥ�� ���ӸŴ������� ������Ʈ ���� �� ���� ���� ���� ����
	Character* player1 = nullptr;
	Character* player2 = nullptr;

	// �ΰ��� UI �Ŵ����� ����
	InGameUIManager* m_InGameUIManager;
	// ���� �ΰ��� ��
	InGameScene* m_NowInGameScene = nullptr;
	// ���� �ð�
	float m_CurRoundTime;
	float m_MaxRoundTime;

	int _maxRound = 3;
	int _currRound = 0;

	int _playerScore[2] = { 0, 0 };

	// ���� ���� �÷���
	bool _isRoundEnd = false;
	// ���� ���� �÷���
	bool _isGameEnd = false;

	// UI ���� �÷���
	bool _IsUIUpdated = false;

	/// <summary>
	/// ���� �ӵ� ���� ����
	/// </summary>
	float _curBpm = 120;
	/// <summary>
	/// ������ �Ǵ� �ӵ� / Bpm
	/// ���� bpm / ���� bpm = ���� �ӵ�?
	/// </summary>
	float _standardBpm = 120;
public:
	GameObject* m_Option = nullptr;
public:
	/// <summary>
	/// �ʱ�ȭ
	/// </summary>
	void Init(Character* _player1, Character* _player2, InGameUIManager* _InGameUIManager, InGameScene* _NowInGameScene);

	/// <summary>
	/// ĳ���� ����
	/// </summary>
	/// <param name="playerIdx">�÷��̾� ��ȣ</param>
	/// <param name="charaterIdx">�ش� �÷��̾ �� ĳ����</param>
	void SettingCharater(int playerIdx, int charaterIdx);

	/// <summary>
	/// ���� ����
	/// </summary>
	void StartRound();

	/// <summary>
	/// ���� ���� �̺�Ʈ
	/// </summary>
	/// <param name="playerIdx">�� �÷��̾� idx</param>
	void EndRound(int playerIdx);

	/// <summary>
	/// ���� ����(�ð� �ʰ�) �̺�Ʈ
	/// </summary>
	void EndRound();

	/// <summary>
	/// ���� ���� �� �����
	/// </summary>
	//void Replay();

	/// <summary>
	/// ���� ���� ����
	/// </summary>
	/// <returns></returns>
	bool CheckRoundEnd() { return _isRoundEnd; };

	/// <summary>
	/// ���� ���� ����
	/// </summary>
	/// <returns></returns>
	bool CheckGameEnd() { return _isGameEnd; };

	/// <summary>
	/// ���� ����Ǹ� ���� ���� ȭ������ �̵�
	/// </summary>
	void GoToEnding();

	/// <summary>
	/// ���� �Ͻ� ����/ �簳
	/// </summary>
	void SetPause(bool _Pause);
	bool GetPause() { return gamePause; }

	void Pause();
	void Resume();

	void ReturnToLobby();
	/// <summary>
	/// bpm�� ����
	/// </summary>
	void SetBpm(int __bpm);

	/// <summary>
	/// ���� bpm / ���� bpm ���� �ӵ� ���
	/// </summary>
	float GetSpeed();

	/// <summary>
	/// ü�¹� UI�� �����Ѵ�
	/// </summary>
	void SetHpUI(int playerIdx, float _ratio, bool _IsShow = true);

	/// <summary>
	/// ������ �ð��� �����Ѵ�
	/// </summary>
	/// <param name="_CurRoundTime"></param>
	/// <param name="_IsShow"></param>
	void SetRoundTime(int _CurRoundTime, bool _IsShow = true);

	// ��Ʈ ����Ʈ ���� ȣ���ϴ� �Լ�.
	void PlayBeatBurst(bool _isPlayer1First);

	// ��Ʈ ����Ʈ �� �����.
	void ChangeBeatBurstScene(bool _isPlayer1First);
	// ������ ���° ��������
	int GetRound() { return _currRound; }

	float GetStdBpm() { return _standardBpm; }
	float GetCurBpm() { return _curBpm; }

	/// �ΰ��� �ʻ�� �г� Onoff
	void SetSpecialPanel(bool _IsPlayer1, bool _IsOnOff);	/// <summary>
	/// �޺� ����Ʈ UI�� �����ϴ� �Լ�
	/// </summary>
	void SetComboList(int _Player, bool _Combo[] /*= nullptr*/);
	/// <summary>
	/// ���� ���� UI�� ���� �Ѵ� �Լ�
	/// </summary>
	/// <param name="_CurRound">���� ����</param>
	void SetCurRoundUI(bool _IsShow = true);

	bool GetisStart();

	Character* GetPlayer1() { return player1; }
	Character* GetPlayer2() { return player2; }
};

