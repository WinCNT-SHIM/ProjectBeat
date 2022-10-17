#include "stdafx.h"
#include "Slider.h"
#include "SpriteRenderer.h"
#include "../ProjectBeat/EventSystem.h"

Slider::Slider(GameObject* gameObject) : IUIComponent(gameObject)
{

}

Slider::~Slider()
{

}

void Slider::Init(GameObject* sliderObj, GameObject* barObj, GameObject* bgObj, RECT minMax, int mode, float initValue)
{
	Vector2D parentPos = m_GameObject->GetWorldTranslate();
	m_Min.x = parentPos.x + minMax.left;
	m_Min.y = parentPos.y + minMax.top;
	m_Max.x = parentPos.x + minMax.right;
	m_Max.y = parentPos.y + minMax.bottom;
	m_Cen = { (m_Min.x + m_Max.x) * 0.5f, (m_Min.y + m_Max.y) * 0.5f };

	m_SliderObj = sliderObj;
	m_BarObj = barObj;
	m_BarSr = m_BarObj->GetComponent<SpriteRenderer>();
	
	// 슬라이더 BG
	m_BGObj = bgObj;
	m_BgSr = bgObj->GetComponent<SpriteRenderer>();

	
	bgRect = minMax;

	m_Mode = (SliderMode)mode;

	m_BarSr->SetDrawMode(DrawMode::Fill);
	m_BarSr->leftTop.x = (float)bgRect.left;
	m_BarSr->leftTop.y = (float)bgRect.top;
	m_BarSr->rightBot.x = (float)bgRect.right;
	m_BarSr->rightBot.y = (float)bgRect.bottom;

	m_BgSr->SetDrawMode(DrawMode::Fill);
	m_BgSr->leftTop.x = (float)bgRect.left;
	m_BgSr->leftTop.y = (float)bgRect.top;
	m_BgSr->rightBot.x = (float)bgRect.right;
	m_BgSr->rightBot.y = (float)bgRect.bottom;

	m_BGObj->SetParent(m_GameObject);
	m_BarObj->SetParent(m_GameObject);
	sliderObj->SetParent(m_GameObject);
	m_BGObj->m_tr->SetWorldTranslateVector(m_Cen);
	m_BarObj->m_tr->SetWorldTranslateVector(m_Cen);
	sliderObj->m_tr->SetWorldTranslateVector(m_Cen);
	
	m_BGObj->SetLayer(m_GameObject->GetLayer());
	m_BarObj->SetLayer(m_GameObject->GetLayer() + 1);
	sliderObj->SetLayer(m_GameObject->GetLayer() + 2);

	SetSlider(initValue);
}

void Slider::Update()
{

}

void Slider::SetSlider(float alpha)
{
	Vector2D alphaPos = m_Cen;
	m_Slider = alpha;

	if(m_Slider < 0) m_Slider = 0;
	else if(m_Slider > 1) m_Slider = 1;

	Vector2D parentPos = m_GameObject->GetWorldTranslate();
	switch (m_Mode)
	{
		case SliderMode::Vertical:
			alphaPos.y = m_Min.y * (1 - m_Slider) + m_Max.y * m_Slider;
			//m_BarSr->rightBot.y = alphaPos.x - parentPos.y;
			m_BarSr->SetFill(1, alpha);
			break;
		case SliderMode::Horizontal:
			alphaPos.x = m_Min.x * (1 - m_Slider) + m_Max.x * m_Slider;
			//m_BarSr->rightBot.x = alphaPos.x - parentPos.x;
			m_BarSr->SetFill(alpha, 1);
			break;
		default:
			break;
	}

	m_SliderObj->m_tr->SetWorldTranslateVector(alphaPos);

	for (auto eventData : m_Events)
	{
		//if (eventData.targetObject)
		//{
			EventSystem::Instance()->Event(4, eventData.componentName, eventData.eventNmae, m_Slider, eventData.intParam);
		//}
	}
}

float Slider::GetSlider()
{
	return m_Slider;
}

void Slider::SetFocus(bool focus)
{

}

void Slider::OnLButtonClick(float mousePosx, float mousePosy)
{

}

void Slider::OnLButtonDown(float mousePosx, float mousePosy)
{
	if (m_SliderObj)
	{
		float alpha = 0;
		switch (m_Mode)
		{
			case SliderMode::Vertical:
				if (m_Min.y > mousePosy)
				{
					alpha = 0;
				}
				else if (m_Max.y < mousePosy)
				{
					alpha = 1;
				}
				else
				{
					alpha = (mousePosy - m_Min.y) / (m_Max.y - m_Min.y);
				}
				break;
			case SliderMode::Horizontal:
				if (m_Min.x > mousePosx)
				{
					alpha = 0;
				}
				else if (m_Max.x < mousePosx)
				{
					alpha = 1;
				}
				else
				{
					alpha = (mousePosx - m_Min.x) / (m_Max.x - m_Min.x);
				}
				break;
			default:
				break;
		}

		SetSlider(alpha);
	}
}

void Slider::OnLButtonUp(float mousePosx, float mousePosy)
{
	//이벤트 발생 해야함
	int a = 0;
}

void Slider::OnMouseMove(float mousePosx, float mousePosy)
{
	if (m_SliderObj)
	{
		float alpha = 0;
		switch (m_Mode)
		{
			case SliderMode::Vertical:
				if (m_Min.y > mousePosy)
				{
					alpha = 0;
				}
				else if (m_Max.y < mousePosy)
				{
					alpha = 1;
				}
				else
				{
					alpha = (mousePosy - m_Min.y) / (m_Max.y - m_Min.y);
				}
				break;
			case SliderMode::Horizontal:
				if (m_Min.x > mousePosx)
				{
					alpha = 0;
				}
				else if (m_Max.x < mousePosx)
				{
					alpha = 1;
				}
				else
				{
					alpha = (mousePosx - m_Min.x) / (m_Max.x - m_Min.x);
				}
				break;
			default:
				break;
		}

		SetSlider(alpha);
	}
}

void Slider::AddEvent(EventData eventData)
{
	m_Events.push_back(eventData);
}

RECT Slider::GetRect()
{
	return bgRect;
}
