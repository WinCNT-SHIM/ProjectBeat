#pragma once
#include <vector>

using namespace std;
class GameObject;


/// <summary>
/// ������ �ܼ��ϰ� ������
/// ������ ������!
/// 2022-01-13 �ż���
/// </summary>
/// 
class D2DEngine;

class ObjectManager
{

public:
	ObjectManager();
	~ObjectManager();
public:

	vector<GameObject*> m_vectorObjects;
	vector<GameObject*> m_AllColliderObjects;

public:
	//���̾� sort�� ���� ���� �Լ�.
	static bool cmp(GameObject* A,GameObject* B);
	//��ü ����
	void InsertObject(GameObject* obj);
	void InsertObjectAll(GameObject* parent);
	void LayerSort();
	//���� �������� ������Ʈ�� �����ؾ��� ���.. �Ⱦ��°��� ��õ
	void PushBackObject(GameObject* obj);

	//Ư�� ��ü ����
	void DeleteObject(GameObject* obj);
	//��ü ����
	void DeleteAll();

	void Update();
	void Render(D2DEngine* _pEngine);
private:
	vector<GameObject*> m_DeleteObjects; //���� ���� ������Ʈ��.
	vector<GameObject*> m_InsertObjects; //�߰� ���� ������Ʈ��.
};

