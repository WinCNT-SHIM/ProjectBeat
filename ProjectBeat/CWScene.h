#pragma once
#include "IScene.h"
class CWScene :
    public IScene
{

public:
    CWScene();
    ~CWScene();

public:

    virtual void Update() override;
    virtual void Render(D2DEngine* m_Engine) override;
};

