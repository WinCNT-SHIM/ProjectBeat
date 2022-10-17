#pragma once
#include "IScene.h"
/// <summary>
/// ũ���� ȭ��
/// 2022.02.15 �ɽ¼�
/// </summary>
class CreditScene :
    public IScene
{
public:
    CreditScene();
    ~CreditScene();
private:
    // ũ���� ȭ��
    SpriteObject* m_CreditSprite;
public:
    void Start() override;
    void Update() override;
    void Render(D2DEngine* m_Engine) override;
};
