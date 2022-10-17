#pragma once
#include "..\Engine\Component.h"

class GameObject;
enum class MsgType
{
    RButtonDown,
    RButtonMove,
    RButtonUp,
    RButtonClick
};

class IUIComponent;

class EventSystem :
    public Component
{
public:
    EventSystem(GameObject* object);
    virtual ~EventSystem();
private:
	static EventSystem* _instance;

    bool m_IsUserInput = false;
    MsgType m_CurrEvent;

    Vector2D m_CurrMouseInputPos;

    std::vector<IUIComponent*> m_UIObjects;

    bool m_IsFoucs = false;
    IUIComponent* m_FocusObject;
public:
	static EventSystem* Instance();
	static void Release();


public:
    void Init();
	void Update();
    void SetName() { m_Name = "EventSystem"; }

	/// �̺�Ʈ�� �������???
    static bool AddEvent(string componentName, string eventName);

    bool AddUIObject(GameObject* object);

    static bool Event(int args, ...);
    static bool Event(GameObject* targetObject, string componentName, string eventName);

    /// <summary>
    /// �̺�Ʈ(������Ʈ ���� �Լ�)�� ȣ�� ����
    /// </summary>
    /// <param name="targetObject">������Ʈ�� ����ִ� ������Ʈ ������</param>
    /// <param name="componentName">������Ʈ �̸�</param>
    /// <param name="eventName">�Լ� �̸�</param>
    /// <returns>�̺�Ʈ ȣ�⿡ ���� �ߴ��� ��ȯ</returns>
    static bool AnimationEvent(GameObject* targetObject, string componentName, string eventName);

    // ���콺 Ŭ�� �̺�Ʈ
    void OnLButtonClick(int mousePosx, int mousePosy);
    void OnLButtonDown(int mousePosx, int mousePosy);
    void OnLButtonUp(int mousePosx, int mousePosy);
    void OnMouseMove(int mousePosx, int mousePosy);
};

