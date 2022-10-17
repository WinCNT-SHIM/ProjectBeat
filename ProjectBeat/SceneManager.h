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

	vector<IScene*>m_DeleteScene; //�� �����ϸ� ���� �� ���� �� ���.

public:
	stack<IScene*>m_SceneStack; //���� ���ϰ� ��� ���游 �� �� ���. 

	void Init();

	IScene* GetScene();

	template<class TScene>
	void ChangeScene(); // �� ���� �� ����.
	void DeleteScene(); // m_DeleteScene�� ���� ���� ��� ����.


	template<class TScene>
	void PushScene(); // ���� ���ϰ� ��� ���游 �� �� ���. 
	void PopScene(); // ���� �� ������ ������ ����ߴ� ������ ����
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
