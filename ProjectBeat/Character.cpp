#include "GamePCH.h"
#include "Character.h"
#include "Animator.h"
#include "ActionComponent.h"
#include "CharactorInfoComponent.h"
#include "MoveComponent.h"
#include "CommandComponent.h"
#include "StateComponent.h"
#include "DeBugPrint.h"
#include "HitDetect.h"
#include "TestHumanCtrl.h"
#include "AnimEventComponent.h"
#include "ParticleManager.h"

std::string sheetNames[4] = 
{
	"0024_Drum_Spritesheets",
	"0026_Synth_Spritesheets",
	"0025_Guitar_Spritesheets",
	"0027_Tambourine_Spritesheets"
};

std::string spriteNames[4][17] =
{
	{
		"Drum_Waist Sprite1",
		"Drum_Body Sprite1",
		"Drum_Head Sprite1",
		"Drum_RightUpperArm Sprite1",
		"Drum_RightLowerArm Sprite1",
		"Drum_RightHand Sprite1",
		"Drum_LeftUpperArm Sprite1",
		"Drum_LeftLowerArm Sprite1",
		"Drum_LeftHand Sprite1",
		"Drum_RightUpperLeg Sprite1",
		"Drum_RightLowerLeg Sprite1",
		"Drum_RightFoot Sprite1",
		"Drum_RightTiptoe Sprite1",
		"Drum_LeftUpperLeg Sprite1",
		"Drum_LeftLowerLeg Sprite1",
		"Drum_LeftFoot Sprite1",
		"Drum_LeftTiptoe Sprite1"
	},
	{
		"Synth_Waist Sprite1",
		"Synth_Body Sprite1",
		"Synth_Head Sprite1",
		"Synth_RightUpperArm Sprite1",
		"Synth_RightLowerArm Sprite1",
		"Synth_RightHand Sprite1",
		"Synth_LeftUpperArm Sprite1",
		"Synth_LeftLowerArm Sprite1",
		"Synth_LeftHand Sprite1",
		"Synth_RightUpperLeg Sprite1",
		"Synth_RightLowerLeg Sprite1",
		"Synth_RightFoot Sprite1",
		"Synth_RightTiptoe Sprite1",
		"Synth_LeftUpperLeg Sprite1",
		"Synth_LeftLowerLeg Sprite1",
		"Synth_LeftFoot Sprite1",
		"Synth_LeftTiptoe Sprite1"
	},
	{
		"Guitar_Waist Sprite1",
		"Guitar_Body Sprite1",
		"Guitar_Head Sprite1",
		"Guitar_RightUpperArm Sprite1",
		"Guitar_RightLowerArm Sprite1",
		"Guitar_RightHand Sprite1",
		"Guitar_LeftUpperArm Sprite1",
		"Guitar_LeftLowerArm Sprite1",
		"Guitar_LeftHand Sprite1",
		"Guitar_RightUpperLeg Sprite1",
		"Guitar_RightLowerLeg Sprite1",
		"Guitar_RightFoot Sprite1",
		"Guitar_RightTiptoe Sprite1",
		"Guitar_LeftUpperLeg Sprite1",
		"Guitar_LeftLowerLeg Sprite1",
		"Guitar_LeftFoot Sprite1",
		"Guitar_LeftTiptoe Sprite1"
	},
	{
		"Tambourine_Waist Sprite1",
		"Tambourine_Body Sprite1",
		"Tambourine_Head Sprite1",
		"Tambourine_RightUpperArm Sprite1",
		"Tambourine_RightLowerArm Sprite1",
		"Tambourine_RightHand Sprite1",
		"Tambourine_LeftUpperArm Sprite1",
		"Tambourine_LeftLowerArm Sprite1",
		"Tambourine_LeftHand Sprite1",
		"Tambourine_RightUpperLeg Sprite1",
		"Tambourine_RightLowerLeg Sprite1",
		"Tambourine_RightFoot Sprite1",
		"Tambourine_RightTiptoe Sprite1",
		"Tambourine_LeftUpperLeg Sprite1",
		"Tambourine_LeftLowerLeg Sprite1",
		"Tambourine_LeftFoot Sprite1",
		"Tambourine_LeftTiptoe Sprite1"
	}
};

