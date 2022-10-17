#include "stdafx.h"


Component::Component(GameObject* _GameObj)
{
	if (_GameObj)
		m_GameObject = _GameObj;
	SetName();

}

Component::~Component()
{

}

void Component::SetName()
{
}


