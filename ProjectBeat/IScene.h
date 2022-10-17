#pragma once
#include <vector>

class GameObject;
class D2DEngine;
class ObjectManager;

using namespace std;

/// <summary>
/// ���� ������..
/// ��...
/// 
/// 
/// �߰� �ּ�
/// ī�޶�� ������Ʈ �Ŵ����� 0��(m_Layer�� 0)���� ������
/// 2022.02.13 �ɽ¼�
/// </summary>
/// 

class IScene
{
public:
	IScene();
	virtual ~IScene();
private:
	//������Ʈ �����ּ���~
	ObjectManager* m_ObjManager;
public:
	virtual void Start() {};
	virtual void Update() abstract;
	virtual void Render(D2DEngine* m_Engine) abstract;

	ObjectManager* GetObjManager();

};
