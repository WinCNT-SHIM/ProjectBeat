#include "GamePCH.h"
#include "CharSelectObject.h"
#include "SeletionComponents.h"
#include "TestScene2.h"
#include "InGameScene.h"
#include "IntroScene.h"

SeletionComponents::SeletionComponents(GameObject* _GameObject) : Component(_GameObject), isPlayer1Select(false), m_Player1Slection(0), m_NowSelection(0),
m_SelectCursor(nullptr), m_illustration(nullptr), m_Idle(nullptr), SelectCheck(false), m_isFinal(false)
{
	for (int i = 0; i < 4; i++)
	{
		m_CharSelectObject[i] = nullptr;
	}
}

SeletionComponents::~SeletionComponents()
{

}

void SeletionComponents::Start()
{
	GetSoundManager()->Play("BGM_Select",IPlayMode::BGM);
	m_NowSelection = 0;
	m_PriorSelection = m_NowSelection;
	SpriteObject* _BG = new SpriteObject("0012_SelectSceneUI", "BG", 1, Vector2D(1920 / 2, 1080 / 2), Vector2D(1920, 1080)); //��� �̹���
	GameProcess::GetGameObjectManager()->InsertObject(_BG);

	m_SelectCursor = new SpriteObject("0012_SelectSceneUI", "PLAYER1CURSUR", 1.0f, m_Pos[0]); //Ŀ�� �̹���
	m_SelectCursor->SetLayer(3);
	GameProcess::GetGameObjectManager()->InsertObject(m_SelectCursor);

	SpriteObject* _TOPUI = new SpriteObject("0012_SelectSceneUI", "TOPUI", 1.0f, Vector2D(960, 100)); //Ŀ�� �̹���
	_TOPUI->SetLayer(3);
	GameProcess::GetGameObjectManager()->InsertObject(_TOPUI);

	/// ���� ������ �ʱ�ȭ �� ����

	m_Pos[0] = Vector2D(550.0f, 700.0f);
	m_Pos[1] = Vector2D(950.0f, 800.0f);
	m_Pos[2] = Vector2D(1250.0f, 600.0f);
	m_Pos[3] = Vector2D(1550.0f, 700.0f);


	/// �Ϸ���Ʈ ����
	m_illustration = new SpriteObject("0002_illustration", "DRUM", 1.0f, Vector2D(300, 600)); //�Ϸ���Ʈ �̹���
	m_illustration->SetLayer(3);
	GameProcess::GetGameObjectManager()->InsertObject(m_illustration);
	/// �Ϸ���Ʈ ����

	/// idle ����
	m_Idle = new SpriteObject("0012_SelectSceneUI", "DRUMIDLE", 0.7f, Vector2D(0, 0)); //�Ϸ���Ʈ �̹���
	m_Idle->SetLayer(6);
	GameProcess::GetGameObjectManager()->InsertObject(m_Idle);
	/// idle ����

	// ���� ���� ����
	m_Idle->SetLocalTranslateVector(3000, 3000);
	// ���� ���� ����


	//���ܳ��� �͵�
	m_SelectCursor2 = new SpriteObject("0012_SelectSceneUI", "PLAYER2CURSUR", 1.0f, Vector2D(3000, 3000)); //Ŀ�� �̹���
	m_SelectCursor2->SetLayer(3);
	GameProcess::GetGameObjectManager()->InsertObject(m_SelectCursor2);
	m_illustration2 = new SpriteObject("0002_illustration", "DRUM", 1.0f, Vector2D(3000, 3000)); //�Ϸ���Ʈ �̹���
	m_illustration2->SetLayer(3);
	GameProcess::GetGameObjectManager()->InsertObject(m_illustration2);
}

