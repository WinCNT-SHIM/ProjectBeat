#include "GamePCH.h"
#include "ParticleManager.h"
#include "Effect.h"
#include "SpecialEf.h"
#include "HitEf.h"
#include "MotionEf.h"

Effect* ParticleManager::m_Effect[5] = { nullptr };
Effect* ParticleManager::m_HitEffect[5] = { nullptr };
Effect* ParticleManager::m_MotionEffect[5] = { nullptr };
ParticleManager::ParticleManager()
{

}

ParticleManager::~ParticleManager()
{
}

void ParticleManager::Init()
{
	for (int i = 0; i < 5; i++)
	{
		GameObject* Effect = new GameObject();
		m_Effect[i] = Effect->AddComponent<SpecialEf>();
		m_Effect[i]->m_GameObject->SetLayer(100);
		GameProcess::GetGameObjectManager()->InsertObject(Effect);
		Effect->SetActive(false);
	}

	for (int i = 0; i < 5; i++)
	{
		GameObject* Effect = new GameObject();
		m_HitEffect[i] = Effect->AddComponent<HitEf>();
		m_HitEffect[i]->m_GameObject->SetLayer(100);
		GameProcess::GetGameObjectManager()->InsertObject(Effect);
		Effect->SetActive(false);
	}


	for (int i = 0; i < 5; i++)
	{
		GameObject* Effect = new GameObject();
		m_MotionEffect[i] = Effect->AddComponent<MotionEf>();
		m_MotionEffect[i]->m_GameObject->SetLayer(100);
		GameProcess::GetGameObjectManager()->InsertObject(Effect);
		Effect->SetActive(false);
	}
}

void ParticleManager::Play(bool _isPlayer1, int _CharIndex, Vector2D _pos, Particle _particle, float _Damage, string _SpriteName)
{
	///init후 사용하세요.

	switch (_particle)
	{

	case Particle::Effect:

		for (int i = 0; i < 5; i++)
		{

			if (!m_Effect[i]->GetisPlay())
			{
				m_Effect[i]->m_GameObject->SetLocalTranslateVector(_pos);
				m_Effect[i]->Play(_isPlayer1, _CharIndex, _Damage);
				m_Effect[i]->m_GameObject->SetActive(true);

				break;
			}
		}

		break;
	case Particle::Hit:

		for (int i = 0; i < 5; i++)
		{

			if (!m_Effect[i]->GetisPlay())
			{
				m_HitEffect[i]->m_GameObject->SetLocalTranslateVector(_pos);
				m_HitEffect[i]->Play(_isPlayer1, _CharIndex, _Damage);
				m_HitEffect[i]->m_GameObject->SetActive(true);
				break;
			}
		}

		break;
	case Particle::Motion:

		for (int i = 0; i < 5; i++)
		{

			if (!m_Effect[i]->GetisPlay())
			{
				m_MotionEffect[i]->m_GameObject->SetLocalTranslateVector(_pos);
				m_MotionEffect[i]->Play(_isPlayer1, _CharIndex, _SpriteName);
				m_MotionEffect[i]->m_GameObject->SetActive(true);
				break;
			}
		}

		break;
	default:
		break;
	}


}
