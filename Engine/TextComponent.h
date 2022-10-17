#pragma once
#include "Renderer.h"
#include <string>

enum class VerticalAlignment
{
	Top,
	Bottom,
	Center
};
enum class HorizontalAlignment
{
	Left,
	Right,
	Center
};

class TextComponent :
	public Renderer
{
public:
	TextComponent(GameObject* gameobject);
	virtual ~TextComponent();

private:
	bool m_isActive = true;
public:
	float halfwidth = 200;
	float halfheight = 50;

	std::string _text = "";
	int _font = 10;
	int _fontSize = 30;
	int _LineSpacing = 10;
	VerticalAlignment _verticalAlignment = VerticalAlignment::Center;
	HorizontalAlignment _horizontalAlignment = HorizontalAlignment::Center;

	unsigned long _color = 0xffffff;
public:
	void Init(std::string text);

	void SetColor(unsigned long value) { _color = value; }
	void SetActive(bool _isActive) { m_isActive = _isActive; }
	bool GetActiveSelf() { return m_isActive; }

	/// <summary>
	/// Text¸¦ ¶ç¿ò
	/// </summary>
	/// <param name="engine"></param>
	virtual void Update() override;
	virtual void Render(D2DEngine* _pEngine) override;
	virtual void DrawGizmo();

public:
	virtual void SetName() { m_Name = "SpriteRenderer"; }
};

