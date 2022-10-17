#include "stdafx.h"
#include "Animator.h"
#include "GameObject.h"
#include "../Resource/Resource/AnimatorController.h"


#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

Animator::Animator(GameObject* gameObject) : Component(gameObject)
{
}

Animator::~Animator()
{
	if (_animatorController != nullptr)
	{
		delete _animatorController;
	}
}

void Animator::Init(AnimatorController* animatorController)
{
	_animatorController = new AnimatorController(*animatorController);
	_animatorController->Init();
	map<string, GameObject*> objects;

	AttachGameObject(m_GameObject, objects);

	_animatorController->AttachObject(objects);
}

void Animator::AttachGameObject(GameObject* parent, map<string, GameObject*>& objects)
{
	objects.insert({ parent->GetName(), parent });

	for (auto child : *(parent->GetChilds()))
	{
		AttachGameObject(child, objects);
	}
}

int Animator::GetInteger(string name)
{
	if (!_animatorController || (_animatorController->_intParameter.end() == _animatorController->_intParameter.find(name))) return 0;

	return (_animatorController->_intParameter[name]);
}

float Animator::GetFloat(string name)
{
	if (!_animatorController || (_animatorController->_floatParameter.end() == _animatorController->_floatParameter.find(name))) return 0;

	return _animatorController->_floatParameter[name];
}

bool Animator::GetBool(string name)
{
	if (!_animatorController || (_animatorController->_booleanParameter.end() == _animatorController->_booleanParameter.find(name))) return 0;

	return _animatorController->_booleanParameter[name];
}

void Animator::SetInteger(string name, int value)
{
	if (!_animatorController || (_animatorController->_intParameter.end() == _animatorController->_intParameter.find(name))) return;

	_animatorController->_intParameter[name] = value;
}

void Animator::SetFloat(string name, float value)
{
	if (!_animatorController || (_animatorController->_floatParameter.end() == _animatorController->_floatParameter.find(name))) return;

	_animatorController->_floatParameter[name] = value;
}

void Animator::SetBool(string name, bool value)
{
	if (!_animatorController || (_animatorController->_booleanParameter.end() == _animatorController->_booleanParameter.find(name))) return;

	_animatorController->_booleanParameter[name] = value;
}

void Animator::SetTrigger(string name)
{
	if (!_animatorController || (_animatorController->_triggerParameter.end() == _animatorController->_triggerParameter.find(name))) return;

	_animatorController->_triggerParameter[name] = true;
}

float Animator::GetSpeed()
{
	return _speed;
}

void Animator::SetSpeed(float speed)
{
	_speed = speed;
}

float Animator::GetCurrAnimationTime()
{
	return _currTimer;
}

void Animator::Update()
{
	if(!_animatorController) return;

	_animatorController->Update(_currTimer, _currFrame);
	_currTimer += (CTime::GetDeltaTime() * _speed * 1.5f);
}
