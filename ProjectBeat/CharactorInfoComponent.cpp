#include "GamePCH.h"
#include "CharactorInfoComponent.h"
#include "DeBugPrint.h"
#include "CommandComponent.h"
#include "ParticleManager.h"
CharactorInfoComponent::CharactorInfoComponent(GameObject* _GameObject) :Component(_GameObject)
{
}

CharactorInfoComponent::~CharactorInfoComponent()
{

}


///
void CharactorInfoComponent::ApplyDmgtoTarget(float dmg)
{
	if (target != nullptr)
	{
		CharactorInfoComponent* T_Info = target->GetComponent<CharactorInfoComponent>();
		if (DamageAble())
		{
			if (target->GetComponent<StateComponent>()->GetState() != 5)
			{
				m_DeltaTime = 0;
				KEYBORAD->SetXBoxPadVibration(T_Info->playerIndex - 1);

				playHitSound();
				SetDamageAble(false);

				if (T_Info->playerIndex == 1)
					ParticleManager::Play(true, T_Info->CharIndex, T_Info->m_GameObject->GetLocalTranslate(), Particle::Hit);
				else
					ParticleManager::Play(false, T_Info->CharIndex, T_Info->m_GameObject->GetLocalTranslate(), Particle::Hit);

					target->GetComponent<CommandComponent>()->reset();
				if (T_Info->getHp() - dmg <= 0)
				{
					T_Info->setHp(0);
					target->GetComponent<StateComponent>()->ChangeState(7);
				}
				else
				{
					if (StrongHit == true)
					{
						StrongHit = false;
						target->m_Pyhsics->AddForce(Vector2D(target->GetLocalScale() * -1), 35);
					}

					T_Info->setHp(T_Info->getHp() - dmg);
					target->GetComponent<StateComponent>()->ChangeState(6);
				}
				//target->GetComponent<CommandComponent>()->reset();
				GameManager::Instance()->SetHpUI(T_Info->playerIndex, T_Info->getHp() / T_Info->getMaxHp());
				if (T_Info->getHp() == 0)
				{
					GameManager::Instance()->EndRound(T_Info->playerIndex);
				}
				else if (T_Info->getHp() / T_Info->getMaxHp() <= 0.3)
				{
					if (!T_Info->m_isLowHpSound)
					{
						T_Info->PlayLowHpSound();
					}
				}
			}

		}

	}
}

void CharactorInfoComponent::SetDamageAble(bool on)
{
	CanDmg = on;
}

void CharactorInfoComponent::Update()
{
	// 게임 패드 진동 조절을 위한 타이머
	m_DeltaTime += CTime::GetDeltaTime();
	if (m_DeltaTime > 0.25f)
	{
		// 게임 패드의 진동을 멈춤
		// 구현 위치가 이상하지만 현재 시간이 없고 더 좋은 위치가 떠오르지 않는다...
		CharactorInfoComponent* T_Info = target->GetComponent<CharactorInfoComponent>();
		KEYBORAD->SetXBoxPadVibration(T_Info->playerIndex - 1, 0, 0);
		m_DeltaTime = 0;
	}
}

void CharactorInfoComponent::Init(int charIndex)
{
	Hp = 20;
	MaxHp = 20;
	Guage = 0;
	MaxGuage = 100;
	speed = 5;
	CharIndex = charIndex;
	m_isLowHpSound = false;
	CState = GetComponent<StateComponent>();
}

void CharactorInfoComponent::playHitSound()
{
	if (GetComponent<CommandComponent>()->getPunch())
	{
		switch (CharIndex)
		{
		case 0:
			::GetSoundManager()->Play("Spe_Drum_P", IPlayMode::Effect);
			break;
		case 1:
			::GetSoundManager()->Play("Spe_Syn_P", IPlayMode::Effect);
			break;
		case 2:
			::GetSoundManager()->Play("Spe_Ele_P", IPlayMode::Effect);
			break;
		case 3:
			::GetSoundManager()->Play("Spe_Tam_P", IPlayMode::Effect);
			break;
		}

	}
	else
	{
		switch (CharIndex)
		{
		case 0:
			::GetSoundManager()->Play("Spe_Drum_K", IPlayMode::Effect);
			break;
		case 1:
			::GetSoundManager()->Play("Spe_Syn_K", IPlayMode::Effect);
			break;
		case 2:
			::GetSoundManager()->Play("Spe_Ele_K", IPlayMode::Effect);
			break;
		case 3:
			::GetSoundManager()->Play("Spe_Tam_K", IPlayMode::Effect);
			break;
		}
	}
}

void CharactorInfoComponent::SetSpecial(bool _isOn)
{
	m_isOnSpecial = _isOn;

	if (playerIndex == 1)
	{
		GameManager::Instance()->SetSpecialPanel(true, m_isOnSpecial);

		if (!m_isOnSpecial)
			m_GameObject->GetComponent<CommandComponent>()->CommandSuccessReset();
	}
	else
	{
		GameManager::Instance()->SetSpecialPanel(false, m_isOnSpecial);

		if (!m_isOnSpecial)
			m_GameObject->GetComponent<CommandComponent>()->CommandSuccessReset();
	}
}

void CharactorInfoComponent::PlayLowHpSound()
{
	m_isLowHpSound = true;

	switch (CharIndex)
	{
	case 0:
		GetSoundManager()->Play("Vo_On_Drum", IPlayMode::Effect);
		break;
	case 1:
		GetSoundManager()->Play("Vo_On_Syn", IPlayMode::Effect);
		break;
	case 2:
		GetSoundManager()->Play("Vo_On_Elec", IPlayMode::Effect);
		break;
	case 3:
		GetSoundManager()->Play("Vo_On_Tam", IPlayMode::Effect);
		break;

	default:
		break;
	}

}


