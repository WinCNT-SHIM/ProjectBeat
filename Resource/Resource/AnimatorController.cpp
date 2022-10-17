#include "ResourceManager.h"
#include "AnimatorController.h"


#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

AnimatorController::AnimatorController()
{
}

AnimatorController::~AnimatorController()
{
	for (auto iter : _nodes)
	{
		if(iter.second._animationClip != nullptr)
			delete iter.second._animationClip;
	}
}

void AnimatorController::AttachObject(map<string, GameObject*>& objects)
{
	for (auto& iter : _nodes)
	{
		iter.second._animationClip->AttachObject(objects);
	}
}

void AnimatorController::AddAnimationClip(AnimationClip* animationClip)
{
	_animationClip.push_back(animationClip);
}

void AnimatorController::Init()
{
	// Load Animation Clip
	for (auto& clip : _nodes)
	{
		clip.second._animationClip = RESOURCE->GetAnimationClip(clip.second._animationClipName);
	}

	// Link랑 연결되야할 애니메이션 클립을 연결
	LoadAnimationClips();
}

void AnimatorController::SetStartNode(string nodeName)
{
	_currAnimationNode = &_nodes[nodeName];
}

void AnimatorController::LoadAnimationClips()
{
	{
		for (auto intLink : _anyStateNode._intLinkNodes)
		{
			_anyStateNode.AddIntLink(intLink.first, &_nodes[intLink.second]);
		}
		for (auto floatLink : _anyStateNode._floatLinkNodes)
		{
			_anyStateNode.AddFloatLink(floatLink.first, &_nodes[floatLink.second]);
		}
		for (auto booleanLink : _anyStateNode._booleanLinkNodes)
		{
			_anyStateNode.AddBooleanLink(booleanLink.first, &_nodes[booleanLink.second]);
		}
		for (auto triggerLink : _anyStateNode._triggerLinkNodes)
		{
			_anyStateNode.AddTriggerLink(triggerLink.first, &_nodes[triggerLink.second]);
		}
		for (auto anyLink : _anyStateNode._anyLinkNodes)
		{
			_anyStateNode.AddAnyLink(&_nodes[anyLink]);
		}
	}
	for (auto& iter : _nodes)
	{
		for (auto intLink : iter.second._intLinkNodes)
		{
			iter.second.AddIntLink(intLink.first, &_nodes[intLink.second]);
		}
		for (auto floatLink : iter.second._floatLinkNodes)
		{
			iter.second.AddFloatLink(floatLink.first, &_nodes[floatLink.second]);
		}
		for (auto booleanLink : iter.second._booleanLinkNodes)
		{
			iter.second.AddBooleanLink(booleanLink.first, &_nodes[booleanLink.second]);
		}
		for (auto triggerLink : iter.second._triggerLinkNodes)
		{
			iter.second.AddTriggerLink(triggerLink.first, &_nodes[triggerLink.second]);
		}
		for (auto anyLink : iter.second._anyLinkNodes)
		{
			iter.second.AddAnyLink(&_nodes[anyLink]);
		}
	}
}

void AnimatorController::AddIntParameter(string name)
{
	_intParameter.insert({ name, 0 });
}

void AnimatorController::AddFloatParameter(string name)
{
	_floatParameter.insert({name, 0.f});
}

void AnimatorController::AddBooleanParameter(string name)
{
	_booleanParameter.insert({name, true});
}

void AnimatorController::AddTriggerParameter(string name)
{
	_triggerParameter.insert({name, false});
}

void AnimatorController::AddAnimationClipNode(AnimationClipNode node)
{
	_nodes.insert({ node._animationClipName, node });
}

void AnimatorController::Update(float& currTimer, int& currFrame)
{
	CheckState(currTimer, currFrame);
	if(!_currAnimationNode || !_currAnimationNode->_animationClip) return;

	InitTrigger();
	_currAnimationNode->_animationClip->Update(currTimer, currFrame);
}

