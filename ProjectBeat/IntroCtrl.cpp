#include "GamePCH.h"
#include "IntroCtrl.h"
#include "SelectionScene.h"
#include "OpeningScene.h"
#include "../SoundLib/ISoundManager.h"

IntroCtrl::IntroCtrl(GameObject* gameObject) : Component(gameObject)
{
}

IntroCtrl::~IntroCtrl()
{
}

void IntroCtrl::Init(GameObject* introParent, GameObject* creditParent, GameObject* comboParent, GameObject* cursorObj, Vector2D cursorPos)
{
	m_IntroObj = introParent;
	m_CreditObj = creditParent;
	m_ComboObj = comboParent;
	m_Cursor = cursorObj;
	m_CursorPos = cursorPos;
}

void IntroCtrl::Update()
{
	m_VibrationTimer += CTime::GetDeltaTime();
	if (m_VibrationTimer > 0.20f)
	{
		// 게임 패드의 진동을 멈춤
		// 구현 위치가 이상하지만 현재 시간이 없고 더 좋은 위치가 떠오르지 않는다...
		KEYBORAD->SetXBoxPadVibration(0, 0, 0);
		KEYBORAD->SetXBoxPadVibration(1, 0, 0);
		m_VibrationTimer = 0;
	}

	if (isChanging)
	{
		if (isFadeOut == false && isFadeIn == false)
		{
			// 지금 씬을 아웃시킴
			GameObject* currObj = nullptr;
			switch (m_CurrState)
			{
				case IntroState::IntroMain:
					isFadeOut = FadeOut(m_IntroObj);
					currObj = m_IntroObj;
					break;
				case IntroState::Credit:
					isFadeOut = FadeOut(m_CreditObj);
					currObj = m_CreditObj;
					break;
				case IntroState::ComboList:
					isFadeOut = FadeOut(m_ComboObj);
					currObj = m_ComboObj;
					break;
				default:
					break;
			}
			if (isFadeOut && currObj)
			{
				currObj->SetActive(false);
			}
		}
		else if (isFadeOut == true && isFadeIn == false)
		{
			// 씬 아웃이 끝났음으로 새로운 씬 인
			GameObject* currObj = nullptr;
			switch (m_NextState)
			{
				case IntroState::IntroMain:
					isFadeIn = FadeIn(m_IntroObj);
					currObj = m_IntroObj;
					break;
				case IntroState::Credit:
					isFadeIn = FadeIn(m_CreditObj);
					currObj = m_CreditObj;
					break;
				case IntroState::ComboList:
					isFadeIn = FadeIn(m_ComboObj);
					currObj = m_ComboObj;
					break;
				default:
					break;
			}
			if (currObj && !currObj->m_ActiveSelf)
			{
				currObj->SetActive(true);
			}
		}
		else if (isFadeOut == true && isFadeIn == true)
		{
			if (m_Init)
			{
				m_Init = false;
				m_FadeSpeed = 0.7f;
				m_Cursor->SetActive(true);
			}
			else if (m_CursorOn)
			{
				m_CursorOn = false;
				m_Cursor->SetActive(true);
			}
			// 씬 교체 완료
			isChanging = false;
			isFadeOut = false;
			isFadeIn = false;
			m_CurrState = m_NextState;

		}
		return;
	}

	if (m_CurrState == IntroState::IntroMain)
	{
		if (KEYBORAD->KeyDonw(VK_UP)
			|| KEYBORAD->XBoxPadDown(0, XBoxPadInput::Up)
			|| KEYBORAD->XBoxPadDown(1, XBoxPadInput::Up))
		{
			m_MenuCnt--;
			if (m_MenuCnt == -1)
			{
				m_MenuCnt = m_MenuMax;
				m_CursorPos.y += m_CursorMoveLen * 3;
			}
			else
			{
				m_CursorPos.y -= m_CursorMoveLen;
			}

			::GetSoundManager()->Play("Ef_Beep", IPlayMode::Effect);
			m_Cursor->SetLocalTranslateVector(m_CursorPos);
		}
		if (KEYBORAD->KeyDonw(VK_DOWN)
			|| KEYBORAD->XBoxPadDown(0, XBoxPadInput::Down)
			|| KEYBORAD->XBoxPadDown(1, XBoxPadInput::Down))
		{
			m_MenuCnt++;
			if (m_MenuCnt == m_MenuMax + 1)
			{
				m_MenuCnt = 0;
				m_CursorPos.y -= m_CursorMoveLen * 3;
			}
			else
			{
				m_CursorPos.y += m_CursorMoveLen;
			}

			::GetSoundManager()->Play("Ef_Beep", IPlayMode::Effect);
			m_Cursor->SetLocalTranslateVector(m_CursorPos);
		}
		if (KEYBORAD->KeyDonw(VK_RETURN)
			|| KEYBORAD->IsXBoxPadKeyDown(0)
			|| KEYBORAD->IsXBoxPadKeyDown(1))
		{
			// 게임 패드 진동 설정
			m_VibrationTimer = 0;
			if (KEYBORAD->IsXBoxPadKeyDown(0))
			{
				KEYBORAD->SetXBoxPadVibration(0);
			}
			if (KEYBORAD->IsXBoxPadKeyDown(1))
			{
				KEYBORAD->SetXBoxPadVibration(1);
			}

			switch (m_MenuCnt)
			{
				case 0:
				{
					::GetSoundManager()->Play("Ef_Press", IPlayMode::Effect);
					GameProcess::m_pSceneManager->ChangeScene<OpeningScene>();
				}
				break;
				case 1:
				{
					isChanging = true;
					m_NextState = IntroState::ComboList;
					m_Cursor->SetActive(false);
					::GetSoundManager()->Play("Ef_Swoop", IPlayMode::Effect);
				}
				break;
				case 2:
				{
					isChanging = true;
					m_NextState = IntroState::Credit;
					m_Cursor->SetActive(false);
					::GetSoundManager()->Play("Ef_Swoop", IPlayMode::Effect);
				}
				break;
				case 3:
				{
					// 게임 종료
					exit(0);
				}
				break;
				default:
				{
				}
				break;
			}
		}
	}
	else
	{
		if (KEYBORAD->KeyDonw(VK_ESCAPE)
			|| KEYBORAD->XBoxPadDown(0, XBoxPadInput::Back)
			|| KEYBORAD->XBoxPadDown(1, XBoxPadInput::Back))
		{
			// 게임 패드 진동 설정
			if (KEYBORAD->XBoxPadDown(0, XBoxPadInput::Back))
			{
				KEYBORAD->SetXBoxPadVibration(0);
			}
			if (KEYBORAD->XBoxPadDown(1, XBoxPadInput::Back))
			{
				KEYBORAD->SetXBoxPadVibration(1);
			}

			// 타이틀 화면으로 이동
			isChanging = true;
			m_NextState = IntroState::IntroMain;
			m_CursorOn = true;
			::GetSoundManager()->Play("Ef_Swoop", IPlayMode::Effect);
		}
	}
	
}


void IntroCtrl::ChangeIntroState(int idx)
{
	
}

bool IntroCtrl::FadeOut(GameObject* parent)
{
	m_FadeAlpha -= CTime::GetDeltaTime() * m_FadeSpeed;
	FadeObj(parent);

	if (m_FadeAlpha <= 0.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool IntroCtrl::FadeIn(GameObject* parent)
{
	m_FadeAlpha += CTime::GetDeltaTime() * m_FadeSpeed;
	FadeObj(parent);

	if (m_FadeAlpha >= 1.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void IntroCtrl::FadeObj(GameObject* parent)
{
	SpriteRenderer* sr = parent->GetComponent<SpriteRenderer>();

	if (sr)
	{
		sr->SetAlpha(m_FadeAlpha);
	}

	for (auto child : *parent->GetChilds())
	{
		FadeObj(child);
	}

}
