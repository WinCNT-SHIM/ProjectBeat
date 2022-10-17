#pragma once
#include "..\Engine\Component.h"
enum class IntroState
{
	IntroMain,
	ComboList,
	Credit
};

class GameObject;

class IntroCtrl :
    public Component
{
public:
    IntroCtrl(GameObject* gameObject);
    virtual ~IntroCtrl();

	// Ŀ�� ��ǥ
	Vector2D m_CursorPos;
	// Ŀ�� �̵� ����
	int m_MenuCnt = 0;
	const int m_MenuMax = 3;
	const float m_CursorMoveLen = 123.0f;

	IntroState m_CurrState = IntroState::IntroMain;
	IntroState m_NextState = IntroState::IntroMain;
	bool isChanging = true;

	bool isFadeOut = true;
	bool isFadeIn = false;

	GameObject* m_IntroObj;
	GameObject* m_CreditObj;
	GameObject* m_ComboObj;
	GameObject* m_Cursor;

	float m_FadeAlpha = 0.f;
	float m_FadeSpeed = 0.2f;

	bool m_Init = true;
	bool m_CursorOn = false;

	// ���� �е� ���� Ÿ�̸�
	float m_VibrationTimer = 0;
public:
	void Init(GameObject* introParent, GameObject* creditParent, GameObject* comboParent, GameObject* cursorObj, Vector2D cursorPos);
    virtual void Update();
    virtual void SetName() {m_Name = "introCtrl"; }

public:
	void ChangeIntroState(int idx);

private:
	bool FadeOut(GameObject* parent);
	bool FadeIn(GameObject* parent);
	void FadeObj(GameObject* parent);
};

