#pragma once
#include "GameObject.h"

class CameraObject;
class SpriteRenderer;

/// <summary>
/// UI ������Ʈ
/// 2022.02.15 �ɽ¼�
/// </summary>
class UIObject :
    public GameObject
{
// ������ �� �ʱ�ȭ
public:
    UIObject(std::string _UIName, CameraObject* _CameraObject, string _SheetName, string _SpriteName, float _alpha = 1.f, float _ratio = 1.f);
    virtual ~UIObject();
    void Init();
// ����
private:
    // UI ��ġ�� ���� Ʈ������
    //Transform* m_tr;
    // UI ��������Ʈ�� ��Ʈ���ϱ� ���� Shortcut
    SpriteRenderer* m_UIRenderer;
// �Լ�
public:
    SpriteRenderer* GetUIRenderer() const { return m_UIRenderer; }
    void SetUIRenderer(SpriteRenderer* val) { m_UIRenderer = val; }
};
