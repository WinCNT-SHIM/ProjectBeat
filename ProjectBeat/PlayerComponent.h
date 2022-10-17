#pragma once
#include "Component.h"
class PlayerComponent :
    public Component
{
public:
	PlayerComponent(GameObject* _GameObject);
	virtual ~PlayerComponent();



public:
	virtual void Update();
	virtual void SetName() { m_Name = "PlayerComponent"; }
 





};

