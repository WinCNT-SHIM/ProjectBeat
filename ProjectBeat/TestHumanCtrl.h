#pragma once
#include "..\Engine\Component.h"

class GameObject;
class Animator;
class SpriteRenderer;

class TestHumanCtrl :
    public Component
{
public:
    TestHumanCtrl(GameObject* _GameObject);
    ~TestHumanCtrl();

public:
    Animator* _animator = nullptr;
    SpriteRenderer* _sr = nullptr;

public:
    void Init();

    void TestFunc();
    void TestFunc2();

    virtual void SetName() { m_Name = "TestHumanCtrl"; }

	virtual void Update();
};

