#include "GamePCH.h"
#include "SpecialEf.h"
#include "Character.h"
#include "CharactorInfoComponent.h"


SpecialEf::SpecialEf(GameObject* _GameObject) :Effect(_GameObject)
{
	m_Renderer = m_GameObject->AddComponent<SpriteRenderer>();
	m_Renderer->Init("0035_Ef_Special", "DRUM1", 1.0f);
	m_GameObject->collider = m_GameObject->AddComponent<AABBCollider>();
	dynamic_cast<AABBCollider*>(m_GameObject->collider)->Init(Vector2D(m_Renderer->_sprite->Width * 0.5f, m_Renderer->_sprite->Height * 0.5f));

	m_GameObject->AddComponent<RectRender>()->Init(m_Renderer->leftTop.x, m_Renderer->leftTop.y, m_Renderer->rightBot.x, m_Renderer->rightBot.y);
}

SpecialEf::~SpecialEf()
{
}

void SpecialEf::Play(bool _isPlayer1, int _CharIndex, float _Damage)
{
	SetisPlay(true);
	m_isPlayer1 = _isPlayer1;
	m_CharIndex = _CharIndex;
	m_isCol = false;
	m_Size = 1.0f;
	m_Alpha = 1.0f;
	m_Timer = 0.0f;
	m_Damage = _Damage;
	m_Renderer->SetAlpha(m_Alpha);
	if (m_isPlayer1)
		m_GameObject->SetLocalScaleVector(1.0f, 1.0f);
	else
		m_GameObject->SetLocalScaleVector(-1.0f, 1.0f);

	switch (m_CharIndex)
	{
	case 0: //드럼
		m_Renderer->SetSprite("0035_Ef_Special", "DRUM1", m_Size);
		break;

	case 1: //신디
		m_Renderer->SetSprite("0035_Ef_Special", "SYN1", m_Size);
		break;

	case 2: //기타
		m_Renderer->SetSprite("0035_Ef_Special", "ELEC1", m_Size);
		break;

	case 3: //탬버린
		m_Renderer->SetSprite("0035_Ef_Special", "TAM1", m_Size);
		break;
	default:
		break;
	}

}

void SpecialEf::Start()
{

}

void SpecialEf::Update()
{
	if (!GetisPlay())
	{
		m_GameObject->SetActive(false);
		return;
	}
	if (!m_isCol)
	{
		m_GameObject->SetLocalTranslateVector(m_GameObject->GetLocalTranslate().x + (20 * m_GameObject->GetLocalScale().x * GameManager::Instance()->GetSpeed()), m_GameObject->GetLocalTranslate().y);
	}
	else
	{
		switch (m_CharIndex)
		{
		case 0: //드럼
			m_Renderer->SetSprite("0035_Ef_Special", "DRUM2", m_Size);
			break;

		case 1: //신디
			m_Renderer->SetSprite("0035_Ef_Special", "SYN2", m_Size);
			break;

		case 2: //기타
			m_Renderer->SetSprite("0035_Ef_Special", "ELEC2", m_Size);
			break;

		case 3: //탬버린
			m_Renderer->SetSprite("0035_Ef_Special", "TAM2", m_Size);
			break;
		default:
			break;
		}
		m_Renderer->SetAlpha(m_Alpha);

		if (m_Timer >= 1)
		{
			SetisPlay(false);
		}

		m_Size += 0.02f;
		m_Timer += 0.1f;
		m_Alpha -= 0.1f;

	}
}

void SpecialEf::OnEnterCollider(GameObject* Other)
{
	//player1이니?
	if (m_isPlayer1)
	{
		if (Other->m_teg == "Player2")
		{
			m_isCol = true;
			CharactorInfoComponent* _temp = GameManager::Instance()->GetPlayer1()->GetComponent<CharactorInfoComponent>();
			_temp->SetDamageAble(true);
			_temp->StrongHit = true;
			_temp->GetComponent<StateComponent>()->ChangeState(0);
			Other->GetComponent<StateComponent>()->ChangeState(0);

			_temp->ApplyDmgtoTarget(m_Damage);
		}
	}
	else //player2
	{
		if (Other->m_teg == "Player1")
		{
			m_isCol = true;
			CharactorInfoComponent* _temp = GameManager::Instance()->GetPlayer2()->GetComponent<CharactorInfoComponent>();
			_temp->SetDamageAble(true);
			_temp->StrongHit = true;
			_temp->GetComponent<StateComponent>()->ChangeState(0);
			Other->GetComponent<StateComponent>()->ChangeState(0);
			_temp->ApplyDmgtoTarget(m_Damage);

		}
	}

}
