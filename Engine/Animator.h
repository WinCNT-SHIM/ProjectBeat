#pragma once
#include "Component.h"
#include <string>
#include <map>

using namespace std;

class AnimatorController;

/// <summary>
/// 애니메이터 컴포넌트
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
    // 컨트롤러 설정
    void Init(AnimatorController* animatorController);

    void AttachGameObject(GameObject* parent, map<string, GameObject*>& objects);
    /// <summary>
    /// 각 이름의 맞는 파라미터 값 반환
    /// </summary>
    /// <param name="name">파라미터 이름</param>
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
    // 애니메이션 컨트롤러의 업데이트를 불러와줌
    virtual void Update();

public:
	virtual void SetName() { m_Name = "Animator"; }
};

