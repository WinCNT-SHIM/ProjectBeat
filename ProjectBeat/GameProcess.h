#pragma once
#include <Windows.h>

class ResourceManager;
class D2DEngine;
class IScene;
class CPlayerInput;
class CTime;
class SceneManager;
class ISoundManager;

class GameProcess
{
public:
	GameProcess();
	~GameProcess();

private:
	D2DEngine* m_Engine;
	CPlayerInput* m_Input;
	CTime* m_Time;

public:
	void Initialize(HWND hWnd);
	void Update();
	void Render();

private:
	void LoadSoundAll();
	void ChangeDisPlay(HWND _hwnd,int Width, int Height);
public:
	static SceneManager* m_pSceneManager;

	static ObjectManager* GetGameObjectManager()
	{
		return m_pSceneManager->GetScene()->GetObjManager();
	}

	static ISoundManager* m_pSoundManager;
};

