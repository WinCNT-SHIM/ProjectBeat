#include "GamePCH.h"
#include "HitEf.h"

HitEf::HitEf(GameObject* _GameObject) : Effect(_GameObject)
{
	m_Renderer = m_GameObject->AddComponent<SpriteRenderer>();
	m_Renderer->Init("0033_Ef_Hit", "DRUM", 1.0f);
}

HitEf::~HitEf()
{
}

void HitEf::Play(bool _isPlayer1, int _CharIndex, float _Damage)
{
	SetisPlay(true);
	m_isPlayer1 = _isPlayer1;
	m_CharIndex = _CharIndex;
	m_Size = 1.0f;
	m_Alpha = 1.0f;
	m_Timer = 0.0f;
	m_Damage = _Damage;
	m_Renderer->SetAlpha(m_Alpha);

	if (m_isPlayer1)
		m_GameObject->SetLocalScaleVector(1.0f, 1.0f);
	else
		m_GameObject->SetLocalScaleVector(-1.0f, 1.0f);

	m_GameObject->m_tr->AddLocalTranslateVector(-30.0f * m_GameObject->GetLocalScale().x, -70.0f);
	switch (m_CharIndex)
	{
	case 0: //�巳
		m_Renderer->SetSprite("0033_Ef_Hit", "DRUM", m_Size);
		break;

	case 1: //�ŵ�
		m_Renderer->SetSprite("0033_Ef_Hit", "SYN", m_Size);
		break;

	case 2: //��Ÿ
		m_Renderer->SetSprite("0033_Ef_Hit", "ELEC", m_Size);
		break;

	case 3: //�ƹ���
		m_Renderer->SetSprite("0033_Ef_Hit", "TAM", m_Size);
		break;
	default:
		break;
	}
}

void HitEf::Start()
{
}

void HitEf::Update()
{
	if (!GetisPlay())
	{
		m_GameObject->SetActive(false);
		return;
	}
	m_Timer += 0.1f;
	m_Size += 0.01f;
	m_Alpha -= 0.1f;
	m_Renderer->SetAlpha(m_Alpha);
	switch (m_CharIndex)
	{
	case 0: //�巳
		m_Renderer->SetSprite("0033_Ef_Hit", "DRUM", m_Size);
		break;

	case 1: //�ŵ�
		m_Renderer->SetSprite("0033_Ef_Hit", "SYN", m_Size);
		break;

	case 2: //��Ÿ
		m_Renderer->SetSprite("0033_Ef_Hit", "ELEC", m_Size);
		break;

	case 3: //�ƹ���
		m_Renderer->SetSprite("0033_Ef_Hit", "TAM", m_Size);
		break;
	default:
		break;
	}
	if (m_Timer >= 1)
	{

		SetisPlay(false);
	}
}
