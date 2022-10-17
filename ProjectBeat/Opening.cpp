#include "GamePCH.h"
#include "Opening.h"
#include "SelectionScene.h"
Opening::Opening(GameObject* _GameObject) : Component(_GameObject)
{
}

Opening::~Opening()
{
}

void Opening::Start()
{
	m_GameObject->m_tr->SetLocalTranslateVector(960, 540);
	m_Renderer = m_GameObject->AddComponent<SpriteRenderer>();
	string _SheetName = "00" + to_string(m_SheetIndex) + "_Opening" + to_string(m_SheetCount);
	m_Renderer->Init(_SheetName, to_string(m_Count), 1.0f);
	GetSoundManager()->Play("BGM_Epil", IPlayMode::BGM);

	GameObject* _SkipButton = new GameObject();
	_SkipButton->SetLocalTranslateVector(1850, 990);
	SpriteRenderer* _Temp = _SkipButton->AddComponent<SpriteRenderer>();
	_Temp->Init("0031_Opening4", "BUTTON", 0.8f);
	_Temp->SetAlpha(0.4f);
	GameProcess::GetGameObjectManager()->InsertObject(_SkipButton);


}

void Opening::Update()
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

	if (KEYBORAD->KeyDonw(VK_LBUTTON))
		GameProcess::m_pSceneManager->ChangeScene<SelectionScene>();

	if (KEYBORAD->GetDownKey()
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

		NextScene();
	}

	m_Timer += CTime::GetDeltaTime();
	if (m_Timer >= m_TimeKey[m_TimeIndex])
		NextScene();

	if (m_isFade)
	{
		if (FadeOut())
			GameProcess::m_pSceneManager->ChangeScene<SelectionScene>();
	}
}

void Opening::Render(D2DEngine* _pEngine)
{

}
void Opening::NextScene()
{
	m_Timer = 0;
	if (m_SheetIndex == 31 && m_Count == 2)
	{
		m_isFade = true;
		return;
	}
	m_Count++; //3
	m_TimeIndex++;
	if (m_Count > 4)
	{
		m_Count = 1;
		m_SheetCount++;
		m_SheetIndex++; //31
	}

	string _SheetName = "00" + to_string(m_SheetIndex) + "_Opening" + to_string(m_SheetCount);
	m_Renderer->SetSprite(_SheetName, to_string(m_Count), 1.0f);
	GetSoundManager()->Play("Ef_Trun", IPlayMode::Effect);

}
bool Opening::FadeIn()
{
	if (m_FadeAlpha >= 1)
		return true;
	m_FadeAlpha += CTime::GetDeltaTime() * m_FadeSpeed;
	m_Renderer->SetAlpha(m_FadeAlpha);
	return false;
}
bool Opening::FadeOut()
{
	if (m_FadeAlpha <= 0)
		return true;
	m_FadeAlpha -= CTime::GetDeltaTime() * m_FadeSpeed;
	m_Renderer->SetAlpha(m_FadeAlpha);
	return false;
}
void Opening::FadeObj(GameObject* parent)
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