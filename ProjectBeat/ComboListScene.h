#pragma once
#include "IScene.h"
/// <summary>
/// ÄÞº¸ ¸®½ºÆ® È­¸é ¾À
/// 2022.02.15 ½É½Â¼ö
/// </summary>
class ComboListScene :
    public IScene
{
public:
    ComboListScene();
    ~ComboListScene();
private:
    // ÄÞº¸ ¸®½ºÆ® È­¸é
    SpriteObject* m_ComboListSprite;
public:
    void Start() override;
    void Update() override;
    void Render(D2DEngine* m_Engine) override;
};