void AnimatorController::CheckState(float& currTimer, int& currFrame)
{
	if(CheckAnyState(currTimer, currFrame)) return;

	for (auto iter : _currAnimationNode->_anyLinks)
	{
		if (_currAnimationNode->_animationClip->_isPlay == false)
		{
			_currAnimationNode = iter;
			currTimer = 0.f;
			currFrame = 0;
			_currAnimationNode->_animationClip->_isPlay = true;
			for (auto& snap : _currAnimationNode->_animationClip->_animationSnaps)
			{
				snap.InitEvent();
			}
			return;
		}
	}

	for (auto iter : _currAnimationNode->_intLinks)
	{
		if (iter.first.CheckCondition(_intParameter[iter.first._parameterName]))
		{
			_currAnimationNode = iter.second;
			currTimer = 0.f;
			currFrame = 0;
			_currAnimationNode->_animationClip->_isPlay = true;
			for (auto& snap : _currAnimationNode->_animationClip->_animationSnaps)
			{
				snap.InitEvent();
			}
			return;
		}
	}
	for (auto iter : _currAnimationNode->_floatLinks)
	{
		if (iter.first.CheckCondition(_floatParameter[iter.first._parameterName]))
		{
			_currAnimationNode = iter.second;
			currTimer = 0.f;
			currFrame = 0;
			_currAnimationNode->_animationClip->_isPlay = true;
			for (auto& snap : _currAnimationNode->_animationClip->_animationSnaps)
			{
				snap.InitEvent();
			}
			return;
		}
	}
	for (auto iter : _currAnimationNode->_booleanLinks)
	{
		if (iter.first.CheckCondition(_booleanParameter[iter.first._parameterName]))
		{
			_currAnimationNode = iter.second;
			currTimer = 0.f;
			currFrame = 0;
			_currAnimationNode->_animationClip->_isPlay = true;
			for (auto& snap : _currAnimationNode->_animationClip->_animationSnaps)
			{
				snap.InitEvent();
			}
			return;
		}
	}
	for (auto iter : _currAnimationNode->_triggerLinks)
	{
		if (_triggerParameter[iter.first])
		{
			_triggerParameter[iter.first] = false;
			_currAnimationNode = iter.second;
			currTimer = 0.f;
			currFrame = 0;
			_currAnimationNode->_animationClip->_isPlay = true;
			for (auto& snap : _currAnimationNode->_animationClip->_animationSnaps)
			{
				snap.InitEvent();
			}
			return;
		}
	}
}

bool AnimatorController::CheckAnyState(float& currTimer, int& currFrame)
{
	for (auto iter : _anyStateNode._intLinks)
	{
		if (iter.first.CheckCondition(_intParameter[iter.first._parameterName]))
		{
			_currAnimationNode = iter.second;
			currTimer = 0.f;
			currFrame = 0;
			_currAnimationNode->_animationClip->_isPlay = true;
			for (auto& snap : _currAnimationNode->_animationClip->_animationSnaps)
			{
				snap.InitEvent();
			}
			return 1;
		}
	}
	for (auto iter : _anyStateNode._floatLinks)
	{
		if (iter.first.CheckCondition(_floatParameter[iter.first._parameterName]))
		{
			_currAnimationNode = iter.second;
			currTimer = 0.f;
			currFrame = 0;
			_currAnimationNode->_animationClip->_isPlay = true;
			for (auto& snap : _currAnimationNode->_animationClip->_animationSnaps)
			{
				snap.InitEvent();
			}
			return 1;
		}
	}
	for (auto iter : _anyStateNode._booleanLinks)
	{
		if (iter.first.CheckCondition(_booleanParameter[iter.first._parameterName]))
		{
			_currAnimationNode = iter.second;
			currTimer = 0.f;
			currFrame = 0;
			_currAnimationNode->_animationClip->_isPlay = true;
			for (auto& snap : _currAnimationNode->_animationClip->_animationSnaps)
			{
				snap.InitEvent();
			}
			return 1;
		}
	}
	for (auto iter : _anyStateNode._triggerLinks)
	{
		if (_triggerParameter[iter.first])
		{
			_triggerParameter[iter.first] = false;
			_currAnimationNode = iter.second;
			currTimer = 0.f;
			currFrame = 0;
			_currAnimationNode->_animationClip->_isPlay = true;
			for (auto& snap : _currAnimationNode->_animationClip->_animationSnaps)
			{
				snap.InitEvent();
			}
			return 1;
		}
	}

	return 0;
}

void AnimatorController::InitTrigger()
{
	for (auto& trigger : _triggerParameter)
	{
		if(trigger.second) trigger.second = false;
	}
}
