#include "GamePCH.h"
#include "EventSystem.h"
#include <map>
#include <algorithm>
#include <stdarg.h>

#include "../../Engine/IUIComponent.h"
#include "../../ProjectBeat/TestHumanCtrl.h"
#include "../../ProjectBeat/AnimEventComponent.h"

static std::map<std::string, int> s_hm;
#define STR_SWITCH_BEGIN(key) \
{ \
	static bool s_bInit = false;\
    bool bLoop = true; \
    while(bLoop) \
    { \
        int nKey = -1; \
        if(s_bInit) \
        { \
            nKey=s_hm[key]; \
            bLoop = false; \
        } \
        switch(nKey) \
        { \
            case -1: \
            {

#define CASE(token) \
            } \
            case __LINE__: \
                if(!s_bInit) \
                    s_hm[token] = __LINE__; \
                else {

#define DEFAULT() \
                } \
            case 0: \
            default: \
                if(s_bInit) {

#define STR_SWITCH_END() \
            } \
        } \
        if(!s_bInit) \
            s_bInit=true; \
        } \
    }

bool CmpUIDepth(GameObject* A, GameObject* B)
{
	return (A->GetLayer() < B->GetLayer());
}

EventSystem* EventSystem::_instance = nullptr;

EventSystem::EventSystem(GameObject* object) : Component(object)
{
	if (_instance == nullptr)
	{
		_instance = this;
	}
}

EventSystem::~EventSystem()
{
	_instance = nullptr;
}

EventSystem* EventSystem::Instance()
{
	return _instance;
}

void EventSystem::Release()
{
	if (_instance != nullptr)
	{
		delete _instance;
	}
}

void EventSystem::Init()
{
	STR_SWITCH_BEGIN("")
	{
		CASE("AnimEventComponent")
			CASE("EndAnim")
			CASE("SetIdle")
			CASE("SendDmg")
			CASE("DmgOn")
			CASE("InputOff")
			CASE("PlayPunchHitSound")
			CASE("PlayKickHitSound")
			CASE("SoundManager")
			CASE("SetSoundVoulume")
			CASE("GameManager")
			CASE("ReturnToLobby")
			CASE("Resume")
	}
	STR_SWITCH_END()
}

void EventSystem::Update()
{
	if(m_IsUserInput == false) return;

	if(m_FocusObject != nullptr)
	{
		switch (m_CurrEvent)
		{
			case MsgType::RButtonDown:
				m_FocusObject->OnLButtonDown(m_CurrMouseInputPos.x, m_CurrMouseInputPos.y);
				break;
			case MsgType::RButtonMove:
				m_FocusObject->OnMouseMove(m_CurrMouseInputPos.x, m_CurrMouseInputPos.y);
				break;
			case MsgType::RButtonUp:
				m_FocusObject->OnLButtonUp(m_CurrMouseInputPos.x, m_CurrMouseInputPos.y);
				m_IsFoucs = false;
				m_FocusObject = nullptr;
				break;
			case MsgType::RButtonClick:
				m_FocusObject->OnLButtonClick(m_CurrMouseInputPos.x, m_CurrMouseInputPos.y);
				m_IsFoucs = false;
				m_FocusObject = nullptr;
				break;
			default:
				break;
		}
	}

	m_IsUserInput = false;
}

bool EventSystem::AddEvent(string componentName, string eventName)
{
	return false;
}

bool EventSystem::AddUIObject(GameObject* object)
{
	if(Instance() == nullptr) return false;

	IUIComponent* uiObj = object->GetComponent<IUIComponent>();

	if (uiObj)
	{
		m_UIObjects.push_back(uiObj);
		return true;
	}
	return false;
}

