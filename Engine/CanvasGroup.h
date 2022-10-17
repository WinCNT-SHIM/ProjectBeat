#pragma once
#include "Component.h"
class CanvasGroup :
    public Component
{
public:
    CanvasGroup(GameObject* gameObject);
    virtual ~CanvasGroup();

public:
    float m_Alpha = 1.0;
    float m_PrevAlpha = 1.0;

public:
    void Init();
    virtual void Update();
    virtual void SetName() { m_Name = "CanvasGroup"; }
    void SetAlphaAllChild(GameObject* parent);
};

