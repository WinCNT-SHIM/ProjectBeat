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
	////엔진 생성 및 초기화
	m_Engine = new D2DEngine(hWnd);
	m_Engine->Initialize();
	m_Time = new CTime();
	m_Time->Initialize();
	m_Input = new CPlayerInput(hWnd);
	m_pSceneManager = new SceneManager();
	m_pSoundManager = ::GetSoundManager();
	m_pSoundManager->Initialize();
	LoadSoundAll();	// 내부에서 리소스 매니저 사용함. D2D엔진에서 리소스매니저를 초기화하는데, 시점을 명시 해 놓아야 할 것 같다.
	m_pSceneManager->ChangeScene<IntroScene>();
	//m_pSceneManager->ChangeScene<InGameScene>();
	//dynamic_cast<InGameScene*>(m_pSceneManager->GetScene())->Init(0,1);
	// 그래픽스 엔진 카메라의 초기화
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
	//디버그 확인용.
	if (KEYBORAD->KeyDonw(VK_F5))
		DebugRectOnOff();
	// 시간 함수 업데이트
	m_Time->Update();
	// 키 입력 업데이트
	KEYBORAD->Update();
	// 씬 업데이트
	m_pSceneManager->GetScene()->Update();
	// 사운드매니저 업데이트
	m_pSoundManager->Update();
}

void GameProcess::Render()
{
	// 렌더 그리기 시작
	m_Engine->BeginRender();
	string fps = to_string(m_Time->GetFPS());
	// 씬 렌더
	m_pSceneManager->GetScene()->Render(m_Engine);
	//프레임 표시용.
	if (GetDebugMod())
		m_Engine->DrawString(10, 10, "FPS: " + fps, 24, 0x00FFFFFF);
	// 렌더 종료
	m_Engine->EndRender();

	m_pSceneManager->DeleteScene();

}

// 리소스매니저와 사운드매니저를 이용해서 모든 오디오클립을 로드한다.
void GameProcess::LoadSoundAll()
{
	/// 이거 아무리봐도 여기가 위치가 아닌데,
	/// 
	/// 1. 리소스매니저가 사운드매니저를 포함한다. 
	/// (가장 옳은 것 같은데, 현 설계는 리소스매니저가 메타정보만 로드하는 식이다.)
	/// (사실 스프라이트를 보면 그렇지도 않다.)
	/// 
	/// 2. 사운드 매니저에 리소스매니저로부터 읽은 리소스가 map의 형태로 전달되어서 읽도록 한다.
	/// (사운드 매니저의 interface가 완전 더럽혀져서 싫다..)
	/// 
	/// 3. 사운드매니저의 로드 함수를 리소스매니저로 전달해서 로드하도록 한다.
	/// (함수포인터, 함수자, 람다식 모두 마음에 들지 않는다. 무엇보다 알기 어렵다.)
	/// 
	/// 4. 사운드매니저와 리소스매니저를 병렬로 놓고, 둘 다를 포함하는 곳에서 데이터를 전달한다.
	/// (현행. 타 매니저급 클래스들을 보면 사운드매니저가 여기에서 생성되고 Update되는 것이 맞는 듯. )
	/// 
	/// 종속성을 막기 위해서 이것저것 쓸 수 있지만 일단 리소스매니저가 리소스를 모두 관리하지 않는 상태에서는 어쩔 수 없다.

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
	mode.dmBitsPerPel = 16;   // 16비트 칼라로 변경
	mode.dmPelsWidth = Width;
	mode.dmPelsHeight = Height;
	mode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
	ChangeDisplaySettings(&mode, CDS_FULLSCREEN);
	ShowWindow(_hwnd, SW_SHOWMAXIMIZED);

}


