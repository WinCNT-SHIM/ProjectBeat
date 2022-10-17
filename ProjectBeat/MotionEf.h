#pragma once

class MotionEf : public Effect
{
public:
	MotionEf(GameObject* _GameObject);
	~MotionEf();

private:
	string m_SpriteName;
	string m_SheetName;
public:
	virtual void Play(bool _isPlayer1, int _CharIndex, float _Damage = 0);
	virtual void Play(bool _isPlayer1, int _CharIndex, string _SpriteName);
	virtual void Start();
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void SetName() { m_Name = "HitEf"; }

};
