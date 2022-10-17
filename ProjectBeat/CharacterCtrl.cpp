#include "GamePCH.h"
#include "CharacterCtrl.h"
#include "../Engine/Animator.h"

CharacterCtrl::CharacterCtrl(GameObject* gameObject) : Component(gameObject)
{
}

CharacterCtrl::~CharacterCtrl()
{
}

void CharacterCtrl::Init()
{

}

void CharacterCtrl::Start()
{
	m_Animator = GetComponent<Animator>();
}

void CharacterCtrl::Update()
{
	if(GameManager::Instance()->GetPause()) return;

	m_GameSpeed = GameManager::Instance()->GetSpeed();

	if(m_Animator) m_Animator->SetSpeed(m_GameSpeed);

	if (m_TargetCharacter && m_CurrState != CharacterState::Death)
	{
		if (m_TargetCharacter->GetWorldTranslate().x > m_GameObject->GetWorldTranslate().x)
		{
			m_Direction.x = 1;
		}
		else
		{
			m_Direction.x = -1;
		}
	}

	CheckState();
}

void CharacterCtrl::CheckState()
{
	switch (m_CurrState)
	{
		case CharacterState::Idle:
			CheckIdleInput();
			break;
		case CharacterState::Run:
			CheckRunInput();
			break;
		case CharacterState::Attack:
			break;
		case CharacterState::Jump:
			CheckJumpInput();
			break;
		case CharacterState::Guard:
			CheckGuardInput();
			break;
		case CharacterState::Stun:
			m_StumTime += CTime::GetDeltaTime() * m_GameSpeed;
			if (m_StumTime >= m_MaxStumTime)
			{
				m_StumTime = 0.f;
				m_MoveAble = true;
			}
			break;
		case CharacterState::Death:
			m_CanInput = false;
			break;
		default:
			break;
	}
}

void CharacterCtrl::CheckIdleInput()
{
	if(!m_CanInput)return;

	if (KEYBORAD->GetDownKey() == VK_UP && m_JumpAble)
	{
		m_CurrState = CharacterState::Jump;
		m_JumpAble = false;
		m_GameObject->m_Pyhsics->AddForce(Vector2D(0, -1), 35);
	}
	else if(KEYBORAD->GetDownKey() == VK_LEFT && m_MoveAble)
	{
		if (m_Direction.x > 0)
		{
			m_CurrState = CharacterState::Guard;
		}
		else if (m_Direction.x <= 0)
		{
			m_CurrState = CharacterState::Run;
		}
	}
	else if (KEYBORAD->GetDownKey() == VK_RIGHT && m_MoveAble)
	{
		if (m_Direction.x > 0)
		{
			m_CurrState = CharacterState::Run;
		}
		else if (m_Direction.x <= 0)
		{
			m_CurrState = CharacterState::Guard;
		}
	}
}

void CharacterCtrl::CheckJumpInput()
{
	if (!m_CanInput)return;

	Vector2D currPos = m_GameObject->GetWorldTranslate();
	if (KEYBORAD->KeyPress(VK_LEFT) && m_MoveAble)
	{
		if (m_Direction.x > 0)
		{
			m_GameObject->m_tr->SetWorldTranslateVector(currPos + m_Direction);
		}
		else if (m_Direction.x <= 0)
		{
			m_CurrState = CharacterState::Run;

		}
	}
	else if (KEYBORAD->KeyPress(VK_RIGHT) && m_MoveAble)
	{
		if (m_Direction.x > 0)
		{
			m_CurrState = CharacterState::Run;

		}
		else if (m_Direction.x <= 0)
		{
			m_GameObject->m_tr->SetWorldTranslateVector(currPos + m_Direction);
		}
	}
	else
	{
		m_CurrState = CharacterState::Idle;
	}
}

void CharacterCtrl::CheckRunInput()
{
	if (!m_CanInput)return;

	Vector2D currPos = m_GameObject->GetWorldTranslate();
	if (KEYBORAD->KeyPress(VK_LEFT) && m_MoveAble)
	{
		if (m_Direction.x > 0)
		{
			m_CurrState = CharacterState::Guard;
		}
		else if (m_Direction.x <= 0)
		{
			m_GameObject->m_tr->SetWorldTranslateVector(currPos + m_Direction);
		}
	}
	else if (KEYBORAD->KeyPress(VK_RIGHT) && m_MoveAble)
	{
		if (m_Direction.x > 0)
		{
			m_GameObject->m_tr->SetWorldTranslateVector(currPos + m_Direction);
		}
		else if (m_Direction.x <= 0)
		{
			m_CurrState = CharacterState::Guard;
		}
	}
	else if (KEYBORAD->GetDownKey() == VK_UP && m_JumpAble)
	{
		m_CurrState = CharacterState::Jump;
		m_JumpAble = false;
		m_GameObject->m_Pyhsics->AddForce(Vector2D(0, -1), 35);
	}
	else
	{
		m_CurrState = CharacterState::Idle;
	}
}

void CharacterCtrl::CheckGuardInput()
{
	if (!m_CanInput)return;

	Vector2D currPos = m_GameObject->GetWorldTranslate();
	if (KEYBORAD->KeyPress(VK_LEFT) && m_MoveAble)
	{
		if (m_Direction.x > 0)
		{
			m_GameObject->m_tr->SetWorldTranslateVector(currPos + m_Direction);
		}
		else if (m_Direction.x <= 0)
		{
			m_CurrState = CharacterState::Run;

		}
	}
	else if (KEYBORAD->KeyPress(VK_RIGHT) && m_MoveAble)
	{
		if (m_Direction.x > 0)
		{
			m_CurrState = CharacterState::Run;

		}
		else if (m_Direction.x <= 0)
		{
			m_GameObject->m_tr->SetWorldTranslateVector(currPos + m_Direction);
		}
	}
	else if (KEYBORAD->GetDownKey() == VK_UP && m_JumpAble)
	{
		m_CurrState = CharacterState::Jump;
		m_JumpAble = false;
		m_GameObject->m_Pyhsics->AddForce(Vector2D(0, -1), 35);
	}
	else
	{
		m_CurrState = CharacterState::Idle;
	}
}

void CharacterCtrl::MoveAgent()
{
	if (!m_CanInput)return;

}
