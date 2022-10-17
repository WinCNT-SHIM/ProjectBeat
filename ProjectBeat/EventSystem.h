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

	/// 이벤트를 등록해줌???
    static bool AddEvent(string componentName, string eventName);

    bool AddUIObject(GameObject* object);

    static bool Event(int args, ...);
    static bool Event(GameObject* targetObject, string componentName, string eventName);

    /// <summary>
    /// 이벤트(컴포넌트 안의 함수)를 호출 해줌
    /// </summary>
    /// <param name="targetObject">컴포넌트가 담겨있는 오브젝트 포인터</param>
    /// <param name="componentName">컴포넌트 이름</param>
    /// <param name="eventName">함수 이름</param>
    /// <returns>이벤트 호출에 성공 했는지 반환</returns>
    static bool AnimationEvent(GameObject* targetObject, string componentName, string eventName);

    // 마우스 클릭 이벤트
    void OnLButtonClick(int mousePosx, int mousePosy);
    void OnLButtonDown(int mousePosx, int mousePosy);
    void OnLButtonUp(int mousePosx, int mousePosy);
    void OnMouseMove(int mousePosx, int mousePosy);
};