void SeletionComponents::Update()
{
	m_VibrationTimer += CTime::GetDeltaTime();
	if (m_VibrationTimer > 0.20f)
	{
		// ���� �е��� ������ ����
		// ���� ��ġ�� �̻������� ���� �ð��� ���� �� ���� ��ġ�� �������� �ʴ´�...
		KEYBORAD->SetXBoxPadVibration(0, 0, 0);
		KEYBORAD->SetXBoxPadVibration(1, 0, 0);
		m_VibrationTimer = 0;
	}

	m_PriorSelection = m_NowSelection;
	if (m_isFinal)
	{
		static float _Count = 0;

		_Count += CTime::GetDeltaTime();

		if (_Count > 1)
		{
			/// <summary>
					/// ���Ⱑ �� ��ȯ�ϴ� �κ�. 
					/// </summary>
			GameProcess::m_pSceneManager->ChangeScene<InGameScene>();
			dynamic_cast<InGameScene*>(GameProcess::m_pSceneManager->GetScene())->Init(m_Player1Slection, m_NowSelection);
			_Count = 0;
		}
	}
	else
	{


		if (KEYBORAD->KeyDonw(VK_BACK) && !m_isFinal
			|| KEYBORAD->KeyDonw(VK_ESCAPE) && !m_isFinal
			|| (KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::Back) && !m_isFinal))
		{
			if (SelectCheck)
			{
				m_Idle->SetLocalTranslateVector(3000, 3000);
				SelectCheck = false;
			}
			else if (isPlayer1Select)
			{
				isPlayer1Select = false;
				m_Player1Slection = 0;
				m_SelectCursor2->SetLocalTranslateVector(Vector2D(3000, 3000));
				m_illustration2->SetLocalTranslateVector(Vector2D(3000, 3000));
			}
			else
			{
				GameProcess::m_pSceneManager->ChangeScene<IntroScene>();
			}
			m_NowSelection = 0;
			if (m_NowSelection >= 0 && m_NowSelection < 4)
			{
				if (isPlayer1Select)
					m_SelectCursor2->SetLocalTranslateVector(Vector2D(m_Pos[m_NowSelection].x, m_Pos[m_NowSelection].y - 200.0f));
				else
					m_SelectCursor->m_tr->SetLocalTranslateVector(Vector2D(m_Pos[m_NowSelection].x, m_Pos[m_NowSelection].y - 200.0f));
			}
		}
		if (!SelectCheck && !m_isFinal)
		{
			if (isPlayer1Select)
			{
				if (KEYBORAD->KeyDonw(VK_RIGHT)
					|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::Right)
					)
				{

					if (m_NowSelection < 3)
						m_NowSelection++;
				}
				if (KEYBORAD->KeyDonw(VK_LEFT)
					|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::Left))
				{


					if (m_NowSelection > 0)
						m_NowSelection--;
				}


				if (m_NowSelection == 0)
				{
					m_illustration2->GetComponent<SpriteRenderer>()->SetSprite("0002_illustration", "DRUM", 1.0f);
					m_Idle->GetComponent<SpriteRenderer>()->SetSprite("0012_SelectSceneUI", "DRUMIDLE", 1.0f);

				}
				else if (m_NowSelection == 1)
				{
					m_illustration2->GetComponent<SpriteRenderer>()->SetSprite("0002_illustration", "SYNTHESIZER", 1.0f);
					m_Idle->GetComponent<SpriteRenderer>()->SetSprite("0012_SelectSceneUI", "SYNTHESIZERIDLE", 1.0f);
				}
				else if (m_NowSelection == 2)
				{
					m_illustration2->GetComponent<SpriteRenderer>()->SetSprite("0002_illustration", "GUITAR", 1.0f);
					m_Idle->GetComponent<SpriteRenderer>()->SetSprite("0012_SelectSceneUI", "GUITARIDLE", 1.0f);
				}
				else if (m_NowSelection == 3)
				{
					m_illustration2->GetComponent<SpriteRenderer>()->SetSprite("0002_illustration", "TAMBOURINE", 1.0f);
					m_Idle->GetComponent<SpriteRenderer>()->SetSprite("0012_SelectSceneUI", "TAMBOURINEIDLE", 1.0f);

				}
			}
			else
			{
				if (KEYBORAD->KeyDonw(VK_RIGHT)
					|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::Right))
				{
					if (m_NowSelection < 3)
						m_NowSelection++;
				}
				if (KEYBORAD->KeyDonw(VK_LEFT)
					|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::Left))
				{

					if (m_NowSelection > 0)
						m_NowSelection--;
				}

				if (m_NowSelection == 0)
				{
					m_illustration->GetComponent<SpriteRenderer>()->SetSprite("0002_illustration", "DRUM", 1.0f);
					m_Idle->GetComponent<SpriteRenderer>()->SetSprite("0012_SelectSceneUI", "DRUMIDLE", 1.0f);

				}
				else if (m_NowSelection == 1)
				{
					m_illustration->GetComponent<SpriteRenderer>()->SetSprite("0002_illustration", "SYNTHESIZER", 1.0f);
					m_Idle->GetComponent<SpriteRenderer>()->SetSprite("0012_SelectSceneUI", "SYNTHESIZERIDLE", 1.0f);
				}
				else if (m_NowSelection == 2)
				{
					m_illustration->GetComponent<SpriteRenderer>()->SetSprite("0002_illustration", "GUITAR", 1.0f);
					m_Idle->GetComponent<SpriteRenderer>()->SetSprite("0012_SelectSceneUI", "GUITARIDLE", 1.0f);
				}
				else if (m_NowSelection == 3)
				{
					m_illustration->GetComponent<SpriteRenderer>()->SetSprite("0002_illustration", "TAMBOURINE", 1.0f);
					m_Idle->GetComponent<SpriteRenderer>()->SetSprite("0012_SelectSceneUI", "TAMBOURINEIDLE", 1.0f);

				}
			}


			if (m_PriorSelection != m_NowSelection)
				GetSoundManager()->Play("Ef_Chose", IPlayMode::Effect);

		}

		if (KEYBORAD->KeyDonw(VK_SPACE) || KEYBORAD->KeyDonw(VK_RETURN)
			|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::ButtonA)
			|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::ButtonB)
			|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::ButtonX)
			|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::ButtonY)
			)
		{
			// ���� �е� ���� ����
			m_VibrationTimer = 0;
			if (KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::ButtonA)
				|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::ButtonB)
				|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::ButtonX)
				|| KEYBORAD->XBoxPadDown((int)isPlayer1Select, XBoxPadInput::ButtonY))
			{
				KEYBORAD->SetXBoxPadVibration((int)isPlayer1Select);
			}
			// �̰� ���� �Ф�
			if (KEYBORAD->XBoxPadDown((int)!isPlayer1Select, XBoxPadInput::ButtonA)
				|| KEYBORAD->XBoxPadDown((int)!isPlayer1Select, XBoxPadInput::ButtonB)
				|| KEYBORAD->XBoxPadDown((int)!isPlayer1Select, XBoxPadInput::ButtonX)
				|| KEYBORAD->XBoxPadDown((int)!isPlayer1Select, XBoxPadInput::ButtonY))
			{
				KEYBORAD->SetXBoxPadVibration((int)!isPlayer1Select);
			}

			//����Ű�� ĳ���͸� ����

			if (SelectCheck)
			{
				//Ȯ��â�� �� �������.
				
					m_Idle->SetLocalTranslateVector(3000, 3000);
				if (isPlayer1Select && m_NowSelection != m_Player1Slection)
				{
					GetSoundManager()->Play("Ef_Decide", IPlayMode::Effect);
					//Player2 ����, ���� ����, VS ICON ����
					SpriteObject* _vs = new SpriteObject("0012_SelectSceneUI", "VERSUS", 1.0f, Vector2D(960, 440));
					_vs->SetLayer(6);
					GameProcess::GetGameObjectManager()->InsertObject(_vs);
					m_isFinal = true;
				}
				else if (!isPlayer1Select)
				{
					//Player1 ����
					GetSoundManager()->Play("Ef_Decide", IPlayMode::Effect);
					isPlayer1Select = true;
					m_Player1Slection = m_NowSelection;
					m_SelectCursor2->SetLocalTranslateVector(m_Pos[0]);
					m_illustration2->SetLocalTranslateVector(Vector2D(1700, 600));
				}
				SelectCheck = false;
			}
			else
			{
				if (!(isPlayer1Select && m_NowSelection == m_Player1Slection))
				{
					GetSoundManager()->Play("Ef_Decide", IPlayMode::Effect);
					//Ȯ��â
					string _SoundName;
					switch (m_NowSelection)
					{
					case 0:
						_SoundName = "Vo_In_Drum";
						break;
					case 1:
						_SoundName = "Vo_In_Syn";
						break;
					case 2:
						_SoundName = "Vo_In_Elec";
						break;
					case 3:
						_SoundName = "Vo_In_Tam";
						break;
					default:
						break;
					}
					GetSoundManager()->Play(_SoundName, IPlayMode::Effect);

					m_Idle->SetLocalTranslateVector(960, 500);
					SelectCheck = true;
				}
			}
		}
		if (m_NowSelection >= 0 && m_NowSelection < 4)
		{
			//Ŀ�� �̵�
			if (isPlayer1Select)
				m_SelectCursor2->SetLocalTranslateVector(Vector2D(m_Pos[m_NowSelection].x, m_Pos[m_NowSelection].y - 200.0f));
			else
				m_SelectCursor->m_tr->SetLocalTranslateVector(Vector2D(m_Pos[m_NowSelection].x, m_Pos[m_NowSelection].y - 200.0f));
		}
	}




}

