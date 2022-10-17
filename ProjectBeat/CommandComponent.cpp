#include "GamePCH.h"
#include "CommandComponent.h"
#include "CharactorInfoComponent.h"
#include "Animator.h"
#include "StateComponent.h"
#include "ParticleManager.h"

CommandComponent::CommandComponent(GameObject* _GameObject) :
	Component(_GameObject)
{
	IsPunch = true;
	_animator = GetComponent<Animator>();
	_state = GetComponent<StateComponent>();
	charindex = GetComponent<CharactorInfoComponent>()->CharIndex;

}

void CommandComponent::sendAnim()
{
	CanInput = true;

	if (IsPunch)
	{

		_animator->SetTrigger("Punch");
		CommandCount += 0;
	}
	else
	{

		_animator->SetTrigger("Kick");
		CommandCount += 1;
	}
	_state->ChangeState(4);
	AtkInput = false;
	checkCombo();
}

void CommandComponent::setPunch(bool pun)
{
	if (_state->IsAttackable())
	{
		if (CanInput == true)
		{
			CanInput = false;
			if (pun == true)
			{
				IsPunch = true;
			}
			else
			{
				IsPunch = false;
			}
			CheckFirst();

		}

	}


}


void CommandComponent::CheckFirst()
{
	curClip = _animator->_animatorController->_currAnimationNode->_animationClipName;
	if (_state->GetState() == 4)
	{


		if (curClip == "idle" || curClip == "BackStep" || curClip == "Run")
		{
			reset();
		}
		else
		{
			AtkInput = true;
		}

	}
	else if (_state->GetState() == 0 || _state->GetState() == 1 || _state->GetState() == 2)
	{

		if (curClip != "idle" && curClip != "BackStep" && curClip != "Run")
		{
			reset();
		}
		else
		{
			sendAnim();
		}


	}
	else if (_state->GetState() == 3)
	{
		CanInput = true;
		AtkInput = false;
		comboCount = 0;
		CommandCount = 0;
	}

}


void CommandComponent::InputOff()
{

	if (AtkInput == true)
	{
		sendAnim();
	}

}

//콤보 입력 없이 공격 애님이 끝났을 시 첫콤 그리고 firtHit 초기화 하려고 했긴 했는데 이거 Hit 당하면 어떻하지
void CommandComponent::EndAnim()
{
	reset();

}


void CommandComponent::checkCombo()
{
	comboCount += 1;
	if (comboCount >= 5)
	{
		switch (CommandCount)
		{

		case 0://PPPPP
			commandSuccess[0] = true;
			//DEBUG_PRINT("1 Success\n");
			GameManager::Instance()->SetComboList(m_GameObject->GetComponent<CharactorInfoComponent>()->playerIndex, commandSuccess);
			break;

		case 9://PKPPK
			commandSuccess[2] = true;
			//DEBUG_PRINT("3 Success\n");
			GameManager::Instance()->SetComboList(m_GameObject->GetComponent<CharactorInfoComponent>()->playerIndex, commandSuccess);
			break;

		case 13://PKKPK
			commandSuccess[3] = true;
			//DEBUG_PRINT("4 Success\n");
			GameManager::Instance()->SetComboList(m_GameObject->GetComponent<CharactorInfoComponent>()->playerIndex, commandSuccess);
			break;

		case 19://KPPKK
			commandSuccess[1] = true;
			//DEBUG_PRINT("2 Success\n");
			GameManager::Instance()->SetComboList(m_GameObject->GetComponent<CharactorInfoComponent>()->playerIndex, commandSuccess);
			break;
		default:
			break;
		}
		comboCount = 0;
		CommandCount = 0;
		GetComponent<CharactorInfoComponent>()->StrongHit = true;
		int i = 0;
		while (commandSuccess[i++])
		{
			if (i == 4)
			{
				CharactorInfoComponent* _Temp = m_GameObject->GetComponent<CharactorInfoComponent>();
				_Temp->SetSpecial(true);

				break;
			}
		}
	}
	else
	{
		CommandCount = CommandCount << 1;
		//DEBUG_PRINT("shift\n");
	}

}

void CommandComponent::SendHit(float dmg)
{
	GetComponent<CharactorInfoComponent>()->ApplyDmgtoTarget(dmg);
}


void CommandComponent::reset()
{

	_state->ChangeState(0);
	CanInput = true;
	AtkInput = false;
	comboCount = 0;
	CommandCount = 0;



}

void CommandComponent::CommandSuccessReset()
{
	for (int i = 0; i < 5; i++)
	{
		commandSuccess[i] = false;
	}
	GameManager::Instance()->SetComboList(m_GameObject->GetComponent<CharactorInfoComponent>()->playerIndex, commandSuccess);
}

void CommandComponent::Update()
{

}

