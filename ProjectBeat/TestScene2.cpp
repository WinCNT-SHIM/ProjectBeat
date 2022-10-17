#include "GamePCH.h"
#include "TestScene2.h"
#include "TESTHuman.h"
#include "Effect.h"
#include "ParticleManager.h"

TestScene2::TestScene2() : IScene()
{
	/*GetObjManager()->InsertObject(new OBBObject(Vector2D(50, 50), Vector2D(30, 30), Vector2D(0, 1), Vector2D(1, 1), Vector2D(0, 0)));
	GetObjManager()->InsertObject(new OBBObject(Vector2D(250, 250), Vector2D(30, 30), Vector2D(0, 1), Vector2D(1, 1), Vector2D(0, 0)));*/

	//GetObjManager()->InsertObject(new RectObject(Vector2D(50, 50), Vector2D(30, 30)));
	//GetObjManager()->InsertObject(new RectObject(Vector2D(250, 250), Vector2D(30, 30)));
	//GetObjManager()->InsertObject(new CircleObject(Vector2D(50, 50), 30));


}

TestScene2::~TestScene2()
{
}

void TestScene2::Start()
{
	ParticleManager::Init();

	
	GameObject* _temp = new OBBObject(Vector2D(120, 120), Vector2D(50, 50));
	GetObjManager()->InsertObject(_temp);

	GameObject* _temp3 = new OBBObject(Vector2D(100, 100), Vector2D(40, 40));
	GetObjManager()->InsertObject(_temp3);

	GameObject* _temp4 = new OBBObject(Vector2D(100, 100), Vector2D(40, 40));
	GetObjManager()->InsertObject(_temp4);

	_temp->SetLocalScaleVector(-2,1);

	_temp3->SetParent(_temp);
	_temp4->SetParent(_temp3);

	 _temp = new OBBObject(Vector2D(120, 120), Vector2D(50, 50));
	GetObjManager()->InsertObject(_temp);

	_temp3 = new OBBObject(Vector2D(100, 100), Vector2D(40, 40));
	GetObjManager()->InsertObject(_temp3);

	_temp4 = new OBBObject(Vector2D(100, 100), Vector2D(40, 40));
	GetObjManager()->InsertObject(_temp4);

	_temp->SetLocalScaleVector(1, 1);

	_temp3->SetParent(_temp);
	_temp4->SetParent(_temp3);
}

void TestScene2::Update()
{
	GetObjManager()->Update();

	Vector2D _tr = GetObjManager()->m_AllColliderObjects[0]->m_tr->GetWorldTranslate();
	if (KEYBORAD->KeyPress(VK_UP))
		GetObjManager()->m_AllColliderObjects[0]->m_tr->SetWorldTranslateVector(Vector2D(_tr.x, _tr.y - 1));
	if (KEYBORAD->KeyPress(VK_DOWN))
		GetObjManager()->m_AllColliderObjects[0]->m_tr->SetWorldTranslateVector(Vector2D(_tr.x, _tr.y + 1));
	if (KEYBORAD->KeyPress(VK_LEFT))
		GetObjManager()->m_AllColliderObjects[0]->m_tr->SetWorldTranslateVector(Vector2D(_tr.x - 1, _tr.y));
	if (KEYBORAD->KeyPress(VK_RIGHT))
		GetObjManager()->m_AllColliderObjects[0]->m_tr->SetWorldTranslateVector(Vector2D(_tr.x + 1, _tr.y));

	if (KEYBORAD->KeyDonw(VK_SPACE))
		GameProcess::m_pSceneManager->PopScene();
	if (KEYBORAD->KeyPress(VK_RETURN))
		GetObjManager()->m_AllColliderObjects[0]->m_tr->SetLocalRotateVector(Vector2D(GetObjManager()->m_AllColliderObjects[0]->GetLocalRotate().x, GetObjManager()->m_AllColliderObjects[0]->GetLocalRotate().y+0.1f));

	if (KEYBORAD->KeyPress(VK_LBUTTON))
		ParticleManager::Play(true,1,KEYBORAD->GetPos(), Particle::Effect);
}

void TestScene2::Render(D2DEngine* m_Engine)
{
	GetObjManager()->Render(m_Engine);
}
