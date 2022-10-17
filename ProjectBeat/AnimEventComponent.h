#pragma once
#include "..\Engine\Component.h"

class CharactorInfoComponent;
class CommandComponent;
class StateComponent;
class AnimEventComponent :
	public Component
{
public:
	AnimEventComponent(GameObject* _GameObject);
	virtual ~AnimEventComponent() {}

	CharactorInfoComponent* m_CharInfo;
	CommandComponent* m_Cmd;
	StateComponent* m_state;

	virtual void SetName() { m_Name = "AnimEventComponent"; }

	virtual void Update() {};

	void DmgOn();
	void InputOff();


	void SendDmg();

	void SetIdle();
	
	void EndAnim();
	void PlayPunchHitSound();
	void PlayKickHitSound();
	void SpawnHitParticle(int index);
};

