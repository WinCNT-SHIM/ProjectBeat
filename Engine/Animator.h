#pragma once
#include "Component.h"
#include <string>
#include <map>

using namespace std;

class AnimatorController;

/// <summary>
/// �ִϸ����� ������Ʈ
/// </summary>
class Animator :
    public Component
{
public:
    Animator(GameObject* gameObject);
    virtual ~Animator();

    AnimatorController* _animatorController = nullptr;

public:
    float _speed = 1.f;
    float _currTimer = 0.f;

    int _currFrame = 0;
    //SnapFrame _currFrame;

public:
    // ��Ʈ�ѷ� ����
    void Init(AnimatorController* animatorController);

    void AttachGameObject(GameObject* parent, map<string, GameObject*>& objects);
    /// <summary>
    /// �� �̸��� �´� �Ķ���� �� ��ȯ
    /// </summary>
    /// <param name="name">�Ķ���� �̸�</param>
    int GetInteger(string name);
    float GetFloat(string name);
    bool GetBool(string name);

    void SetInteger(string name, int value);
    void SetFloat(string name, float value);
    void SetBool(string name, bool value);
    void SetTrigger(string name);

    float GetSpeed();
    void SetSpeed(float speed);

    float GetCurrAnimationTime();
public:
    // �ִϸ��̼� ��Ʈ�ѷ��� ������Ʈ�� �ҷ�����
    virtual void Update();

public:
	virtual void SetName() { m_Name = "Animator"; }
};

