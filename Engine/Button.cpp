#include "stdafx.h"
#include "Button.h"
#include "SpriteRenderer.h"
#include "../ProjectBeat/EventSystem.h"
#include "../Resource/ResourceManager.h"

Button::Button(GameObject* gameObject) : IUIComponent(gameObject)
{

}

Button::~Button()
{

}

void Button::Init(RECT rect, pair<string, string> idleSprite, pair<string, string> downSprite = {})
{
	m_BgRect = rect;
	m_BtnSpriteRenderer = GetComponent<SpriteRenderer>();
	if (!m_BtnSpriteRenderer)
	{
		m_BtnSpriteRenderer = m_GameObject->AddComponent<SpriteRenderer>();
	}

	m_IdleSprite = RESOURCE->GetSprite(idleSprite.first, idleSprite.second);
	m_DownSprite = RESOURCE->GetSprite(downSprite.first, downSprite.second);

	m_BtnSpriteRenderer->_sprite = m_IdleSprite;
	m_BtnSpriteRenderer->leftTop.x = (float)rect.left;
	m_BtnSpriteRenderer->leftTop.y = (float)rect.top;
	m_BtnSpriteRenderer->rightBot.x = (float)rect.right;
	m_BtnSpriteRenderer->rightBot.y = (float)rect.bottom;

	Vector2D pos = m_GameObject->GetWorldTranslate();
}

void Button::Update()
{

}

void Button::SetFocus(bool focus)
{

}

void Button::OnLButtonClick(float mousePosx, float mousePosy)
{

}

void Button::OnLButtonDown(float mousePosx, float mousePosy)
{
	if (m_DownSprite)
	{
		m_BtnSpriteRenderer->_sprite = m_DownSprite;
	}
}

void Button::OnLButtonUp(float mousePosx, float mousePosy)
{
	if (m_IdleSprite)
	{
		m_BtnSpriteRenderer->_sprite = m_IdleSprite;
	}

	// 이벤트 발생
	for (auto eventData : m_Events)
	{
		//if (eventData.targetObject)
		//{
			EventSystem::Instance()->Event(2, eventData.componentName, eventData.eventNmae);
		//}
	}
}

void Button::OnMouseMove(float mousePosx, float mousePosy)
{

}

void Button::AddEvent(EventData eventData)
{
	m_Events.push_back(eventData);
}

RECT Button::GetRect()
{
	return m_BgRect;
}
