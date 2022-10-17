#pragma once

class CharSelectObject;

class SeletionComponents : public Component
{
public:
	SeletionComponents(GameObject* _GameObject);
	virtual ~SeletionComponents();

private:

	Vector2D m_Pos[4]; //악기들의 위치
	CharSelectObject* m_CharSelectObject[4]; // 악기들.
	SpriteObject* m_SelectCursor; // 캐릭터 선택 커서
	SpriteObject* m_SelectCursor2; // Player2 캐릭터 선택 커서

	SpriteObject* m_illustration; // 선택중인 일러스트
	SpriteObject* m_illustration2; // Player2 선택중인 일러스트
	SpriteObject* m_Idle; // 선택중인 Idle
	
	int m_NowSelection;
	int m_Player1Slection;

	bool isPlayer1Select;
	bool SelectCheck;
	bool m_isFinal;
	
	int m_PriorSelection;

	// 게임 패드 진동 타이머
	float m_VibrationTimer = 0;
public:

	virtual void Start();
	virtual void Update() override; // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render(D2DEngine* _pEngine) {}; //모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더

	//충돌 시작
	virtual void OnEnterCollider(GameObject* Other) {};
	//충돌 중
	virtual void OnStayCollider(GameObject* Other) {};
	//충돌 끝
	virtual void OnExitCollider(GameObject* Other) {};




	virtual void SetName() { m_Name = "SeletionComponents"; }
};

