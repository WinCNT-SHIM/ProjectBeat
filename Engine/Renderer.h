#pragma once
#include "Component.h"

class Renderer :
    public Component
{
public:
    Renderer(GameObject* parent);
	virtual ~Renderer();

public:
	
	virtual void Update() abstract;
	virtual void Render(D2DEngine* _pEngine) abstract;
	virtual void DrawGizmo() {};

public:
	virtual void SetName() abstract;
};

