#include "GamePCH.h"
#include "SpecialPanel.h"

SpecialPanel::SpecialPanel(GameObject* _GameObject) :Component(_GameObject)
{

}

SpecialPanel::~SpecialPanel()
{
}

void SpecialPanel::Init(Vector2D _Startpos, Vector2D _Endpos, float _Speed, bool _isPlayer1First)
{
	m_Startpos = _Startpos;
	m_EndPos = _Endpos;
	m_DeltaPos = m_EndPos - m_Startpos;
	m_DeltaPos.x = m_DeltaPos.x / _Speed;
	m_DeltaPos.y = m_DeltaPos.y / _Speed;
	m_isPlayer1First = _isPlayer1First;
	m_GameObject->SetLocalTranslateVector(m_Startpos);
	
	
	
}

void SpecialPanel::Update()
{
	if (m_isArrive && !m_UseBeatBurst)
	{
		GameManager::Instance()->SetPause(true);
		m_Timer += CTime::GetDeltaTime();
		if (m_Timer > 1)
		{
			GameManager::Instance()->SetPause(false);
			//비트 버스트 씬 이동.
			//시전자에 따라 값 바꿔주기
			GameManager::Instance()->ChangeBeatBurstScene(m_isPlayer1First);
			m_UseBeatBurst = true;
		}
	}
	else if (!m_isArrive && m_UseBeatBurst)
	{
		//종료.
		GameProcess::GetGameObjectManager()->DeleteObject(m_GameObject);
	}
	else
	{
		if (!m_isArrive)
		{
			Vector2D _temp = m_GameObject->GetLocalTranslate();

			if (m_DeltaPos.x > 0)
			{
				if (_temp.x > m_EndPos.x)

					m_isArrive = true;
			}
			else
			{
				if (_temp.x < m_EndPos.x)
					m_isArrive = true;
			}

			_temp += m_DeltaPos * CTime::GetDeltaTime() * 60 * GameManager::Instance()->GetSpeed();
			m_GameObject->SetLocalTranslateVector(_temp);

		}
		else
		{
			Vector2D _temp = m_GameObject->GetWorldTranslate();
			_temp -= m_DeltaPos * CTime::GetDeltaTime() * 60 * GameManager::Instance()->GetSpeed();
			m_GameObject->SetLocalTranslateVector(_temp);

			if (m_DeltaPos.x > 0)
			{
				if (_temp.x < m_Startpos.x)
					m_isArrive = false;
			}
			else
			{
				if (_temp.x > m_Startpos.x)
					m_isArrive = false;
			}
		}
	}

}