bool EventSystem::Event(int args, ...)
{
	va_list ap;

	va_start(ap, args);

	GameObject* targetObject = nullptr;
	std::string componentName = va_arg(ap, std::string);
	std::string eventname = va_arg(ap, std::string);
	STR_SWITCH_BEGIN(componentName)
	{
		CASE("SoundManager")
		{
			STR_SWITCH_BEGIN(eventname)
			{
				CASE("SetSoundVoulume")
				{
					if (::GetSoundManager())
					{
						float volume = (float)va_arg(ap, double);
						IPlayMode mode = (IPlayMode)va_arg(ap, int);
						::GetSoundManager()->SetSoundVoulume(volume, mode);
						return true;
					}
					else
					{
						return false;
					}
					break;
				}
				DEFAULT()
				{
				}
				break;
			}
			STR_SWITCH_END()
			break;
		}
		CASE("GameManager")
		{
			STR_SWITCH_BEGIN(eventname)
			{
				CASE("ReturnToLobby")
				{
					GameManager* gm = GameManager::Instance();
					if (gm)
					{
						gm->ReturnToLobby();
						return true;
					}
					else
					{
						return false;
					}
					break;
				}
				CASE("Resume")
				{
					GameManager* gm = GameManager::Instance();
					if (gm)
					{
						gm->Resume();
						return true;
					}
					else
					{
						return false;
					}
					break;
				}
				DEFAULT()
				{
				}
				break;
			}
			STR_SWITCH_END()
				break;
		}
		DEFAULT()
		{
		}
		break;
	}
	STR_SWITCH_END()
	
	va_end(ap);
	return true;
}

bool EventSystem::AnimationEvent(GameObject* targetObject, string componentName, string eventName)
{
	STR_SWITCH_BEGIN(componentName)
	{
		CASE("AnimEventComponent")
		{
			STR_SWITCH_BEGIN(eventName)
			{
				CASE("EndAnim")
					AnimEventComponent* anim = targetObject->GetComponent<AnimEventComponent>();
				if (anim)
				{
					anim->EndAnim();
					return true;
				}
				else
				{
					return false;
				}
				break;
				CASE("SendDmg")
					AnimEventComponent* anim = targetObject->GetComponent<AnimEventComponent>();
				if (anim)
				{
					anim->SendDmg();
					return true;
				}
				else
				{
					return false;
				}
				break;
				CASE("DmgOn")
					AnimEventComponent* anim = targetObject->GetComponent<AnimEventComponent>();
				if (anim)
				{
					anim->DmgOn();
					return true;
				}
				else
				{
					return false;
				}
				break;
				CASE("SetIdle")
					AnimEventComponent* anim = targetObject->GetComponent<AnimEventComponent>();
				if (anim)
				{
					anim->SetIdle();
					return true;
				}
				else
				{
					return false;
				}
				break;
				CASE("PlayPunchHitSound")
				{
					AnimEventComponent* anim = targetObject->GetComponent<AnimEventComponent>();
					if (anim)
					{
						anim->PlayPunchHitSound();
						return true;
					}
					else
					{
						return false;
					}
					break;
				}
				CASE("InputOff")
				{
					AnimEventComponent* anim = targetObject->GetComponent<AnimEventComponent>();
					if (anim)
					{
						anim->InputOff();
						return true;
					}
					else
					{
						return false;
					}
					break;
				}
				CASE("PlayKickHitSound")
				{
					AnimEventComponent* anim = targetObject->GetComponent<AnimEventComponent>();
					if (anim)
					{
						anim->PlayKickHitSound();
						return true;
					}
					else
					{
						return false;
					}
					break;
				}
				DEFAULT()
					break;
			}
			STR_SWITCH_END()
				break;
		}
		DEFAULT()
		{
		}
		break;
	}
	STR_SWITCH_END()
		return false;
}

