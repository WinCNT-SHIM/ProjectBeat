#pragma once
#include "Component.h"
#include <queue>

class ActionComponent :
    public Component
{
public:
    ActionComponent(GameObject* _GameObject);
    virtual ~ActionComponent();
    virtual void SetName() { m_Name = "ActionComponent"; }
private:
	unsigned char keys[3];

    std::queue<unsigned char> m_Commandqueue;
    bool m_isInput = false;
    int m_InputFrame = 0;
    bool m_isKeys[3];
public:

    virtual void Update();
    void Init(unsigned char punch, unsigned char kick);
  
    void executePunch();
    void executeKick();
    void executeUltra();


  
};

