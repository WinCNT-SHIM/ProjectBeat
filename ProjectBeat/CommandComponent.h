#pragma once
#include "..\Engine\Component.h"
#include <string>
#include "CharactorInfoComponent.h"
#include "StateComponent.h"


class Animator;

class CommandComponent :
	public Component
{
public:
	CommandComponent(GameObject* _GameObject);
	virtual ~CommandComponent() {};
	virtual void SetName() { m_Name = "CommandComponent"; }

private:
	bool IsPunch;
	bool firstHit = true;
	bool commandSuccess[5] = { false };
	bool CanInput = true;
	bool AtkInput = false;
	std::string curClip;
		
public:
	int charindex;
	Animator* _animator;
	StateComponent* _state;
	int comboCount = 0;

	unsigned int CommandCount = 0;
	void sendAnim();
	void setPunch(bool pun);



	void InputOff();
	void EndAnim();

	bool getPunch() { return IsPunch; }
	bool getFirstHit() { return AtkInput; }
	bool getCanInput() { return CanInput; }
	
	
	void setFirstHit(bool on) { firstHit = on; }

	void checkCombo();


	void SendHit(float dmg);

	void reset();
	void CommandSuccessReset();

	void CheckFirst();
	virtual void Update();
};
