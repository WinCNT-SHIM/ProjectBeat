#pragma once
#include <map>
#include "Component.h"

class Transform;

struct CollisionBool
{

	bool m_isCur = false;
	bool m_isPrior = false;
};
class Collider : public Component
{
public:
	Collider(GameObject* _GameObject);
	virtual ~Collider();
public:
	GameObject* m_GameObject; //ºÎ¸ð
	Transform* m_tr;
	Vector2D* m_pos;
	bool ispriorCol;
	bool isCol;

	map<GameObject*, CollisionBool*> m_OtherCollider;

	virtual bool Check(Collider* other) { return false; }
	virtual void Update();

public:
	virtual void SetName() abstract;
};

