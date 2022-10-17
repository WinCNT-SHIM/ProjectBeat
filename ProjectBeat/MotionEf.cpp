#include "GamePCH.h"
#include "MotionEf.h"

MotionEf::MotionEf(GameObject* _GameObject) :Effect(_GameObject)
{
	m_Renderer = m_GameObject->AddComponent<SpriteRenderer>();
	m_Renderer->Init("0034_Ef_HitDrum", "P", 1.0f);
}

MotionEf::~MotionEf()
{
}

void MotionEf::Play(bool _isPlayer1, int _CharIndex, float _Damage)
{
}

void MotionEf::Play(bool _isPlayer1, int _CharIndex, string _SpriteName)
{
	SetisPlay(true);
	m_isPlayer1 = _isPlayer1;
	m_CharIndex = _CharIndex;
	m_Size = 1.2f;
	m_Alpha = 1.0f;
	m_Timer = 0.0f;
	m_EndTimer = 0;
	m_SpriteName = _SpriteName;
	if (_SpriteName == "P" || _SpriteName == "K" || _SpriteName == "PP" || _SpriteName == "PPP")
	{
		m_EndTimer = 1.4f;
	}
	else if (_SpriteName == "KP" || _SpriteName == "PKP"  || _SpriteName == "PKPPK")
	{
		m_EndTimer = 1.0f;
	}
	else if (_SpriteName == "PKK")
	{
		m_EndTimer = 0.8f;
	}
	else if (_SpriteName == "PK")
	{
		m_EndTimer = 0.f;
	}




	m_Renderer->SetAlpha(m_Alpha);
	m_Renderer->SetActive(false);
	if (m_isPlayer1)
		m_GameObject->SetLocalScaleVector(1.0f, 1.0f);
	else
		m_GameObject->SetLocalScaleVector(-1.0f, 1.0f);

	m_GameObject->m_tr->AddLocalTranslateVector(-30.0f * m_GameObject->GetLocalScale().x, -70.0f);
	switch (m_CharIndex)
	{
	case 0: //드럼
		m_SheetName = "0034_Ef_HitDrum";
		break;

	case 1: //신디
		m_SheetName = "0036_Ef_HitSyn";
		break;

	case 2: //기타
		m_SheetName = "0037_Ef_HitElec";
		break;

	case 3: //탬버린
		m_SheetName = "0038_Ef_HitTam";
		break;
	default:
		break;
	}
	m_Renderer->SetSprite(m_SheetName, m_SpriteName, m_Size);
}

void MotionEf::Start()
{
}

void MotionEf::Update()
{
	if (!GetisPlay())
	{
		m_GameObject->SetActive(false);
		return;
	}
	m_Timer += 0.1f;
	if (m_Timer > 0.6f + m_EndTimer)
	{
		m_Renderer->SetActive(true);
		m_Alpha -= 0.1f;
		m_Renderer->SetAlpha(m_Alpha);
		m_Renderer->SetSprite(m_SheetName, m_SpriteName, m_Size);

		if (m_Timer >= 2.0f + m_EndTimer)
		{
			SetisPlay(false);
		}
	}
}
