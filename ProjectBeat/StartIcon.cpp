#include "GamePCH.h"
#include "StartIcon.h"

StartIcon::StartIcon(GameObject* _GameObject) : Component(_GameObject)
{
	m_Renderer = m_GameObject->AddComponent<SpriteRenderer>();
	m_Renderer->Init("0023_InGameSceneUI", "START", 1.0f);
}

StartIcon::~StartIcon()
{
}

void StartIcon::Play()
{
	m_isPlay = true;
	m_Timer = 0;
	m_Size = 1.5f;
	m_GameObject->SetActive(true);
}

void StartIcon::Start()
{
}

void StartIcon::Update()
{
	if (!m_isPlay) return;

	m_Timer += CTime::GetDeltaTime();
	if (m_Timer < 0.5f)
	{
		m_Size -= 0.02f;
		m_Renderer->SetSprite("0023_InGameSceneUI", "START", m_Size);
	}
	else if (m_Timer > 1.0f)
	{
		m_Size -= 0.1f;
		m_Renderer->SetSprite("0023_InGameSceneUI", "START", m_Size);

		if (m_Size <= 0)
		{
			m_isPlay = false;
			m_GameObject->SetActive(false);
			}
	}
	else
	{
		m_Size = 1.0f;
	}
}

void StartIcon::SetName()
{
m_Name = "StartIcon";
}
