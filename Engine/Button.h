#pragma once
#include "IUIComponent.h"

class D2DSprite;
class SpriteRenderer;

class Button :
    public IUIComponent
{
public:
	Button(GameObject* gameObject);
	virtual ~Button();
private:

	std::vector<EventData> m_Events;
	D2DSprite* m_IdleSprite;
	D2DSprite* m_DownSprite;
	SpriteRenderer* m_BtnSpriteRenderer;
	RECT m_BgRect;
public:
	void Init(RECT rect, pair<string, string> idleSprite, pair<string, string> downSprite);

	virtual void Update();
	virtual void SetName() { m_Name = "Button"; }

	virtual void SetFocus(bool focus) override;
	virtual void OnLButtonClick(float mousePosx, float mousePosy) override;
	virtual void OnLButtonDown(float mousePosx, float mousePosy) override;
	virtual void OnLButtonUp(float mousePosx, float mousePosy) override;
	virtual void OnMouseMove(float mousePosx, float mousePosy) override;
	virtual void AddEvent(EventData eventData) override;

	virtual RECT GetRect() override;
};

