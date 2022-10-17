#include "GamePCH.h"
#include "EndingScene.h"
#include "IntroScene.h"

EndingScene::EndingScene()
{

}

EndingScene::~EndingScene()
{
}

void EndingScene::Init(int _CharIndex /*= 0*/)
{
	// ���ҽ� �Ŵ����� ȹ��(�̱���)
	ResourceManager* m_ResourceManager = ResourceManager::Instance();

	// BGM ���
	GameProcess::m_pSoundManager->Play("BGM_Ending", IPlayMode::BGM);

	// todo: ���� �� �þ�� ����
	// ���� �� ����

	string _SheetName ="";
	string _SpriteName ="";

	switch (_CharIndex)
	{
		/// 0 �巳
		case 0:
		{
			_SheetName = "0022_EndingDrum";
			_SpriteName = "0022_EndingDrum";
		}
		break;
		/// 1 �ŵ�
		case 1:
		{
			_SheetName = "0022_EndingDrum";
			_SpriteName = "0022_EndingDrum";
		}
		break;
		/// 2 ��Ÿ
		case 2:
		{
			_SheetName = "0022_EndingDrum";
			_SpriteName = "0022_EndingDrum";
		}
		break;
		/// 3 �ƹ���
		case 3:
		{
			_SheetName = "0022_EndingDrum";
			_SpriteName = "0022_EndingDrum";
		}
		break;
		default:
		{
			_SheetName = "0022_EndingDrum";
			_SpriteName = "0022_EndingDrum";
		}
		break;
	}

	// ���� ���� ��� �����ϰ� ������Ʈ �Ŵ����� Insert�Ѵ�
	for (size_t i = 0; i < (unsigned int)m_MaxEndingScene; i++)
	{
		D2DSprite* _Sprite = m_ResourceManager->GetSprite(_SheetName, _SpriteName + to_string(i + 1));
		// ���� ��������Ʈ ����
		SpriteObject* _tmp = new SpriteObject(_SheetName, _Sprite->m_spriteName, 1.f, Vector2D((float)(_Sprite->Width / 2), (float)(_Sprite->Height / 2)));
		_tmp->GetComponent<SpriteRenderer>()->SetAlpha(0.f);
		_tmp->GetComponent<SpriteRenderer>()->SetSprite(_SheetName, _Sprite->m_spriteName, 1.0f);
		
		// ������ ���� ��������Ʈ�� ����
		m_EndingSprite.push_back(_tmp);
		// ������Ʈ �Ŵ����� Insert
		GetObjManager()->InsertObject(_tmp);
	}
}

void EndingScene::Start()
{
}

void EndingScene::Update()
{
#pragma region ��ŵ Ű ���� ó��
	// ��ŵ Ű
	if (KEYBORAD->KeyDonw(VK_ESCAPE)
		|| KEYBORAD->XBoxPadDown(0, XBoxPadInput::Back)
		|| KEYBORAD->XBoxPadDown(1, XBoxPadInput::Back))
	{
		// Ÿ��Ʋ ȭ������ �̵�
		GameProcess::m_pSceneManager->ChangeScene<IntroScene>();
	}
#pragma endregion

#pragma region �� ��ȯ ó��
	m_SceneChangeTimer += CTime::GetDeltaTime();

	if (m_SceneChangeTimer < 2.5f)
		FadeIn(m_EndingSprite.at(0));
	else if (m_SceneChangeTimer >= 2.5f && m_SceneChangeTimer < 5.0f)
		FadeOut(m_EndingSprite.at(0));

	if (m_SceneChangeTimer >=  5.0f && m_SceneChangeTimer < 7.5f)
		FadeIn(m_EndingSprite.at(1));
	else if (m_SceneChangeTimer >= 7.5f && m_SceneChangeTimer < 10.0f)
		FadeOut(m_EndingSprite.at(1));

	if (m_SceneChangeTimer >= 10.f)
		FadeIn(m_EndingSprite.at(2));
#pragma endregion
}

void EndingScene::Render(D2DEngine* m_Engine)
{
	GetObjManager()->Render(m_Engine);
	string str = "ESC: Ÿ��Ʋ ȭ������";
	m_Engine->DrawString(10, 40, str, 24, 0x00FFFFFF);
}

void EndingScene::FadeIn(SpriteObject* _Sprite)
{
	m_FadeAlpha += CTime::GetDeltaTime() * m_FadeSpeed;
	_Sprite->GetComponent<SpriteRenderer>()->SetAlpha(m_FadeAlpha);
}

void EndingScene::FadeOut(SpriteObject* _Sprite)
{
	m_FadeAlpha -= CTime::GetDeltaTime() * m_FadeSpeed;
	_Sprite->GetComponent<SpriteRenderer>()->SetAlpha(m_FadeAlpha);
}
