#pragma once
#include "IScene.h"
class TestAnimatorScene :
    public IScene
{
public:
    TestAnimatorScene();
    ~TestAnimatorScene();

public:
	virtual void Update() override;
	virtual void Render(D2DEngine* m_Engine) override;
};

