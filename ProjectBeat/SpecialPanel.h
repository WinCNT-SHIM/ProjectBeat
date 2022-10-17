#pragma once
class SpecialPanel : public Component
{
public:
	SpecialPanel(GameObject* _GameObject);
	virtual ~SpecialPanel();

private:
	Vector2D m_Startpos; // ��� ����
	Vector2D m_EndPos; // ���� ����
	Vector2D m_DeltaPos; // �̵���

	bool m_isArrive = false;
	bool m_UseBeatBurst = false;

	bool m_isPlayer1First = false;

	float m_Timer = 0;
public:
	void Init(Vector2D _Startpos, Vector2D _Endpos, float _Speed, bool _isPlayer1First);
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void SetName() { m_Name = "SpecialPanel"; }
};

