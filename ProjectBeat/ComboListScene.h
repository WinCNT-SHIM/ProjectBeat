#pragma once
#include "IScene.h"
/// <summary>
/// �޺� ����Ʈ ȭ�� ��
/// 2022.02.15 �ɽ¼�
/// </summary>
class ComboListScene :
    public IScene
{
public:
    ComboListScene();
    ~ComboListScene();
private:
    // �޺� ����Ʈ ȭ��
    SpriteObject* m_ComboListSprite;
public:
    void Start() override;
    void Update() override;
    void Render(D2DEngine* m_Engine) override;
};

