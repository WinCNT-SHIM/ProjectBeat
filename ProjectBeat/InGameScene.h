#pragma once

class Character;
class CameraObject; // ī�޶�
class UIObject; // UI
//class CTime; // ���� �ð�
class InGameUIManager; // �ΰ��� UI �Ŵ��� 

class InGameScene : public IScene
{
	// ������ �� �ʱ�ȭ
public:
	InGameScene();
	~InGameScene();

	// ����
public:
	Character* _MainBody;
	Character* _MainBody2;
private:
	// ��� ������Ʈ
	SpriteObject* m_Background;
	// �ΰ��� UI �Ŵ���
	InGameUIManager* m_InGameUIManager;
	// ���� ���� ����
	bool m_isRoundEnd = false;
	// ī�޶� ������Ʈ
	CameraObject* m_SceneCamera;
	// ���� �ð� �� UI
	int const m_MaxRoundTime = 60;
	float m_DeltaTime = 0;
	int m_CurRoundTime = m_MaxRoundTime;

	// ���� ������ ������
	float m_EndRoundTimer = 0;

	// ���� ó�� ������ �� ������
	float m_StartTimer = 0;
	float m_FirstRoundTimer = 0;

	bool m_isStart = false;
	bool m_isStart2 = false;

	bool m_isFirstRound1 = false;
	bool m_isFirstRound2 = false;

	bool m_RoundShout = true;
	bool m_RoundStart = true;

	//
	GameObject* m_MetroNome; //��Ʈ�γ�

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



	// �Լ�
public:
	void Init(int _Player1Index, int _Player2Index);
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(D2DEngine* m_Engine) override;
};

