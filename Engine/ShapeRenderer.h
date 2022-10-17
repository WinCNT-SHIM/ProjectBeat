#pragma once
#include "Renderer.h"
/// <summary>
/// 다형적 동작을 하는 도형을 위한 인터페이스
/// 신성현
/// </summary>
class ShapeRenderer :
    public Renderer
{
public:
	ShapeRenderer(GameObject* gameObject);
	virtual ~ShapeRenderer();

public:

	double _point1;
	double _point2;
	double _point3;
	double _point4;

	unsigned long _color;

	//-width,-height, width, height//
	void Init(double point1, double point2 = 0, double point3 = 0, double point4 = 0);

	virtual void Update() abstract;
	virtual void Render(D2DEngine* engine) abstract;
	virtual void DrawGizmo() {};

public:
	virtual void SetName() abstract;
};

