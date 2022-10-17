#pragma once

class CharSelectObject;

class SeletionComponents : public Component
{
public:
	SeletionComponents(GameObject* _GameObject);
	virtual ~SeletionComponents();

private:

	Vector2D m_Pos[4]; //�Ǳ���� ��ġ
	CharSelectObject* m_CharSelectObject[4]; // �Ǳ��.
	SpriteObject* m_SelectCursor; // ĳ���� ���� Ŀ��
	SpriteObject* m_SelectCursor2; // Player2 ĳ���� ���� Ŀ��

	SpriteObject* m_illustration; // �������� �Ϸ���Ʈ
	SpriteObject* m_illustration2; // Player2 �������� �Ϸ���Ʈ
	SpriteObject* m_Idle; // �������� Idle
	
	int m_NowSelection;
	int m_Player1Slection;

	bool isPlayer1Select;
	bool SelectCheck;
	bool m_isFinal;
	
	int m_PriorSelection;

	// ���� �е� ���� Ÿ�̸�
	float m_VibrationTimer = 0;
public:

	virtual void Start();
	virtual void Update() override; // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render(D2DEngine* _pEngine) {}; //��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����

	//�浹 ����
	virtual void OnEnterCollider(GameObject* Other) {};
	//�浹 ��
	virtual void OnStayCollider(GameObject* Other) {};
	//�浹 ��
	virtual void OnExitCollider(GameObject* Other) {};




	virtual void SetName() { m_Name = "SeletionComponents"; }
};

