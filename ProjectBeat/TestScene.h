#pragma once
#include "IScene.h"

class TestScene : public IScene
{
public:
	TestScene();
	~TestScene();

public:
	virtual void Update() override;
	virtual void Render(D2DEngine* m_Engine) override;

};

