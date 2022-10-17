#include "GamePCH.h"
#include "Pause.h"

Pause::Pause(GameObject* _GameObject) : Component(_GameObject)
{
}

Pause::~Pause()
{
}

void Pause::Start()
{
	m_Renderer = m_GameObject->AddComponent<SpriteRenderer>();
	m_Renderer->Init("0023_InGameSceneUI", "PAUSE", 1.0f);
}

void Pause::Update()
{
	m_DeltaTime += CTime::GetDeltaTime();
	if (m_DeltaTime > 0.5f)
	{
		m_DeltaTime = 0;
		m_Renderer->SetActive(!m_Renderer->GetActive());
	}
}