Character::Character(string _teg,
	unsigned char up, unsigned char down, unsigned char left, unsigned char right,
	unsigned char punch, unsigned char kick, unsigned int characterType)
{
	m_teg = _teg;
	AABBCollider* instance = AddComponent<AABBCollider>();
	collider = instance;
	instance->Init(Vector2D(100, 200));

	m_Pyhsics = AddComponent<Physics>();
	m_Pyhsics->init(ColliderType::AABB);
	m_Pyhsics->SetDynamic(true);
	AddComponent<RectRender>()->Init(-100, -200, 100, 200);

	Animator* cp_anim = AddComponent<Animator>();
	ActionComponent* cp_action = AddComponent<ActionComponent>();
	MoveComponent* cp_move = AddComponent<MoveComponent>();
	CharactorInfoComponent* cp_Cinfo = AddComponent<CharactorInfoComponent>();
	StateComponent* cp_state = AddComponent<StateComponent>();
	cp_Cinfo->Init(characterType);

	cp_move->Init(cp_Cinfo->getSpeed(), up, down, left, right);
	cp_action->Init(punch, kick);
	CommandComponent* cp_command = AddComponent<CommandComponent>();

	CharacterSpriteObject* rootObj = new CharacterSpriteObject;
	SetName("Character");
	rootObj->SetName("Root");
	rootObj->SetLocalTranslateVector(0, -50);
	rootObj->SetLayer(0);
	rootObj->SetParent(this);

	string sheetName, spriteName;

	CharacterSpriteObject* waistObj = new CharacterSpriteObject;		// Çã¸®
	waistObj->SetParent(rootObj);
	waistObj->SetLocalTranslateVector(0, -100);
	waistObj->SetName("Waist");
	waistObj->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][0]);
	waistObj->SetLayer(8);

	CharacterSpriteObject* bodyObj = new CharacterSpriteObject;		// ¸öÅë
	bodyObj->SetParent(waistObj);
	bodyObj->SetLocalTranslateVector(0, 0);
	bodyObj->SetName("Body");
	bodyObj->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][1]);
	bodyObj->SetLayer(9);

	CharacterSpriteObject* headObj = new CharacterSpriteObject;		// ¸Ó¸®
	headObj->SetParent(bodyObj);
	headObj->SetLocalTranslateVector(0, -115);
	headObj->SetName("Head");
	headObj->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][2]);
	headObj->SetLayer(14);

	CharacterSpriteObject* rightUpperArm = new CharacterSpriteObject;	// ¿À¸¥ ÆÈ¶Ò
	CharacterSpriteObject* rightLowerArm = new CharacterSpriteObject;	// ¿À¸¥ ÆÈ
	CharacterSpriteObject* rightHand = new CharacterSpriteObject;		// ¿À¸¥ ¼Õ
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

	rightUpperArm->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][3]);
	rightLowerArm->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][4]);
	rightHand->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][5]);

	CharacterSpriteObject* leftUpperArm = new CharacterSpriteObject;	// ¿Þ ÆÈ¶Ò
	CharacterSpriteObject* leftLowerArm = new CharacterSpriteObject;	// ¿Þ ÆÈ
	CharacterSpriteObject* leftHand = new CharacterSpriteObject;		// ¿Þ ¼Õ
	leftUpperArm->SetParent(bodyObj);
	leftLowerArm->SetParent(leftUpperArm);
	leftHand->SetParent(leftLowerArm);
	leftUpperArm->SetLocalTranslateVector(20, -90);
	leftLowerArm->SetLocalTranslateVector(5, 35);
	leftHand->SetLocalTranslateVector(0, 40);
	leftUpperArm->SetName("LeftUpperArm");
	leftLowerArm->SetName("LeftLowerArm");
	leftHand->SetName("LeftHand");

	leftUpperArm->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][6]);
	leftLowerArm->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][7]);
	leftHand->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][8]);

	leftUpperArm->SetLayer(1);
	leftLowerArm->SetLayer(2);
	leftHand->SetLayer(3);

	CharacterSpriteObject* rightUpperLeg = new CharacterSpriteObject; // ¿À¸¥ Çã¹÷Áö
	CharacterSpriteObject* rightLowerLeg = new CharacterSpriteObject; // ¿À¸¥ Á¾¾Æ¸®
	CharacterSpriteObject* rightfoot = new CharacterSpriteObject;		// ¿À¸¥ ¹ß
	CharacterSpriteObject* righttiptoe = new CharacterSpriteObject;	// ¿À¸¥ ¹ß³¡
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

	rightUpperLeg->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][9]);
	rightLowerLeg->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][10]);
	rightfoot->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][11]);
	righttiptoe->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][12]);

	rightUpperLeg->SetLayer(10);
	rightLowerLeg->SetLayer(11);
	rightfoot->SetLayer(12);
	righttiptoe->SetLayer(13);

	CharacterSpriteObject* leftUpperLeg = new CharacterSpriteObject;	// ¿Þ Çã¹÷Áö
	CharacterSpriteObject* leftLowerLeg = new CharacterSpriteObject;	// ¿Þ Á¾¾Æ¸®
	CharacterSpriteObject* leftfoot = new CharacterSpriteObject;		// ¿Þ ¹ß
	CharacterSpriteObject* lefttiptoe = new CharacterSpriteObject;	// ¿Þ ¹ß³¡

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

	leftUpperLeg->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][13]);
	leftLowerLeg->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][14]);
	leftfoot->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][15]);
	lefttiptoe->sr->SetSprite(sheetNames[characterType], spriteNames[characterType][16]);

	leftUpperLeg->SetLayer(4);
	leftLowerLeg->SetLayer(5);
	leftfoot->SetLayer(6);
	lefttiptoe->SetLayer(7);

	cp_anim->Init(ResourceManager::Instance()->GetAnimationController("HumanAnimatorController"));

	cp_anim->_animatorController->_currAnimationNode = &cp_anim->_animatorController->_nodes["idle"];
	SetChildsTeg(_teg);

	rootObj->AddComponent<TestHumanCtrl>();
	this->AddComponent<AnimEventComponent>();


}

Character::~Character()
{
}

void Character::Update()
{
	//ÀÌ Ä£±¸ ÇÏ³ª Á¤Áö ½ÃÅ°±âÀ§ÇØ ÀÌ·¸°Ô ¾÷µ¥ÀÌÆ®¸¦ ¿­¾î¹ö·Áµµ µÇ´Â°É±î?
	if (GameManager::Instance()->GetPause()) return;
	GameObject::Update();
}

void Character::Start(GameObject* target, int index)
{
	GetComponent<CharactorInfoComponent>()->setTarget(target);
	GetComponent<CharactorInfoComponent>()->playerIndex=index;
}
void Character::Setting(int idx)
{
}
CharacterSpriteObject::CharacterSpriteObject()
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
	AddComponent<HitDetect>();

}

CharacterSpriteObject::~CharacterSpriteObject()
{
}





