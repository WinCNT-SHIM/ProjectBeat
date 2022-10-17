#pragma once
#include <vector>

class GameObject;
class D2DEngine;
class ObjectManager;

using namespace std;

/// <summary>
/// 씬을 만들자..
/// 씬...
/// 
/// 
/// 추가 주석
/// 카메라는 오브젝트 매니저에 0번(m_Layer도 0)으로 넣을것
/// 2022.02.13 심승수
/// </summary>
/// 

class IScene
{
public:
	IScene();
	virtual ~IScene();
private:
	//업데이트 돌려주세용~
	ObjectManager* m_ObjManager;
public:
	virtual void Start() {};
	virtual void Update() abstract;
	virtual void Render(D2DEngine* m_Engine) abstract;

	ObjectManager* GetObjManager();

};
