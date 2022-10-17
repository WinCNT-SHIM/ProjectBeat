#include "GamePCH.h"
#include "TESTHuman.h"




/// <summary>
/// 하드코딩의 결정체
/// </summary>

TESTHuman::TESTHuman(Vector2D _pos /*= Vector2D(0, 0)*/, Vector2D _Rotate /*= Vector2D(1, 0)*/,
	Vector2D _Scale /*= Vector2D(1, 1)*/, string _teg) : GameObject()
{
	m_Pyhsics->SetDynamic(true);
	Vector2D rc(40, 30);
	//허리는 밖에서 생성..
	CreateParts(Vector2D(0, -60), rc, _Rotate, _Scale, Vector2D(0, 0), 0, "waist");
	//왼다리
	rc = Vector2D(30, 60);
	CreateParts(Vector2D(-20, 0), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, -50), 1, "LEG1");
	rc = Vector2D(10, 30);
	CreateParts(Vector2D(0, 70), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, -20), 2, "LEG2");
	rc = Vector2D(30, 20);
	CreateParts(Vector2D(10, 30), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(-10, 0), 3, "FOOT1");
	rc = Vector2D(20, 20);
	CreateParts(Vector2D(30, 0), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(-10, 0), 4, "FOOT2");
	//오른다리
	rc = Vector2D(30, 60);
	CreateParts(Vector2D(20, 0), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, -50), 1, "LEG1");//4 허리에 이어주기 위함.
	rc = Vector2D(10, 30);
	CreateParts(Vector2D(0, 70), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, -20), 6, "LEG2");
	rc = Vector2D(30, 20);
	CreateParts(Vector2D(10, 30), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(-10, 0), 7, "FOOT1");
	rc = Vector2D(20, 20);
	CreateParts(Vector2D(30, 0), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(-10, 0), 8, "FOOT2");
	//상체
	rc = Vector2D(50, 70);
	CreateParts(Vector2D(0, -100), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, 100), 1, "BODY");

	//왼팔
	rc = Vector2D(10, 20);
	CreateParts(Vector2D(-30, -20), rc, Vector2D(0, 1), Vector2D(1, 1), Vector2D(0, -10), 10, "ARM1");
	rc = Vector2D(10, 20);
	CreateParts(Vector2D(0, 30), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, -10), 11, "ARM2");
	rc = Vector2D(40, 50);
	CreateParts(Vector2D(0, 50), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, 0), 12, "HAND");

	//오른팔
	rc = Vector2D(10, 20);
	CreateParts(Vector2D(30, -20), rc, Vector2D(0, -1), Vector2D(1, 1), Vector2D(0, -10), 10, "ARM1"); //상체에 붙이기 위함
	CreateParts(Vector2D(0, 30), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, -10), 14, "ARM2");
	rc = Vector2D(40, 50);
	CreateParts(Vector2D(0, 50), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, 0), 15, "HAND");

	//머리
	rc = Vector2D(60, 60);
	CreateParts(Vector2D(0, -120), rc, Vector2D(1, 0), Vector2D(1, 1), Vector2D(0, 40), 10, "HEAD");


	for (auto iter : m_MyParts)
	{
		iter->m_teg = _teg;
	}
}

TESTHuman::~TESTHuman()
{

}



void TESTHuman::CreateParts(Vector2D _pos, Vector2D rc, Vector2D _Gradient, Vector2D _Scale, Vector2D _Pivot, int _num, string spriteName)
{
	//마지막에 생성된 오브젝트를 부모로 한다.
	vector<GameObject*> temp = GameProcess::m_pSceneManager->GetScene()->GetObjManager()->m_vectorObjects;
	OBBObject* A = new OBBObject(_pos, rc, _Gradient, _Scale, _Pivot);
	A->SetLayer(_num);
	GameProcess::m_pSceneManager->GetScene()->GetObjManager()->InsertObject(A);
	if (_num > 0)
		A->SetParent(m_MyParts[_num - 1]);
	else
		A->SetParent(this);

	m_MyParts.push_back(A);




	SpriteRenderer* _spriteRenderer = A->AddComponent<SpriteRenderer>();
	//_spriteRenderer->Init("0001_Ball_Sheet", spriteName, &A->m_RT); //될까?


}
