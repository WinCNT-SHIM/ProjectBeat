#include "GamePCH.h"
#include "AnimEventComponent.h"
#include "CommandComponent.h"
#include "StateComponent.h"
#include "CharactorInfoComponent.h"
#include "../SoundLib/ISoundManager.h"



AnimEventComponent::AnimEventComponent(GameObject* _GameObject) :Component(_GameObject)
{
	m_CharInfo = GetComponent<CharactorInfoComponent>();
	m_Cmd = GetComponent<CommandComponent>();
	m_state = GetComponent<StateComponent>();
}




void AnimEventComponent::DmgOn()
{
	m_CharInfo->SetDamageAble(true);
}

void AnimEventComponent::InputOff()
{
	m_Cmd->InputOff(); 
	m_CharInfo->SetDamageAble(false);

}

void AnimEventComponent::SendDmg()
{

}

void AnimEventComponent::SetIdle()
{
	m_state->ChangeState(0);
}

void AnimEventComponent::EndAnim()
{
	m_Cmd->EndAnim();
	
}

void AnimEventComponent::PlayPunchHitSound()
{
}

void AnimEventComponent::PlayKickHitSound()
{
}

void AnimEventComponent::SpawnHitParticle(int index)
{
}
