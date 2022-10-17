#include "GamePCH.h"
#include "ActionComponent.h"
#include "CharactorInfoComponent.h"
#include "StateComponent.h"
#include "CommandComponent.h"
#include "CircleCollider.h"
ActionComponent::ActionComponent(GameObject* _GameObject) :
	Component(_GameObject)
{

}

ActionComponent::~ActionComponent()
{

}

void ActionComponent::Update()
{
	if (GameManager::Instance()->CheckRoundEnd() || !GameManager::Instance()->GetisStart()) return;
	// 2������ ���� Ű �Է� �ޱ�.(ù Ű 1������ ���� +1)
	// keys[0] = punch, keys[1] = kick

	// XBox ��Ʈ�ѷ� ������ ���� �÷��̾� �ε����� Get
	int playerIdx = m_GameObject->GetComponent<CharactorInfoComponent>()->playerIndex - 1;

	if (KEYBORAD->KeyDonw(keys[0])
		|| KEYBORAD->XBoxPadDown(playerIdx, XBoxPadInput::ButtonA))
	{
		m_Commandqueue.push(keys[0]);
		if (m_InputFrame <= 0)
		{
			//��� ������ ����
			m_InputFrame = 1;
			//ù Ű�Է�.
			m_isInput = true;
		}
	}
	if (KEYBORAD->KeyDonw(keys[1])
		|| KEYBORAD->XBoxPadDown(playerIdx, XBoxPadInput::ButtonB))
	{
		m_Commandqueue.push(keys[1]);
		if (m_InputFrame <= 0)
		{
			//��� ������ ����
			m_InputFrame = 1;
			//ù Ű�Է�.
			m_isInput = true;
		}
	}


	// �����ð����� Ŀ�ǵ带 �Է� �ް� �ؼ�.
	if (m_InputFrame >= 0)
		m_InputFrame--;
	else if (m_isInput)
	{
		//m_isKeys[0] ��ġ
		//m_isKeys[1] ű
		while (!m_Commandqueue.empty())
		{
			if (m_Commandqueue.front() == keys[0])
				m_isKeys[0] = true;
			else if (m_Commandqueue.front() == keys[1])
				m_isKeys[1] = true;
			m_Commandqueue.pop();
		}
		if (m_isKeys[0] && m_isKeys[1])
		{
			executeUltra();
		}
		else if (m_isKeys[0])
		{
			executePunch();
		}
		else if (m_isKeys[1])
		{
			executeKick();
		}

		m_isKeys[0] = false;
		m_isKeys[1] = false;
		m_isInput = false;
	}

}

void ActionComponent::executePunch()
{
		CommandComponent* C_Command = m_GameObject->GetComponent<CommandComponent>();
		C_Command->setPunch(true);
}

void ActionComponent::executeKick()
{
		CommandComponent* C_Command = m_GameObject->GetComponent<CommandComponent>();
		C_Command->setPunch(false);
}






void ActionComponent::executeUltra()
{
	//Player1�̶�� True;
	//Player2 ��� false;
	//�ʻ��
	CharactorInfoComponent* _Temp = m_GameObject->GetComponent<CharactorInfoComponent>();
	
	if (_Temp->GetSpecial())
	{
		if (_Temp->playerIndex == 1)
			GameManager::Instance()->PlayBeatBurst(true);
		else if (_Temp->playerIndex == 2)
			GameManager::Instance()->PlayBeatBurst(false);

		_Temp->SetSpecial(false);
	}
}

void ActionComponent::Init(unsigned char punch, unsigned char kick)
{
	{
		keys[0] = punch;
		keys[1] = kick;
	}
}

