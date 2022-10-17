#pragma once

//using GAMEMANAGER = GameManager::Instance()

class Character;
class InGameUIManager;
class InGameScene;
/// <summary>
/// 이원택 22.02.19
/// 게임 매니저
/// 게임 상태 이벤트 등을 처리해줄 매니저
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
	/// 게임 퍼즈 변수
	/// 게임 중단에 영향을 받고 싶은 모든 오브젝트의 업데이트에
	/// 이것이 참이면 리턴하도록 추가
	/// </summary>
	bool gamePause = false;

private:
	// 이닛때 캐릭터 숏컷 혹은 게임매니저에서 오브젝트 생성 할 수도 있음 추후 논의
	Character* player1 = nullptr;
	Character* player2 = nullptr;

	// 인게임 UI 매니저의 숏컷
	InGameUIManager* m_InGameUIManager;
	// 현재 인게임 씬
	InGameScene* m_NowInGameScene = nullptr;
	// 라운드 시간
	float m_CurRoundTime;
	float m_MaxRoundTime;

	int _maxRound = 3;
	int _currRound = 0;

	int _playerScore[2] = { 0, 0 };

	// 라운드 종료 플래그
	bool _isRoundEnd = false;
	// 게임 종료 플래그
	bool _isGameEnd = false;

	// UI 변경 플래그
	bool _IsUIUpdated = false;

	/// <summary>
	/// 게임 속도 관련 변수
	/// </summary>
	float _curBpm = 120;
	/// <summary>
	/// 기준이 되는 속도 / Bpm
	/// 기준 bpm / 현재 bpm = 게임 속도?
	/// </summary>
	float _standardBpm = 120;
public:
	GameObject* m_Option = nullptr;
public:
	/// <summary>
	/// 초기화
	/// </summary>
	void Init(Character* _player1, Character* _player2, InGameUIManager* _InGameUIManager, InGameScene* _NowInGameScene);

	/// <summary>
	/// 캐릭터 셋팅
	/// </summary>
	/// <param name="playerIdx">플레이어 번호</param>
	/// <param name="charaterIdx">해당 플레이어가 고른 캐릭터</param>
	void SettingCharater(int playerIdx, int charaterIdx);

	/// <summary>
	/// 라운드 시작
	/// </summary>
	void StartRound();

	/// <summary>
	/// 라운드 종료 이벤트
	/// </summary>
	/// <param name="playerIdx">진 플레이어 idx</param>
	void EndRound(int playerIdx);

	/// <summary>
	/// 라운드 종료(시간 초과) 이벤트
	/// </summary>
	void EndRound();

	/// <summary>
	/// 게임 종료 후 재시작
	/// </summary>
	//void Replay();

	/// <summary>
	/// 게임 종료 판정
	/// </summary>
	/// <returns></returns>
	bool CheckRoundEnd() { return _isRoundEnd; };

	/// <summary>
	/// 게임 종료 판정
	/// </summary>
	/// <returns></returns>
	bool CheckGameEnd() { return _isGameEnd; };

	/// <summary>
	/// 게임 종료되면 게임 엔딩 화면으로 이동
	/// </summary>
	void GoToEnding();

	/// <summary>
	/// 게임 일시 정지/ 재개
	/// </summary>
	void SetPause(bool _Pause);
	bool GetPause() { return gamePause; }

	void Pause();
	void Resume();

	void ReturnToLobby();
	/// <summary>
	/// bpm을 설정
	/// </summary>
	void SetBpm(int __bpm);

	/// <summary>
	/// 기준 bpm / 현재 bpm 으로 속도 계산
	/// </summary>
	float GetSpeed();

	/// <summary>
	/// 체력바 UI를 조절한다
	/// </summary>
	void SetHpUI(int playerIdx, float _ratio, bool _IsShow = true);

	/// <summary>
	/// 라운드의 시간을 조절한다
	/// </summary>
	/// <param name="_CurRoundTime"></param>
	/// <param name="_IsShow"></param>
	void SetRoundTime(int _CurRoundTime, bool _IsShow = true);

	// 비트 버스트 사용시 호출하는 함수.
	void PlayBeatBurst(bool _isPlayer1First);

	// 비트 버스트 씬 변경용.
	void ChangeBeatBurstScene(bool _isPlayer1First);
	// 지금이 몇번째 라운드인지
	int GetRound() { return _currRound; }

	float GetStdBpm() { return _standardBpm; }
	float GetCurBpm() { return _curBpm; }

	/// 인게임 필살기 패널 Onoff
	void SetSpecialPanel(bool _IsPlayer1, bool _IsOnOff);	/// <summary>
	/// 콤보 리스트 UI를 조정하는 함수
	/// </summary>
	void SetComboList(int _Player, bool _Combo[] /*= nullptr*/);
	/// <summary>
	/// 현재 라운드 UI를 끄고 켜는 함수
	/// </summary>
	/// <param name="_CurRound">현재 라운드</param>
	void SetCurRoundUI(bool _IsShow = true);

	bool GetisStart();

	Character* GetPlayer1() { return player1; }
	Character* GetPlayer2() { return player2; }
};

