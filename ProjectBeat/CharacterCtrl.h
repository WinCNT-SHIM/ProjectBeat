#pragma once
#include "..\Engine\Component.h"
enum class CharacterState
{
    Idle,
    Run,
    Attack,
    Jump,
    Guard,
    Stun,
    Death
};

class Animator;

class CharacterInfo
{
public:
    float m_MaxHp = 100.f;
    float m_CurrHp = m_MaxHp;
};
class CharacterCtrl :
    public Component
{
public:
    CharacterCtrl(GameObject* gameObject);
    virtual ~CharacterCtrl();

    CharacterInfo m_CharInfo;
	CharacterState m_CurrState;

    Animator* m_Animator;

    GameObject* m_TargetCharacter;

    float m_StumTime = 0.f;
    float m_MaxStumTime = 0.2f;

    bool m_CanInput = true;
    bool m_AttackAble = true;
    bool m_MoveAble = true;
    bool m_DamagedAble = true;
    bool m_JumpAble = true;

    Vector2D m_Direction = { 1,0 };
    float m_GameSpeed;
public:
    virtual void Init();
    virtual void Start();
    virtual void Update();
    virtual void SetName() { m_Name = "CharacterCtrl"; }

    void CheckState();
    void CheckIdleInput();
    void CheckJumpInput();
    void CheckRunInput();
    void CheckGuardInput();
    void CheckAttackInput();

    void MoveAgent();
};

