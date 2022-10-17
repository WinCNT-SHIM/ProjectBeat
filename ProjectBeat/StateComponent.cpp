#include "GamePCH.h"
#include "StateComponent.h"
#include "Animator.h"
#include "CharactorInfoComponent.h"
#include "ParticleManager.h"
#include "CommandComponent.h"


void StateComponent::ChangeState(int _nextState)
{
	curstate = _nextState;
	sendAnimState();
}

void StateComponent::sendAnimState()
{


	switch (curstate)
	{
	case STATE_IDLE:
		_animator->SetBool("Run", false);
		_animator->SetBool("Back", false);
		_animator->SetBool("Guard", false);

		break;
	case STATE_MOVEFW:
		_animator->SetBool("Run", true);
		break;
	case STATE_MOVEBK:
		_animator->SetBool("Back", true);
		break;
	case STATE_JUMP:
		_animator->SetTrigger("Jump");
		break;
	case STATE_ATTACK:
		break;
	case STATE_GUARD:
		_animator->SetBool("Guard", true);
		break;
	case STATE_HIT:
		_animator->SetTrigger("hit");
		break;
	case STATE_DEATH:
		_animator->SetTrigger("Death");
		break;
	}
}
void StateComponent::setIdle()
{
	_animator->SetSpeed(1);
	_animator->SetInteger("Start", 5);
	_animator->SetInteger("Win", 5);
	_animator->SetTrigger("New");
	GetComponent<CommandComponent>()->reset();
	
}

void StateComponent::SetAttackState(int index)
{

}

void StateComponent::debugState()
{

}

void StateComponent::PlayStartAnim()
{
	_animator->SetSpeed(0.3f);
	int _index = GetComponent<CharactorInfoComponent>()->CharIndex;
	_animator->SetTrigger("New");
	_animator->SetInteger("Start", _index);
}

void StateComponent::PlayWinAnim()
{
	_animator->SetSpeed(0.3f);
	int _index = GetComponent<CharactorInfoComponent>()->CharIndex;
	_animator->SetTrigger("New");
	_animator->SetInteger("Win", _index);
}


StateComponent::StateComponent(GameObject* _GameObject) :Component(_GameObject)
{
	_animator = m_GameObject->GetComponent<Animator>();
}

void StateComponent::Update()
{
	if (GetState() == State::STATE_ATTACK)
	{
		string _AnimationClipName = _animator->_animatorController->_currAnimationNode->_animationClipName;

		if (m_priorSprite == _AnimationClipName) return;

		m_priorSprite = _AnimationClipName;

		if (*_AnimationClipName.c_str() == 'P' || *_AnimationClipName.c_str() == 'K')
		{
			CharactorInfoComponent* _Temp = m_GameObject->GetComponent<CharactorInfoComponent>();
			if (_Temp->playerIndex == 1)
				ParticleManager::Play(true, _Temp->CharIndex, m_GameObject->GetLocalTranslate(), Particle::Motion, 0, _animator->_animatorController->_currAnimationNode->_animationClipName);
			else
				ParticleManager::Play(false, _Temp->CharIndex, m_GameObject->GetLocalTranslate(), Particle::Motion, 0, _animator->_animatorController->_currAnimationNode->_animationClipName);
		}
	}
}

bool StateComponent::IsMovable()
{
	if (curstate == STATE_IDLE || curstate == STATE_JUMP || curstate == STATE_MOVEBK || curstate == STATE_MOVEFW)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool StateComponent::IsAttackable()
{
	if (curstate == STATE_IDLE || curstate == STATE_MOVEBK || curstate == STATE_MOVEFW || curstate==STATE_ATTACK)
	{
		return true;
	}
	else
	{
		return false;
	}

}



