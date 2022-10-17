#include "GamePCH.h"
#include "TestAnimationObject.h"
#include "../Engine/SpriteRenderer.h"
#include "../Engine/Animator.h"
#include "TestHumanCtrl.h"

TestAnimationObject::TestAnimationObject(int x, int y)
{

	Animator* rootObj = AddComponent<Animator>();	// Root
	this->SetName("Root");
	this->SetLocalTranslateVector((float)x, (float)y);
	this->SetLayer(0);

	TestSpriteObject* waistObj = new TestSpriteObject;		// Çã¸®
	waistObj->SetParent(this);
	waistObj->SetLocalTranslateVector(0, -100);
	waistObj->SetName("Waist");
	waistObj->SetLayer(8);

	TestSpriteObject* bodyObj = new TestSpriteObject;		// ¸öÅë
	bodyObj->SetParent(waistObj);
	bodyObj->SetLocalTranslateVector(0, 0);
	bodyObj->SetName("Body");
	bodyObj->sr->SetSprite("Test Sheet", "Body Sprite1");
	bodyObj->SetLayer(9);

	TestSpriteObject* headObj = new TestSpriteObject;		// ¸Ó¸®
	headObj->SetParent(bodyObj);
	headObj->SetLocalTranslateVector(0, -115);
	headObj->SetName("Head");
	headObj->sr->SetSprite("Test Sheet", "Head Sprite1");
	headObj->SetLayer(14);

	TestSpriteObject* rightUpperArm = new TestSpriteObject;	// ¿À¸¥ ÆÈ¶Ò
	TestSpriteObject* rightLowerArm = new TestSpriteObject;	// ¿À¸¥ ÆÈ
	TestSpriteObject* rightHand = new TestSpriteObject;		// ¿À¸¥ ¼Õ
	rightUpperArm->SetParent(bodyObj);
	rightLowerArm->SetParent(rightUpperArm);
	rightHand->SetParent(rightLowerArm);
	rightUpperArm->SetLocalTranslateVector(-25, -90);
	rightLowerArm->SetLocalTranslateVector(5, 35);
	rightHand->SetLocalTranslateVector(0, 40);
	rightUpperArm->SetName("RightUpperArm");
	rightLowerArm->SetName("RightLowerArm");
	rightHand->SetName("RightHand");

	rightUpperArm->SetLayer(15);
	rightLowerArm->SetLayer(16);
	rightHand->SetLayer(17);

	rightUpperArm->sr->SetSprite("Test Sheet", "UpperArm Sprite1");
	rightLowerArm->sr->SetSprite("Test Sheet", "LowerArm Sprite1");
	rightHand->sr->SetSprite("Test Sheet", "Hand Sprite1");

	TestSpriteObject* leftUpperArm = new TestSpriteObject;	// ¿Þ ÆÈ¶Ò
	TestSpriteObject* leftLowerArm = new TestSpriteObject;	// ¿Þ ÆÈ
	TestSpriteObject* leftHand = new TestSpriteObject;		// ¿Þ ¼Õ
	leftUpperArm->SetParent(bodyObj);
	leftLowerArm->SetParent(leftUpperArm);
	leftHand->SetParent(leftLowerArm);
	leftUpperArm->SetLocalTranslateVector(20, -90);
	leftLowerArm->SetLocalTranslateVector(5, 35);
	leftHand->SetLocalTranslateVector(0, 40);
	leftUpperArm->SetName("LeftUpperArm");
	leftLowerArm->SetName("LeftLowerArm");
	leftHand->SetName("LeftHand");

	leftUpperArm->sr->SetSprite("Test Sheet", "UpperArm Sprite1");
	leftLowerArm->sr->SetSprite("Test Sheet", "LowerArm Sprite1");
	leftHand->sr->SetSprite("Test Sheet", "Hand Sprite1");

	leftUpperArm->SetLayer(1);
	leftLowerArm->SetLayer(2);
	leftHand->SetLayer(3);

	TestSpriteObject* rightUpperLeg = new TestSpriteObject; // ¿À¸¥ Çã¹÷Áö
	TestSpriteObject* rightLowerLeg = new TestSpriteObject; // ¿À¸¥ Á¾¾Æ¸®
	TestSpriteObject* rightfoot = new TestSpriteObject;		// ¿À¸¥ ¹ß
	TestSpriteObject* righttiptoe = new TestSpriteObject;	// ¿À¸¥ ¹ß³¡
	rightUpperLeg->SetParent(waistObj);
	rightLowerLeg->SetParent(rightUpperLeg);
	rightfoot->SetParent(rightLowerLeg);
	righttiptoe->SetParent(rightfoot);
	rightUpperLeg->SetLocalTranslateVector(-20, 0);
	rightLowerLeg->SetLocalTranslateVector(-5, 100);
	rightfoot->SetLocalTranslateVector(0, 50);
	righttiptoe->SetLocalTranslateVector(60, 0);
	rightUpperLeg->SetName("RightUpperLeg");
	rightLowerLeg->SetName("RightLowerLeg");
	rightfoot->SetName("RightFoot");
	righttiptoe->SetName("RightTiptoe");

	rightUpperLeg->sr->SetSprite("Test Sheet", "RightUpperLeg Sprite1");
	rightLowerLeg->sr->SetSprite("Test Sheet", "LowerLeg Sprite1");
	rightfoot->sr->SetSprite("Test Sheet", "Foot Sprite1");
	righttiptoe->sr->SetSprite("Test Sheet", "Foot Sprite2");

	rightUpperLeg->SetLayer(10);
	rightLowerLeg->SetLayer(11);
	rightfoot->SetLayer(12);
	righttiptoe->SetLayer(13);

	TestSpriteObject* leftUpperLeg = new TestSpriteObject;	// ¿Þ Çã¹÷Áö
	TestSpriteObject* leftLowerLeg = new TestSpriteObject;	// ¿Þ Á¾¾Æ¸®
	TestSpriteObject* leftfoot = new TestSpriteObject;		// ¿Þ ¹ß
	TestSpriteObject* lefttiptoe = new TestSpriteObject;	// ¿Þ ¹ß³¡

	leftUpperLeg->SetParent(waistObj);
	leftLowerLeg->SetParent(leftUpperLeg);
	leftfoot->SetParent(leftLowerLeg);
	lefttiptoe->SetParent(leftfoot);
	leftUpperLeg->SetLocalTranslateVector(20, 0);
	leftLowerLeg->SetLocalTranslateVector(0, 100);
	leftfoot->SetLocalTranslateVector(0, 50);
	lefttiptoe->SetLocalTranslateVector(60, 0);
	leftUpperLeg->SetName("LeftUpperLeg");
	leftLowerLeg->SetName("LeftLowerLeg");
	leftfoot->SetName("LeftFoot");
	lefttiptoe->SetName("LeftTiptoe");

	leftUpperLeg->sr->SetSprite("Test Sheet", "LeftUpperLeg Sprite1");
	leftLowerLeg->sr->SetSprite("Test Sheet", "LowerLeg Sprite1");
	leftfoot->sr->SetSprite("Test Sheet", "Foot Sprite1");
	lefttiptoe->sr->SetSprite("Test Sheet", "Foot Sprite2");

	leftUpperLeg->SetLayer(4);
	leftLowerLeg->SetLayer(5);
	leftfoot->SetLayer(6);
	lefttiptoe->SetLayer(7);

	rootObj->Init(ResourceManager::Instance()->GetAnimationController("HumanAnimatorController"));

	rootObj->_animatorController->_currAnimationNode = &rootObj->_animatorController->_nodes["testClip3"];


}

