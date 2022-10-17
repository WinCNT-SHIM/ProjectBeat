#include "GamePCH.h"
#include "GameProcess.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "TestScene_SSS.h"
#include "IntroScene.h"
#include "SelectionScene.h"
#include "CWScene.h"
#include "TestAnimatorScene.h"
#include "InGameScene.h"


SceneManager* GameProcess::m_pSceneManager = nullptr;
ISoundManager* GameProcess::m_pSoundManager = nullptr;

GameProcess::GameProcess() //, ACircle(nullptr), BCircle(nullptr)
{
}

GameProcess::~GameProcess()
{
	m_pSceneManager->DeleteScene();
	m_pSoundManager->Finalize();
	ResourceManager::Release();
	ChangeDisplaySettings(NULL, 0);

	delete m_pSceneManager;
	delete m_Time;
	delete m_Input;
	delete m_Engine;
}

void GameProcess::Initialize(HWND hWnd)
{
	////���� ���� �� �ʱ�ȭ
	m_Engine = new D2DEngine(hWnd);
	m_Engine->Initialize();
	m_Time = new CTime();
	m_Time->Initialize();
	m_Input = new CPlayerInput(hWnd);
	m_pSceneManager = new SceneManager();
	m_pSoundManager = ::GetSoundManager();
	m_pSoundManager->Initialize();
	LoadSoundAll();	// ���ο��� ���ҽ� �Ŵ��� �����. D2D�������� ���ҽ��Ŵ����� �ʱ�ȭ�ϴµ�, ������ ��� �� ���ƾ� �� �� ����.
	m_pSceneManager->ChangeScene<IntroScene>();
	//m_pSceneManager->ChangeScene<InGameScene>();
	//dynamic_cast<InGameScene*>(m_pSceneManager->GetScene())->Init(0,1);
	// �׷��Ƚ� ���� ī�޶��� �ʱ�ȭ
	m_Engine->SetEngineCamera(0, 0, 1920, 1080);


	//#define _SSSIntroScene
#ifdef _SSSIntroScene
	m_pSceneManager->ChangeScene<EndingScene>();
	dynamic_cast<EndingScene*>(GameProcess::m_pSceneManager->GetScene())->Init(0);
	//m_pSceneManager->ChangeScene<IntroScene>();
	//m_pSceneManager->ChangeScene<TestScene_SSS>();
	//m_pSceneManager->ChangeScene<InGameScene>();
#endif // DEBUG
}

void GameProcess::Update()
{
	//����� Ȯ�ο�.
	if (KEYBORAD->KeyDonw(VK_F5))
		DebugRectOnOff();
	// �ð� �Լ� ������Ʈ
	m_Time->Update();
	// Ű �Է� ������Ʈ
	KEYBORAD->Update();
	// �� ������Ʈ
	m_pSceneManager->GetScene()->Update();
	// ����Ŵ��� ������Ʈ
	m_pSoundManager->Update();
}

void GameProcess::Render()
{
	// ���� �׸��� ����
	m_Engine->BeginRender();
	string fps = to_string(m_Time->GetFPS());
	// �� ����
	m_pSceneManager->GetScene()->Render(m_Engine);
	//������ ǥ�ÿ�.
	if (GetDebugMod())
		m_Engine->DrawString(10, 10, "FPS: " + fps, 24, 0x00FFFFFF);
	// ���� ����
	m_Engine->EndRender();

	m_pSceneManager->DeleteScene();

}

// ���ҽ��Ŵ����� ����Ŵ����� �̿��ؼ� ��� �����Ŭ���� �ε��Ѵ�.
void GameProcess::LoadSoundAll()
{
	/// �̰� �ƹ������� ���Ⱑ ��ġ�� �ƴѵ�,
	/// 
	/// 1. ���ҽ��Ŵ����� ����Ŵ����� �����Ѵ�. 
	/// (���� ���� �� ������, �� ����� ���ҽ��Ŵ����� ��Ÿ������ �ε��ϴ� ���̴�.)
	/// (��� ��������Ʈ�� ���� �׷����� �ʴ�.)
	/// 
	/// 2. ���� �Ŵ����� ���ҽ��Ŵ����κ��� ���� ���ҽ��� map�� ���·� ���޵Ǿ �е��� �Ѵ�.
	/// (���� �Ŵ����� interface�� ���� ���������� �ȴ�..)
	/// 
	/// 3. ����Ŵ����� �ε� �Լ��� ���ҽ��Ŵ����� �����ؼ� �ε��ϵ��� �Ѵ�.
	/// (�Լ�������, �Լ���, ���ٽ� ��� ������ ���� �ʴ´�. �������� �˱� ��ƴ�.)
	/// 
	/// 4. ����Ŵ����� ���ҽ��Ŵ����� ���ķ� ����, �� �ٸ� �����ϴ� ������ �����͸� �����Ѵ�.
	/// (����. Ÿ �Ŵ����� Ŭ�������� ���� ����Ŵ����� ���⿡�� �����ǰ� Update�Ǵ� ���� �´� ��. )
	/// 
	/// ���Ӽ��� ���� ���ؼ� �̰����� �� �� ������ �ϴ� ���ҽ��Ŵ����� ���ҽ��� ��� �������� �ʴ� ���¿����� ��¿ �� ����.

	auto _audioClipsAll = ResourceManager::Instance()->GetAudioClipsAll();

	for (auto kvp : _audioClipsAll)
	{
		AudioClip* _audioClip = static_cast<AudioClip*>(kvp.second);
		m_pSoundManager->LoadSoundFile((std::string)kvp.first, _audioClip->m_MetaFilePath, _audioClip->m_Mode);
	}
}

void GameProcess::ChangeDisPlay(HWND _hwnd, int Width, int Height)
{
	DEVMODE mode;
	mode.dmBitsPerPel = 16;   // 16��Ʈ Į��� ����
	mode.dmPelsWidth = Width;
	mode.dmPelsHeight = Height;
	mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&mode, CDS_FULLSCREEN);
	ShowWindow(_hwnd, SW_SHOWMAXIMIZED);

}


