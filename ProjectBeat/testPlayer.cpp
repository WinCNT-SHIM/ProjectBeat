#include "GamePCH.h"
#include "testPlayer.h"
#include "ActionComponent.h"
#include "CharactorInfoComponent.h"
#include "MoveComponent.h"
#include "StateComponent.h"
#include "CommandComponent.h"

testPlayer::testPlayer(Vector2D _pos, float _Radius, unsigned char up, unsigned char down, unsigned char left, unsigned char right, unsigned char punch, unsigned char kick) : GameObject(_pos)
{
	ActionComponent* cp_action = AddComponent<ActionComponent>();
	MoveComponent* cp_move = AddComponent<MoveComponent>();
	CharactorInfoComponent* cp_Cinfo = AddComponent<CharactorInfoComponent>();
	StateComponent* cp_state = AddComponent<StateComponent>();
	cp_Cinfo->Init(0);
	cp_move->Init(cp_Cinfo->getSpeed(),up, down, left, right);
	cp_action->Init(punch, kick);
	
	CommandComponent* cp_command = AddComponent<CommandComponent>();


	CircleCollider* Instance = AddComponent<CircleCollider>();
	AddComponent<CircleRender>()->Init(_Radius);
	collider = Instance;
	Instance->Init(_Radius);
	m_Pyhsics = AddComponent<Physics>();
	AddComponent<CircleRender>()->Init(_Radius);
}

testPlayer::~testPlayer()
{

}