TestAnimationObject::TestAnimationObject(int x, int y, int z)
{
	Animator* rootObj = AddComponent<Animator>();	// Root
	this->SetName("Root");
	this->SetLocalTranslateVector((float)x, (float)y);
	this->SetLocalScaleVector(-1, 1);
	this->SetLayer(0);

	TestSpriteObject* waistObj = new TestSpriteObject;		// Çã¸®
	waistObj->SetParent(this);
	waistObj->SetLocalTranslateVector(0, -100);
	waistObj->SetName("Waist");
	waistObj->SetLayer(8);

	TestSpriteObject* bodyObj = new TestSpriteObject;		// ¸öÅë
	bodyObj->SetParent(waistObj);
	bodyObj->SetLocalTranslateVector(0, 0);
	bodyObj->SetName("Body");
	bodyObj->sr->SetSprite("Test Sheet", "Body Sprite1");
	bodyObj->SetLayer(9);

	TestSpriteObject* headObj = new TestSpriteObject;		// ¸Ó¸®
	headObj->SetParent(bodyObj);
	headObj->SetLocalTranslateVector(0, -115);
	headObj->SetName("Head");
	headObj->sr->SetSprite("Test Sheet", "Head Sprite1");
	headObj->SetLayer(14);

	TestSpriteObject* rightUpperArm = new TestSpriteObject;	// ¿À¸¥ ÆÈ¶Ò
	TestSpriteObject* rightLowerArm = new TestSpriteObject;	// ¿À¸¥ ÆÈ
	TestSpriteObject* rightHand = new TestSpriteObject;		// ¿À¸¥ ¼Õ
	rightUpperArm->SetParent(bodyObj);
	rightLowerArm->SetParent(rightUpperArm);
	rightHand->SetParent(rightLowerArm);
	rightUpperArm->SetLocalTranslateVector(-25, -90);
	rightLowerArm->SetLocalTranslateVector(5, 35);
	rightHand->SetLocalTranslateVector(0, 40);
	rightUpperArm->SetName("RightUpperArm");
	rightLowerArm->SetName("RightLowerArm");
	rightHand->SetName("RightHand");

	rightUpperArm->SetLayer(15);
	rightLowerArm->SetLayer(16);
	rightHand->SetLayer(17);

	rightUpperArm->sr->SetSprite("Test Sheet", "UpperArm Sprite1");
	rightLowerArm->sr->SetSprite("Test Sheet", "LowerArm Sprite1");
	rightHand->sr->SetSprite("Test Sheet", "Hand Sprite1");

	TestSpriteObject* leftUpperArm = new TestSpriteObject;	// ¿Þ ÆÈ¶Ò
	TestSpriteObject* leftLowerArm = new TestSpriteObject;	// ¿Þ ÆÈ
	TestSpriteObject* leftHand = new TestSpriteObject;		// ¿Þ ¼Õ
	leftUpperArm->SetParent(bodyObj);
	leftLowerArm->SetParent(leftUpperArm);
	leftHand->SetParent(leftLowerArm);
	leftUpperArm->SetLocalTranslateVector(20, -90);
	leftLowerArm->SetLocalTranslateVector(5, 35);
	leftHand->SetLocalTranslateVector(0, 40);
	leftUpperArm->SetName("LeftUpperArm");
	leftLowerArm->SetName("LeftLowerArm");
	leftHand->SetName("LeftHand");

	leftUpperArm->sr->SetSprite("Test Sheet", "UpperArm Sprite1");
	leftLowerArm->sr->SetSprite("Test Sheet", "LowerArm Sprite1");
	leftHand->sr->SetSprite("Test Sheet", "Hand Sprite1");

	leftUpperArm->SetLayer(1);
	leftLowerArm->SetLayer(2);
	leftHand->SetLayer(3);

	TestSpriteObject* rightUpperLeg = new TestSpriteObject; // ¿À¸¥ Çã¹÷Áö
	TestSpriteObject* rightLowerLeg = new TestSpriteObject; // ¿À¸¥ Á¾¾Æ¸®
	TestSpriteObject* rightfoot = new TestSpriteObject;		// ¿À¸¥ ¹ß
	TestSpriteObject* righttiptoe = new TestSpriteObject;	// ¿À¸¥ ¹ß³¡
	rightUpperLeg->SetParent(waistObj);
	rightLowerLeg->SetParent(rightUpperLeg);
	rightfoot->SetParent(rightLowerLeg);
	righttiptoe->SetParent(rightfoot);
	rightUpperLeg->SetLocalTranslateVector(-20, 0);
	rightLowerLeg->SetLocalTranslateVector(-5, 100);
	rightfoot->SetLocalTranslateVector(0, 50);
	righttiptoe->SetLocalTranslateVector(60, 0);
	rightUpperLeg->SetName("RightUpperLeg");
	rightLowerLeg->SetName("RightLowerLeg");
	rightfoot->SetName("RightFoot");
	righttiptoe->SetName("RightTiptoe");

	rightUpperLeg->sr->SetSprite("Test Sheet", "RightUpperLeg Sprite1");
	rightLowerLeg->sr->SetSprite("Test Sheet", "LowerLeg Sprite1");
	rightfoot->sr->SetSprite("Test Sheet", "Foot Sprite1");
	righttiptoe->sr->SetSprite("Test Sheet", "Foot Sprite2");

	rightUpperLeg->SetLayer(10);
	rightLowerLeg->SetLayer(11);
	rightfoot->SetLayer(12);
	righttiptoe->SetLayer(13);

	TestSpriteObject* leftUpperLeg = new TestSpriteObject;	// ¿Þ Çã¹÷Áö
	TestSpriteObject* leftLowerLeg = new TestSpriteObject;	// ¿Þ Á¾¾Æ¸®
	TestSpriteObject* leftfoot = new TestSpriteObject;		// ¿Þ ¹ß
	TestSpriteObject* lefttiptoe = new TestSpriteObject;	// ¿Þ ¹ß³¡

	leftUpperLeg->SetParent(waistObj);
	leftLowerLeg->SetParent(leftUpperLeg);
	leftfoot->SetParent(leftLowerLeg);
	lefttiptoe->SetParent(leftfoot);
	leftUpperLeg->SetLocalTranslateVector(20, 0);
	leftLowerLeg->SetLocalTranslateVector(0, 100);
	leftfoot->SetLocalTranslateVector(0, 50);
	lefttiptoe->SetLocalTranslateVector(60, 0);
	leftUpperLeg->SetName("LeftUpperLeg");
	leftLowerLeg->SetName("LeftLowerLeg");
	leftfoot->SetName("LeftFoot");
	lefttiptoe->SetName("LeftTiptoe");

	leftUpperLeg->sr->SetSprite("Test Sheet", "LeftUpperLeg Sprite1");
	leftLowerLeg->sr->SetSprite("Test Sheet", "LowerLeg Sprite1");
	leftfoot->sr->SetSprite("Test Sheet", "Foot Sprite1");
	lefttiptoe->sr->SetSprite("Test Sheet", "Foot Sprite2");

	leftUpperLeg->SetLayer(4);
	leftLowerLeg->SetLayer(5);
	leftfoot->SetLayer(6);
	lefttiptoe->SetLayer(7);

	rootObj->Init(ResourceManager::Instance()->GetAnimationController("HumanAnimatorController"));

	rootObj->_animatorController->_currAnimationNode = &rootObj->_animatorController->_nodes["testClip3"];

	AddComponent<TestHumanCtrl>();
}

TestAnimationObject::~TestAnimationObject()
{
}

TestSpriteObject::TestSpriteObject()
{
	Vector2D _rt(50, 50);
	collider = AddComponent<OBBCollider>();
	dynamic_cast<OBBCollider*>(collider)->Init(-_rt.x, -_rt.y, _rt.x, _rt.y);
	AddComponent<RectRender>()->Init(-_rt.x, -_rt.y, _rt.x, _rt.y);

	sr = AddComponent<SpriteRenderer>();
	sr->leftTop.x = -50;
	sr->leftTop.y = -50;
	sr->rightBot.x = 50;
	sr->rightBot.y = 50;
}

TestSpriteObject::~TestSpriteObject()
{
}
