#include "stdafx.h"
#include "TextComponent.h"

TextComponent::TextComponent(GameObject* gameobject) :
Renderer(gameobject)
{

}

TextComponent::~TextComponent()
{

}

void TextComponent::Init(std::string text)
{
	_text = text;
}

void TextComponent::Update()
{
}

void TextComponent::Render(D2DEngine* _pEngine)
{
	if (!m_isActive) return;

	Vector2D pos = m_GameObject->m_tr->GetWorldTranslate();
	_pEngine->DrawString(pos.x - halfwidth, pos.y - halfheight, pos.x + halfwidth, pos.y + halfheight, _text, (float)_fontSize, (int)_verticalAlignment, (int)_horizontalAlignment, _color);
}

void TextComponent::DrawGizmo()
{
}
