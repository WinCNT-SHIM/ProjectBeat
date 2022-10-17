#pragma once
#include "Component.h"
#include "StateComponent.h"
#include "CharactorInfoComponent.h"


class MoveComponent :
	public Component
{
public:
	MoveComponent(GameObject* _GameObject);
	virtual ~MoveComponent();
	virtual void SetName() { m_Name = "MoveComponent"; }

private:
	int direction = 1;
	float gravity = -1;
	bool IsJump = false;
	int  Count =0;
	float speed = 5;
	float jumpSpeed = 5;
	unsigned char keys[4];
public:
	StateComponent* _Cstate;
	CharactorInfoComponent* _CInfo;

	virtual void Update();
	void Init(float _speed, unsigned char up, unsigned char down, unsigned char left, unsigned char right);
	virtual void OnEnterCollider(GameObject* Other) override;
	void Move(int dir);
	void Jump();
	void Sit();
	void Guard();
};


