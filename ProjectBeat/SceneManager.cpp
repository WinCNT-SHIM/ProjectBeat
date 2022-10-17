#include "GamePCH.h"
#include "IntroScene.h"
#include "TestScene.h"
#include "TestScene2.h"
#include "TestAnimatorScene.h"

SceneManager::SceneManager()
{
	Init();
}

SceneManager::~SceneManager()
{
	if (m_pScene != nullptr)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
}

void SceneManager::Init()
{

}

IScene* SceneManager::GetScene()
{
	return m_pScene;
}

void SceneManager::DeleteScene()
{
	if (!m_DeleteScene.empty())
	{
		delete m_DeleteScene.back();
		m_DeleteScene.clear();
	}
}

void SceneManager::PopScene()
{
	if (m_pScene)
		m_DeleteScene.push_back(m_pScene);
	m_pScene = m_SceneStack.top();
}
