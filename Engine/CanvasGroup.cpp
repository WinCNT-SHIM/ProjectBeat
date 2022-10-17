#include "stdafx.h"
#include "CanvasGroup.h"
#include "SpriteRenderer.h"

CanvasGroup::CanvasGroup(GameObject* gameObject) : Component(gameObject)
{

}

CanvasGroup::~CanvasGroup()
{

}

void CanvasGroup::Init()
{

}

void CanvasGroup::Update()
{
	if (m_Alpha == m_PrevAlpha)
	{
		return;
	}
	else
	{
		SetAlphaAllChild(m_GameObject);
		m_PrevAlpha = m_Alpha;
	}
}

void CanvasGroup::SetAlphaAllChild(GameObject* parent)
{
	SpriteRenderer* sr = parent->GetComponent<SpriteRenderer>();

	if(sr)
		sr->SetAlpha(m_Alpha);

	for (auto child : *parent->GetChilds())
	{
		SetAlphaAllChild(child);
	}
}
