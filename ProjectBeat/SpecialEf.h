#pragma once

class SpecialEf : public Effect
{
public:
	SpecialEf(GameObject* _GameObject);
	virtual ~SpecialEf();

private:
	bool m_isCol;

public:
	//����Ʈ �÷���.
	virtual void Play(bool _isPlayer1, int _CharIndex , float _Damage = 0);
	virtual void Start();
	virtual void Update() ; // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void SetName() {m_Name = "SpecialEf" ;}

	virtual void OnEnterCollider(GameObject* Other);
};

