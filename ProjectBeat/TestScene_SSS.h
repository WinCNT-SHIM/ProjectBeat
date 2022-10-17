#pragma once
#include "IScene.h"

class SpriteAnimationClip;
class SpriteAnimator;
class D2DSprite;
// 카메라 테스트용
class CameraObject;
// UI 테스트용
class UIObject;

class TestScene_SSS :
    public IScene
{
public:
    TestScene_SSS();
    ~TestScene_SSS();

public:
    virtual void Update() override;
    virtual void Render(D2DEngine* m_Engine) override;
private:
    RectObject* _bg;
    SpriteAnimator* temp;
    D2DSprite* m_Background;
    CameraObject* m_SceneCamera;
    //RectObject* _TestObj;
    RectObject* _Test;
    RectObject* _TestRect;
    float m_deree = 0;
    // UI 테스트
    UIObject* m_UIObject;
};

