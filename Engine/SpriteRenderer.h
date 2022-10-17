#pragma once
#include "Renderer.h"
#include <windows.h>
class D2DSprite;

enum class DrawMode
{
	Simple,
	Fill
};

class SpriteRenderer :
	public Renderer
{
public:
	SpriteRenderer(GameObject* gameObject);
	virtual ~SpriteRenderer();

public:
	D2DSprite* _sprite;

	float _alpha = 1.0f;
	unsigned long _color;

	Vector2D leftTop;
	Vector2D rightBot;

	int _sortingLayer;
	int _orderInLayer;

	DrawMode _drawMode = DrawMode::Simple;
private:
	// ��������Ʈ�� ä�� ����
	Vector2D m_Fill;
	// ����
	float m_Ratio;

	bool m_isActive;
public:
	void Init(D2DSprite* sprite, float _ratio = 0.2f);
	void Init(string _Sheetname, string _SpriteName, float _ratio = 0.2f);

	void SetColor(unsigned long value) { _color = value; }
	void SetAlpha(float value)
	{
		_alpha = value;
		if (1.f < _alpha) _alpha = 1.0f;
		else if (_alpha < 0.f) _alpha = 0.f;
	}
	void SetSprite(std::string sheetName, std::string spriteName, float _ratio = 0.2f);
	/// <summary>
	/// Fill ��� ����
	/// </summary>
	/// <param name="mode">DrawMode::Simple, DrawMode::Fill</param>
	void SetDrawMode(DrawMode mode);

	/// <summary>
	/// ��������Ʈ _rect ũ�⿡ �°� _sprite�� ��������
	/// </summary>
	/// <param name="engine"></param>
	virtual void Update() override;
	virtual void Render(D2DEngine* _pEngine) override;
	virtual void DrawGizmo();
	// ��������Ʈ�� ä�� ������ �����ϴ� �Լ�(0~1)
	void SetFill(float _FillX, float _FillY);
	Vector2D GetFill() { return m_Fill; };

	void SetActive(bool _isactive) { m_isActive = _isactive; }
	bool GetActive() { return m_isActive; }
public:
	virtual void SetName() { m_Name = "SpriteRenderer"; }
};

