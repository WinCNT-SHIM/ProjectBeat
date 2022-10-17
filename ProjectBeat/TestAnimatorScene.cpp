#include "GamePCH.h"
#include "TestAnimatorScene.h"
#include "TestAnimationObject.h"

#include "../Engine/Animator.h"

TestAnimatorScene::TestAnimatorScene()
{
	TestAnimationObject* testObj = new TestAnimationObject(250, 600);
	TestAnimationObject* testObj2 = new TestAnimationObject(800, 600, 0);
	GetObjManager()->InsertObject(testObj);

	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(0)->GetChild(2)); //left upper arm
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(0)->GetChild(2)->GetChild(0)); // left lower arm
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(0)->GetChild(2)->GetChild(0)->GetChild(0)); // left hand

	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(2)); // left upper leg
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(2)->GetChild(0)); // left lower leg
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(2)->GetChild(0)->GetChild(0)); // left foot
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(2)->GetChild(0)->GetChild(0)->GetChild(0)); // left tiptoe

	GetObjManager()->InsertObject(testObj->GetChild(0)); // waist
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(0)); // body

	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(1)); // right upper leg
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(1)->GetChild(0)); // right lower leg
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(1)->GetChild(0)->GetChild(0)); // right foot
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(1)->GetChild(0)->GetChild(0)->GetChild(0)); // right tiptoe

	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(0)->GetChild(0)); // head

	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(0)->GetChild(1)); // right upper arm
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(0)->GetChild(1)->GetChild(0)); // right lower arm
	GetObjManager()->InsertObject(testObj->GetChild(0)->GetChild(0)->GetChild(1)->GetChild(0)->GetChild(0)); // right hand

	GetObjManager()->InsertObject(testObj2);

	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(0)->GetChild(2)); //left upper arm
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(0)->GetChild(2)->GetChild(0)); // left lower arm
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(0)->GetChild(2)->GetChild(0)->GetChild(0)); // left hand

	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(2)); // left upper leg
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(2)->GetChild(0)); // left lower leg
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(2)->GetChild(0)->GetChild(0)); // left foot
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(2)->GetChild(0)->GetChild(0)->GetChild(0)); // left tiptoe

	GetObjManager()->InsertObject(testObj2->GetChild(0)); // waist
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(0)); // body

	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(1)); // right upper leg
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(1)->GetChild(0)); // right lower leg
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(1)->GetChild(0)->GetChild(0)); // right foot
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(1)->GetChild(0)->GetChild(0)->GetChild(0)); // right tiptoe

	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(0)->GetChild(0)); // head

	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(0)->GetChild(1)); // right upper arm
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(0)->GetChild(1)->GetChild(0)); // right lower arm
	GetObjManager()->InsertObject(testObj2->GetChild(0)->GetChild(0)->GetChild(1)->GetChild(0)->GetChild(0)); // right hand

}

TestAnimatorScene::~TestAnimatorScene()
{
}

void TestAnimatorScene::Update()
{
	GetObjManager()->Update();
}

void TestAnimatorScene::Render(D2DEngine* m_Engine)
{
	GetObjManager()->Render(m_Engine);
}
