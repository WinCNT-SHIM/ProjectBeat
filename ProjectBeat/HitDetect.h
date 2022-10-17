#pragma once
#include "Component.h"

class CharactorInfoComponent;
class Character;


class HitDetect :
    public Component
{

public:
    HitDetect(GameObject* _GameObject);
    virtual ~HitDetect() {}
    virtual void SetName() { m_Name = "HitDetect"; }
private:

    GameObject* CObject = nullptr;
    CharactorInfoComponent* T_Cinfo = nullptr;
    CharactorInfoComponent* Cinfo = nullptr;



    virtual void OnEnterCollider(GameObject* Other);
    virtual void OnExitCollider(GameObject* Other);
    virtual void OnStayCollider(GameObject* Other);
    virtual void Update() {}
    bool testcheck = true;
    void DetectHitPart(GameObject* Other);
};

