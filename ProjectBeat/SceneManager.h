#pragma once
#include <stack>

class IScene;

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

private:
	IScene* m_pScene = nullptr;

	vector<IScene*>m_DeleteScene; //씬 변경하며 이전 씬 삭제 시 사용.

public:
	stack<IScene*>m_SceneStack; //삭제 안하고 잠시 변경만 할 때 사용. 

	void Init();

	IScene* GetScene();

	template<class TScene>
	void ChangeScene(); // 씬 삭제 후 변경.
	void DeleteScene(); // m_DeleteScene에 값이 있을 경우 삭제.


	template<class TScene>
	void PushScene(); // 삭제 안하고 잠시 변경만 할 때 사용. 
	void PopScene(); // 현재 씬 삭제후 이전에 사용했던 씬으로 변경
};

template<class TScene>
inline void SceneManager::ChangeScene()
{
	if (m_pScene)
		m_DeleteScene.push_back(m_pScene);
	m_pScene = new TScene();
	m_pScene->Start();
}

template<class TScene>
inline void SceneManager::PushScene()
{
	if (m_pScene)
		m_SceneStack.push(m_pScene);
	m_pScene = new TScene();
	m_pScene->Start();
}
