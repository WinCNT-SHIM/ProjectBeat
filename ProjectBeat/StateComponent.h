#pragma once
#include "..\Engine\Component.h"
#include "..\Engine\animator.h"


class StateComponent :
	public Component
{
public:
	StateComponent(GameObject* _GameObject);
	virtual ~StateComponent() {}
	virtual void SetName() { m_Name = "StateComponent"; }
	virtual void Update();
private:
	int curstate = 0;
	int AttackIndex = 0;
public:
	enum State {
		STATE_IDLE,
		STATE_MOVEFW,
		STATE_MOVEBK,
		STATE_JUMP,
		STATE_ATTACK,
		STATE_GUARD,
		STATE_HIT,
		STATE_DEATH
	};
	void Init();

	void ChangeState(int _nextState);
	bool IsMovable();
	bool IsAttackable();
	int GetState() { return curstate; }
	void sendAnimState();

	void setIdle();

	void SetAttackState(int index);

	void debugState();

	Animator* _animator;

	void PlayStartAnim();

	void PlayWinAnim();

	private:
	string m_priorSprite;

};