void EventSystem::OnLButtonClick(int mousePosx, int mousePosy)
{
	m_IsUserInput = true;
	m_CurrEvent = MsgType::RButtonClick;
	m_CurrMouseInputPos.x = (float)mousePosx;
	m_CurrMouseInputPos.y = (float)mousePosy;
	vector<GameObject*> interactable;
	RECT uiRect;
	Vector2D uiObjectWorldPos;
	for (unsigned int i = 0; i < m_UIObjects.size(); i++)
	{
		if (m_UIObjects[i]->m_GameObject->m_ActiveSelf)
		{
			uiObjectWorldPos = m_UIObjects[i]->m_GameObject->GetWorldTranslate();
			SpriteRenderer* sr = m_UIObjects[i]->GetComponent<SpriteRenderer>();
			// 다음번엔 RectTransform 를 만들자
			uiRect =
			{
				(LONG)(sr->leftTop.x + uiObjectWorldPos.x),
				(LONG)(sr->leftTop.y + uiObjectWorldPos.y),
				(LONG)(sr->rightBot.x + uiObjectWorldPos.x),
				(LONG)(sr->rightBot.y + uiObjectWorldPos.y)
			};

			if (m_CurrMouseInputPos.x > uiRect.left && m_CurrMouseInputPos.x < uiRect.right
				&& m_CurrMouseInputPos.y > uiRect.top && m_CurrMouseInputPos.y < uiRect.bottom)
			{
				interactable.push_back(m_UIObjects[i]->m_GameObject);
			}
		}
	}

	if (interactable.size())
	{
		// 레이어 비교로 최상단 오브젝트를 찾아야함
		sort(interactable.begin(), interactable.end(), CmpUIDepth);

		// 해당 오브젝트한테 포커스를 얻었다고 줘야함
		m_IsFoucs = true;
		if (interactable[0]->GetComponent<IUIComponent>())
		{
			return;
		}
		m_FocusObject = interactable[0]->GetComponent<IUIComponent>();
	}
	else
	{
		m_IsFoucs = false;
		m_FocusObject = nullptr;
	}
}

void EventSystem::OnLButtonDown(int mousePosx, int mousePosy)
{
	m_IsUserInput = true;
	m_CurrEvent = MsgType::RButtonDown;
	m_CurrMouseInputPos.x = (float)mousePosx;
	m_CurrMouseInputPos.y = (float)mousePosy;

	vector<GameObject*> interactable;
	RECT uiRect;
	Vector2D uiObjectWorldPos;
	for (unsigned int i = 0; i < m_UIObjects.size(); i++)
	{
		if (m_UIObjects[i]->m_GameObject->m_ActiveSelf)
		{
			uiObjectWorldPos = m_UIObjects[i]->m_GameObject->GetWorldTranslate();
			
			// 다음번엔 RectTransform 를 만들자
			uiRect =
			{
				(LONG)(m_UIObjects[i]->GetRect().left + uiObjectWorldPos.x),
				(LONG)(m_UIObjects[i]->GetRect().top + uiObjectWorldPos.y),
				(LONG)(m_UIObjects[i]->GetRect().right + uiObjectWorldPos.x),
				(LONG)(m_UIObjects[i]->GetRect().bottom + uiObjectWorldPos.y)
			};

			if (m_CurrMouseInputPos.x > uiRect.left && m_CurrMouseInputPos.x < uiRect.right
				&& m_CurrMouseInputPos.y > uiRect.top && m_CurrMouseInputPos.y < uiRect.bottom)
			{
				interactable.push_back(m_UIObjects[i]->m_GameObject);
			}
		}
	}

	if (interactable.size())
	{
		// 레이어 비교로 최상단 오브젝트를 찾아야함
		sort(interactable.begin(), interactable.end(), CmpUIDepth);

		// 해당 오브젝트한테 포커스를 얻었다고 줘야함
		m_IsFoucs = true;
		if (!interactable[0]->GetComponent<IUIComponent>())
		{
			return;
		}
		m_FocusObject = interactable[0]->GetComponent<IUIComponent>();
	}
	else
	{
		m_IsFoucs = false;
		m_FocusObject = nullptr;
	}
}

void EventSystem::OnLButtonUp(int mousePosx, int mousePosy)
{
	m_IsUserInput = true;
	m_CurrEvent = MsgType::RButtonUp;
	m_CurrMouseInputPos.x = (float)mousePosx;
	m_CurrMouseInputPos.y = (float)mousePosy;
}

void EventSystem::OnMouseMove(int mousePosx, int mousePosy)
{
	m_IsUserInput = true;
	m_CurrEvent = MsgType::RButtonMove;
	m_CurrMouseInputPos.x = (float)mousePosx;
	m_CurrMouseInputPos.y = (float)mousePosy;
}
