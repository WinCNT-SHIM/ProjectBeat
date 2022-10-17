#pragma once
#include "..\Engine\Component.h"

class GameObject;
class Animator;
class TextComponent;
class StateComponent;
class CommandComponent;
class CharactorInfoComponent;

class CharaterDebug :
    public Component
{
public:
    CharaterDebug(GameObject* gameobject);
    virtual ~CharaterDebug();

public:
    GameObject* _charater = nullptr;
    Animator* _animator = nullptr;
    TextComponent* _textComponent = nullptr;
    StateComponent* _charInfo = nullptr;
    CommandComponent* _cmdComponent = nullptr;
    CharactorInfoComponent* _CharactorInfoComponent = nullptr;
    std::string _debugInfo = "";
public:
    void Init(GameObject* charaterObject);
    void SetName() { m_Name = "ChararterDebug"; }

    virtual void Update();
};

