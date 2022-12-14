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
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void SetName() { m_Name = "HitEf"; }

};
