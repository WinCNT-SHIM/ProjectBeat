#pragma once
#include <vector>

using namespace std;
class GameObject;


/// <summary>
/// 구조를 단순하게 만들어보자
/// 엔진을 만들자!
/// 2022-01-13 신성현
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
	//레이어 sort를 위해 만든 함수.
	static bool cmp(GameObject* A,GameObject* B);
	//객체 생성
	void InsertObject(GameObject* obj);
	void InsertObjectAll(GameObject* parent);
	void LayerSort();
	//만약 동적으로 오브젝트를 생성해야할 경우.. 안쓰는것을 추천
	void PushBackObject(GameObject* obj);

	//특정 객체 삭제
	void DeleteObject(GameObject* obj);
	//전체 삭제
	void DeleteAll();

	void Update();
	void Render(D2DEngine* _pEngine);
private:
	vector<GameObject*> m_DeleteObjects; //삭제 예정 오브젝트들.
	vector<GameObject*> m_InsertObjects; //추가 예정 오브젝트들.
};

