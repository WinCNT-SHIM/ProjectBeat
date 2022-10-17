#include "GamePCH.h"
#include "OutroIcon.h"
#include "Character.h"
#include "CharactorInfoComponent.h"
OutroIcon::OutroIcon(GameObject* _GameObject) : Component(_GameObject)
{
	m_Renderer = m_GameObject->AddComponent<SpriteRenderer>();
	m_Renderer->Init("0023_InGameSceneUI", "START", 1.0f);
}

OutroIcon::~OutroIcon()
{
}


void OutroIcon::Play(int _PlayerIndex)
{
	m_isPlay = true;
	m_Timer = 0;
	m_Size = 1.5f;
	m_GameObject->SetActive(true);
	m_PlayerIndex = _PlayerIndex;

	if (m_PlayerIndex == 1)
	{
		
		m_SpriteName = "P1OUTRO";
	}
	else
	{
		m_SpriteName = "P2OUTRO";
	
	}
		
}

void OutroIcon::Start()
{
}

void OutroIcon::Update()
{
	if (!m_isPlay) return;



	m_Timer += CTime::GetDeltaTime();


	if (m_Timer < 0.5f)
	{
		m_Size -= 0.02f;
		m_Renderer->SetSprite("0023_InGameSceneUI", "KO", m_Size);
	}
	else if (m_Timer > 1.0f && m_Timer < 2.0f)
	{
		if (!m_Renderer->GetActive()) return;

		if (m_Size <= 0)
		{
			m_Size = 1.5;
			m_Renderer->SetActive(false);
			if (GameManager::Instance()->CheckGameEnd())
			{
				int _Index = 0;
				string _SoundName;
				if (m_PlayerIndex == 1)
				{
					_Index = GameManager::Instance()->GetPlayer1()->GetComponent<CharactorInfoComponent>()->CharIndex;
					switch (_Index)
					{
					case 0: //드럼
						_SoundName = "Vo_Win_Drum";
						break;
					case 1: //신디
						_SoundName = "Vo_Win_Syn";
						break;
					case 2: //기타
						_SoundName = "Vo_Win_Elec";
						break;
					case 3: //탬버린
						_SoundName = "Vo_Win_Tam";
						break;
					default:
						break;
					}
				}
				else
				{
					_Index = GameManager::Instance()->GetPlayer2()->GetComponent<CharactorInfoComponent>()->CharIndex;
					switch (_Index)
					{
					case 0: //드럼
						_SoundName = "Vo_Win_Drum";
						break;
					case 1: //신디
						_SoundName = "Vo_Win_Syn";
						break;
					case 2: //기타
						_SoundName = "Vo_Win_Elec";
						break;
					case 3: //탬버린
						_SoundName = "Vo_Win_Tam";
						break;
					default:
						break;
					}
				}
				GetSoundManager()->Play(_SoundName, IPlayMode::Effect);
			}
		}
		else
		{
			m_Size -= 0.1f;
			m_Renderer->SetSprite("0023_InGameSceneUI", "KO", m_Size);
		}

	}
	else if (m_Timer < 2.5f)
	{
		if (m_Size <= 1.0f) return;

		m_Renderer->SetActive(true);
		m_Size -= 0.02f;
		m_Renderer->SetSprite("0023_InGameSceneUI", m_SpriteName, m_Size);
	}
	else if (m_Timer > 5.0f)
	{
		m_Size -= 0.1f;
		m_Renderer->SetSprite("0023_InGameSceneUI", m_SpriteName, m_Size);

		if (m_Size <= 0)
		{
			m_isPlay = false;
			m_GameObject->SetActive(false);
		}
	}

}

void OutroIcon::SetName()
{
	m_Name = "OutroIcon";
}
