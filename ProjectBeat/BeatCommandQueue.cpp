#include "GamePCH.h"
#include "BeatCommandQueue.h"

BeatCommandQueue::BeatCommandQueue(char _KeyA, char _KeyS, string _SheetName, Vector2D _BeatBurstPos, int _CharIndex, int _BeatCount, int _PlayerIndex)
{
	m_PlayerIndex = _PlayerIndex;
	m_BeatCount = _BeatCount;
	m_CommandBarSize = 450 / m_BeatCount;
	m_CharIndex = _CharIndex;
	m_KeyA = _KeyA;
	m_KeyS = _KeyS;
	if (_BeatBurstPos.x > 960)
		m_CommandPos = Vector2D(_BeatBurstPos.x - 250, 125);
	else
		m_CommandPos = Vector2D(_BeatBurstPos.x - 200, 125);
	m_SheetName = _SheetName;


	m_BeatBurstObject = new SpriteObject(_SheetName, "IDLE", m_Size);
	m_BeatBurstObject->SetLayer(1);
	m_BeatBurstObject->SetLocalTranslateVector(_BeatBurstPos);
	GameProcess::GetGameObjectManager()->InsertObject(m_BeatBurstObject);



	switch (m_CharIndex)
	{
	case 0: //드럼
		m_SoundName = "Spe_Drum_";
		break;
	case 1: //신디
		m_SoundName = "Spe_Syn_";
		break;
	case 2: //기타
		m_SoundName = "Spe_Ele_";
		break;
	case 3: //탬버린
		m_SoundName = "Spe_Tam_";
		break;
	default:
		break;
	}


}

BeatCommandQueue::~BeatCommandQueue()
{
}

void BeatCommandQueue::SetSize(float _Size)
{
	m_Size = _Size;
	m_BeatBurstObject->GetComponent<SpriteRenderer>()->SetSprite(m_SheetName, "IDLE", m_Size);
}

bool BeatCommandQueue::CompareOther(BeatCommandQueue* _Other)
{
	if (m_CommandChar.size() != _Other->m_CommandChar.size())
		return false;

	if (m_CommandChar.empty() && _Other->m_CommandChar.empty())
		return true;

	if (m_CommandChar.front() == _Other->m_CommandChar.front())
	{
		m_CommandChar.pop();
		_Other->m_CommandChar.pop();

		return CompareOther(_Other);
	}
	else
		return false;
}

void BeatCommandQueue::Update()
{
	char _InputKey = KEYBORAD->GetDownKey();

	// XBox 컨트롤러 구분을 위해 플레이어 인덱스를 Get
	int playerIdx = m_PlayerIndex - 1;

	if (KEYBORAD->KeyDonw(m_KeyA)
		|| KEYBORAD->XBoxPadDown(playerIdx, XBoxPadInput::ButtonA))
	{
		GetSoundManager()->Play(m_SoundName + "P", IPlayMode::Effect);
		if ((unsigned int)m_BeatCount > m_CommandChar.size())
		{
			m_CommandChar.push('A');
			SpriteObject* _temp = new SpriteObject("0015_BeatBurstScene", "P", 1.0f);
			_temp->SetLayer(3);
			_temp->SetLocalTranslateVector(10 + m_CommandPos.x + m_CommandBarSize * m_CommandSprite.size(), m_CommandPos.y);
			m_CommandSprite.push(_temp);
			GameProcess::GetGameObjectManager()->PushBackObject(_temp);
		}

	}
	else if (KEYBORAD->KeyDonw(m_KeyS)
		|| KEYBORAD->XBoxPadDown(playerIdx, XBoxPadInput::ButtonB))
	{
		GetSoundManager()->Play(m_SoundName + "K", IPlayMode::Effect);
		if ((unsigned int)m_BeatCount > m_CommandChar.size())
		{
			m_CommandChar.push('S');
			SpriteObject* _temp = new SpriteObject("0015_BeatBurstScene", "K", 1.0f);
			_temp->SetLayer(3);
			_temp->SetLocalTranslateVector(10 + m_CommandPos.x + m_CommandBarSize * m_CommandSprite.size(), m_CommandPos.y);
			m_CommandSprite.push(_temp);
			GameProcess::GetGameObjectManager()->PushBackObject(_temp);
		}


	}

	if (KEYBORAD->KeyPress(m_KeyA) && KEYBORAD->KeyPress(m_KeyS))
	{
		m_BeatBurstObject->GetComponent<SpriteRenderer>()->SetSprite(m_SheetName, "MIDDLE", m_Size);
	}
	else if (KEYBORAD->KeyPress(m_KeyA))
	{
		m_BeatBurstObject->GetComponent<SpriteRenderer>()->SetSprite(m_SheetName, "LEFT", m_Size);
	}
	else if (KEYBORAD->KeyPress(m_KeyS))
	{
		m_BeatBurstObject->GetComponent<SpriteRenderer>()->SetSprite(m_SheetName, "RIGHT", m_Size);
	}
	else
	{
		if (KEYBORAD->KeyUp(m_KeyA))
		{
			m_BeatBurstObject->GetComponent<SpriteRenderer>()->SetSprite(m_SheetName, "IDLE", m_Size);
		}
		else if (KEYBORAD->KeyUp(m_KeyS))
		{
			m_BeatBurstObject->GetComponent<SpriteRenderer>()->SetSprite(m_SheetName, "IDLE", m_Size);
		}
	}
}
