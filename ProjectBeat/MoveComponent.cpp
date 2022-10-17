#include "GamePCH.h"
#include "MoveComponent.h"
#include "StateComponent.h"
#include "CharactorInfoComponent.h"
#include "RectObject.h"
MoveComponent::MoveComponent(GameObject* _GameObject)
	:Component(_GameObject)
{

}

MoveComponent::~MoveComponent()
{

}

void MoveComponent::Init(float _speed, unsigned char up, unsigned char down, unsigned char left, unsigned char right)
{
	speed = _speed;
	keys[0] = up;
	keys[1] = down;
	keys[2] = left;
	keys[3] = right;
	_Cstate = m_GameObject->GetComponent<StateComponent>();
	_CInfo = m_GameObject->GetComponent<CharactorInfoComponent>();
}

void MoveComponent::OnEnterCollider(GameObject* Other)
{
	if (Other->GetName() == "RectObject")
	{
		_Cstate->ChangeState(0);
	}
}

void MoveComponent::Update()
{
	if (GameManager::Instance()->CheckRoundEnd() || !GameManager::Instance()->GetisStart()) return;

	// XBox 컨트롤러 구분을 위해 플레이어 인덱스를 Get
	int playerIdx = m_GameObject->GetComponent<CharactorInfoComponent>()->playerIndex - 1;

	if (KEYBORAD->KeyPress(keys[2])
		|| KEYBORAD->XBoxPadPress(playerIdx, XBoxPadInput::Left))
	{
		Move(-1);
	}
	else if (KEYBORAD->KeyPress(keys[3])
		|| KEYBORAD->XBoxPadPress(playerIdx, XBoxPadInput::Right))
	{
		Move(1);
	}
	else if (KEYBORAD->KeyPress(keys[1])
		|| KEYBORAD->XBoxPadPress(playerIdx, XBoxPadInput::Down))
	{
		Guard();
	}

	if ((KEYBORAD->KeyUp(keys[2]) || KEYBORAD->KeyUp(keys[3]))
		||(KEYBORAD->XBoxPadUp(playerIdx, XBoxPadInput::Left) || KEYBORAD->XBoxPadUp(playerIdx, XBoxPadInput::Right)))
	{
		if (_Cstate->IsMovable() && _Cstate->GetState() != 3)
		{
			_Cstate->ChangeState(0);
		}
	}

	if (KEYBORAD->KeyUp(keys[1])
		|| KEYBORAD->XBoxPadUp(playerIdx, XBoxPadInput::Down))
	{
		if (_Cstate->GetState() == 5)
		{
			_Cstate->ChangeState(0);
		}
	}

	if (KEYBORAD->KeyDonw(keys[0])
		|| KEYBORAD->XBoxPadDown(playerIdx, XBoxPadInput::Up))
	{
		//점프
		Jump();
	}

}



//STATE_IDLE,
//STATE_MOVEFW,
//STATE_MOVEBK,
//STATE_JUMP,
//STATE_ATTACK,
//STATE_GUARD,
//STATE_HIT,
//STATE_DEATH

void MoveComponent::Move(int dir)
{
	Vector2D _temp = m_GameObject->GetLocalTranslate();

	if (_CInfo != nullptr)
	{
		if (_Cstate->IsMovable())
		{
			direction = dir;
			if (_Cstate->GetState() == 3)
			{
				m_GameObject->SetLocalTranslateVector(_temp.x + (direction * speed * m_GameObject->m_Speed), _temp.y);
			}
			else
			{

				if (m_GameObject->GetLocalScale().x != dir)
				{
					_Cstate->ChangeState(2);

				}
				else
				{
					_Cstate->ChangeState(1);

				}
				m_GameObject->SetLocalTranslateVector(_temp.x + (direction * speed * m_GameObject->m_Speed), _temp.y);
			}
		}
	}
}
void MoveComponent::Jump()
{
	Vector2D _temp = m_GameObject->GetLocalTranslate();
	if (m_GameObject->GetComponent<CharactorInfoComponent>() != nullptr)
	{
		if (_Cstate->IsMovable())
		{
			if (_Cstate->GetState() == 3)
			{

			}
			else
			{
				_Cstate->ChangeState(3);
				m_GameObject->m_Pyhsics->AddForce(Vector2D(0, -1), 35);

			}
		}
	}
}

void MoveComponent::Sit()
{

}

void MoveComponent::Guard()
{
	if (m_GameObject->GetComponent<CharactorInfoComponent>() != nullptr)
	{

			if (_Cstate->IsMovable()&&_Cstate->GetState() != 3)
			{
				_Cstate->ChangeState(5);
			
			}
			else
			{
				

			}
		
	}
}

