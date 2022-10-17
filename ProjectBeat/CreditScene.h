#pragma once
#include "IScene.h"
/// <summary>
/// Å©·¹µ÷ È­¸é
/// 2022.02.15 ½É½Â¼ö
/// </summary>
class CreditScene :
    public IScene
{
public:
    CreditScene();
    ~CreditScene();
private:
    // Å©·¹µ÷ È­¸é
    SpriteObject* m_CreditSprite;
public:
    void Start() override;
    void Update() override;
    void Render(D2DEngine* m_Engine) override;
};
