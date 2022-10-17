#pragma once
#include "IScene.h"

class ParticleManager;

class TestScene2 : public IScene
{
public:
	TestScene2();
	~TestScene2();

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(D2DEngine* m_Engine) override;

};

