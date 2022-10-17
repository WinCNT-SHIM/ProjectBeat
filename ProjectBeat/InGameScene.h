#pragma once

class Character;
class CameraObject; // 카메라
class UIObject; // UI
//class CTime; // 라운드 시간
class InGameUIManager; // 인게임 UI 매니저 

class InGameScene : public IScene
{
	// 생성자 및 초기화
public:
	InGameScene();
	~InGameScene();

	// 변수
public:
	Character* _MainBody;
	Character* _MainBody2;
private:
	// 배경 오브젝트
	SpriteObject* m_Background;
	// 인게임 UI 매니저
	InGameUIManager* m_InGameUIManager;
	// 라운드 종료 여부
	bool m_isRoundEnd = false;
	// 카메라 오브젝트
	CameraObject* m_SceneCamera;
	// 라운드 시간 및 UI
	int const m_MaxRoundTime = 60;
	float m_DeltaTime = 0;
	int m_CurRoundTime = m_MaxRoundTime;

	// 라운드 끝나고 딜레이
	float m_EndRoundTimer = 0;

	// 게임 처음 시작할 때 딜레이
	float m_StartTimer = 0;
	float m_FirstRoundTimer = 0;

	bool m_isStart = false;
	bool m_isStart2 = false;

	bool m_isFirstRound1 = false;
	bool m_isFirstRound2 = false;

	bool m_RoundShout = true;
	bool m_RoundStart = true;

	//
	GameObject* m_MetroNome; //메트로놈

	GameObject* m_PauseObject;

	GameObject* m_P1SpecialPanel;
	GameObject* m_P2SpecialPanel;
public:
	void ReStart();
	void SetSpecialPanel(bool _IsPlayer1, bool _IsOnOff);
	bool GetisStart() { return m_isStart2; }
private:
	void StartDelay();
	void PauseKeyUpdate();
	void RoundTimer();
	void SpeedGimmick();
	void RoundCheck();



	// 함수
public:
	void Init(int _Player1Index, int _Player2Index);
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(D2DEngine* m_Engine) override;
};

