#pragma once
class SpecialPanel : public Component
{
public:
	SpecialPanel(GameObject* _GameObject);
	virtual ~SpecialPanel();

private:
	Vector2D m_Startpos; // 출발 지점
	Vector2D m_EndPos; // 도착 지점
	Vector2D m_DeltaPos; // 이동량

	bool m_isArrive = false;
	bool m_UseBeatBurst = false;

	bool m_isPlayer1First = false;

	float m_Timer = 0;
public:
	void Init(Vector2D _Startpos, Vector2D _Endpos, float _Speed, bool _isPlayer1First);
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void SetName() { m_Name = "SpecialPanel"; }
};

