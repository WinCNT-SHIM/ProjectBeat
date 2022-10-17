#pragma once
class HitEf : public Effect
{
public:
	HitEf(GameObject* _GameObject);
	~HitEf();

private:

public:
	virtual void Play(bool _isPlayer1, int _CharIndex, float _Damage = 0);
	virtual void Start();
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void SetName() { m_Name = "HitEf"; }

};

