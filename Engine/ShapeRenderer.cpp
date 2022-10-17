#include "stdafx.h"
#include "ShapeRenderer.h"

ShapeRenderer::ShapeRenderer(GameObject* parent) : Renderer(parent), _color(0xFFFFFF)
{
	_point1 = 0;
	_point2 = 0;
	_point3 = 0;
	_point4 = 0;
}

ShapeRenderer::~ShapeRenderer()
{
}

void ShapeRenderer::Init(double point1, double point2, double point3, double point4)
{
	_point1 = point1;
	_point2 = point2;
	_point3 = point3;
	_point4 = point4;
}




