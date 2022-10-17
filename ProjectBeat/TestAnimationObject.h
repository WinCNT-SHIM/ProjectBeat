#pragma once
#include "..\Engine\GameObject.h"

class SpriteRenderer;
class TestHumanCtrl;

class TestSpriteObject :
	public GameObject
{
public:
    TestSpriteObject();
    virtual ~TestSpriteObject();
public:
    SpriteRenderer* sr;
    TestHumanCtrl* ctrl;
};
class TestAnimationObject :
    public TestSpriteObject
{
public:
    TestAnimationObject(int x, int y);
    TestAnimationObject(int x, int y, int z);
    ~TestAnimationObject();

public:
};

