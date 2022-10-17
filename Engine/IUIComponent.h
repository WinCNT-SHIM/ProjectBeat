#pragma once
#include "Component.h"

struct EventData
{   
    EventData(GameObject* targetObject, string componentName, string eventNmae, int intParam = 0, int intParam2 = 0)
    : targetObject(targetObject), componentName(componentName), eventNmae(eventNmae), intParam(intParam), intParam2(intParam2)
    {

    }
    GameObject* targetObject;
    string componentName;
    string eventNmae;
    int intParam;
    int intParam2;
};

class IUIComponent :
    public Component
{
public:
    IUIComponent(GameObject* gameObject) : Component(gameObject) {}
    virtual ~IUIComponent() {}
public:
    virtual void SetFocus(bool focus) abstract;
    virtual void OnLButtonClick(float mousePosx, float mousePosy) abstract;
    virtual void OnLButtonDown(float mousePosx, float mousePosy) abstract;
    virtual void OnLButtonUp(float mousePosx, float mousePosy) abstract;
    virtual void OnMouseMove(float mousePosx, float mousePosy) abstract;
    virtual void AddEvent(EventData eventData) abstract;

    virtual RECT GetRect() abstract;
};

