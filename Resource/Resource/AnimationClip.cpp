#include "AnimationClip.h"
#include "../../Engine/SpriteRenderer.h"
#include "../../Engine/GameObject.h"
#include <unordered_map>
#include <cmath>
#include "../../ProjectBeat/EventSystem.h"

#define DoublePI 3.141592653589793238462643383279502884e+00
#define deg2rad PI / 180


#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

float Degree(Vector2 rotate)
{
	float radian = (float)atan2(rotate.y, rotate.x);
	float Rad2Deg = (float)(360 / (DoublePI * 2));

	return radian * Rad2Deg;
}

Vector2 Slerp(Vector2 A, Vector2 B, float alpha)
{
	if (alpha < 0) alpha = 0;
	else if (alpha > 1) alpha = 1;
	double dot = A.Dot(B);

	if (A.x == B.x && A.y == B.y)
	{
		return A;
	}

	if (dot < -1)
	{
		dot = -1;
	}
	else if (dot > 1)
	{
		dot = 1;
	}
	double acosDot = acos(dot);
	float theta = (float)(acos(dot) * alpha);

	Vector2 R = B - A * dot;

	R.Normalize();
	double cosTheta = cos(theta);
	double sinTheta = sin(theta);
	return ((A * cos(theta)) + (R * sin(theta)));
}

AnimationClip::AnimationClip()
{
}

AnimationClip::~AnimationClip()
{
}

void AnimationClip::AttachObject(map<string, GameObject*>& objects)
{

	for (auto& iter : _animationSnaps)
	{
		iter.AttachObject(objects);
	}
}

void AnimationClip::AddAnimationSnap(AnimationSnap animationSnap)
{
	_animationSnaps.push_back(AnimationSnap(animationSnap));
}

void AnimationClip::Init()
{

}

void AnimationClip::Update(float& currTimer, int& currFrame)
{
	if(_isPlay == false) return;

	if (currFrame == _animationSnaps.size() - 1)
	{
		for (auto& snap : _animationSnaps)
		{
			snap.InitEvent();
		}
		if (_loop)
		{
			//Play(currTimer, currFrame);
			currTimer = 0.f;
			currFrame = 0;
			return;
		}
		else
		{
			_isPlay = false;

			//Play(currTimer, currFrame);
			return;
		}
	}

	Play(currTimer, currFrame);

	if (_animationSnaps.size() <= 1)
	{
		return;
	}

	if (currTimer > _animationSnaps[currFrame + 1]._time)
	{
		currFrame++;
	}
}

void AnimationClip::Play(float& currTimer, int& currFrame)
{
	SnapData* prevSnapData, *currSnapData, *nextSnapData;
	float alpha = 0.f;
	Vector2 lerpVector2;
	for (unsigned int i = 0; i <_animationSnaps[currFrame]._snapDatas.size(); i++)
	{
		currSnapData = &_animationSnaps[currFrame]._snapDatas[i];

		if(currSnapData->_targetObject == nullptr) return;

		string name = currSnapData->_targetObject->GetName();

		if (name == "Root")
		{
			int a = 0;
		}

		if(!currSnapData->_targetObject) continue;

		if (currFrame + 1 == _animationSnaps.size())
		{
			if (currSnapData->_spriteSnapExist)
			{
				currSnapData->_targetObject->GetComponent<SpriteRenderer>()->SetSprite(currSnapData->_sheetName, currSnapData->_spriteName);
			}
			if (currSnapData->_positionSnapExist)
			{
				currSnapData->_targetObject->SetLocalTranslateVector((float)currSnapData->_positionSnap.x, (float)currSnapData->_positionSnap.y);
			}
			if (currSnapData->_rotateSnapExist)
			{
				currSnapData->_targetObject->SetLocalRotateVector((float)currSnapData->_rotateSnap.x, (float)currSnapData->_rotateSnap.y);
			}
			if (currSnapData->_scaleSnapExist)
			{
				currSnapData->_targetObject->SetLocalTranslateVector((float)currSnapData->_scaleSnap.x, (float)currSnapData->_scaleSnap.y);
			}
			if (currSnapData->_eventSnapExist)
			{
				AnimationEvent(*currSnapData);
			}
		}
		else
		{
			int prevFrame = currFrame;
			int nextFrame = currFrame + 1;
			nextSnapData = &_animationSnaps[nextFrame]._snapDatas[i];
			
			if (currSnapData->_spriteSnapExist)
			{
				currSnapData->_targetObject->GetComponent<SpriteRenderer>()->SetSprite(currSnapData->_sheetName, currSnapData->_spriteName);
			}
			if (currSnapData->_positionSnapExist || nextSnapData->_positionSnapExist)
			{
				if (!currSnapData->_positionSnapExist)
				{
					for (int idx = nextFrame - 1; idx >= 0; idx--)
					{
						if (_animationSnaps[idx]._snapDatas[i]._positionSnapExist)
						{
							prevFrame = idx;
							break;
						}
					}
				}
				else if (!nextSnapData->_positionSnapExist)
				{
					for (unsigned int idx = nextFrame; idx < _animationSnaps.size(); idx++)
					{
						if (_animationSnaps[idx]._snapDatas[i]._positionSnapExist)
						{
							nextFrame = idx;
							break;
						}
					}
				}

				if (0 <= prevFrame && nextFrame < (int)_animationSnaps.size())
				{
					prevSnapData = &_animationSnaps[prevFrame]._snapDatas[i];
					nextSnapData = &_animationSnaps[nextFrame]._snapDatas[i];
					alpha = (float)(currTimer - _animationSnaps[prevFrame]._time)
						/ (_animationSnaps[nextFrame]._time - _animationSnaps[prevFrame]._time);

					lerpVector2 = prevSnapData->_positionSnap.Lerp(nextSnapData->_positionSnap, alpha);
					currSnapData->_targetObject->SetLocalTranslateVector((float)lerpVector2.x, (float)lerpVector2.y);
				}
			}
			if (currSnapData->_rotateSnapExist || nextSnapData->_rotateSnapExist)
			{
				if (!currSnapData->_rotateSnapExist)
				{
					for (int idx = nextFrame - 1; idx >= 0; idx--)
					{
						if (_animationSnaps[idx]._snapDatas[i]._rotateSnapExist)
						{
							prevFrame = idx;
							break;
						}
					}
				}
				else if (!nextSnapData->_rotateSnapExist)
				{
					for (unsigned int idx = nextFrame; idx < _animationSnaps.size(); idx++)
					{
						if (_animationSnaps[idx]._snapDatas[i]._rotateSnapExist)
						{
							nextFrame = idx;
							break;
						}
					}
				}

				if (0 <= prevFrame && nextFrame < (int)_animationSnaps.size())
				{
					prevSnapData = &_animationSnaps[prevFrame]._snapDatas[i];
					nextSnapData = &_animationSnaps[nextFrame]._snapDatas[i];
					alpha = (float)(currTimer - _animationSnaps[prevFrame]._time)
						/ (_animationSnaps[nextFrame]._time - _animationSnaps[prevFrame]._time);

					lerpVector2 = Slerp(prevSnapData->_rotateSnap, nextSnapData->_rotateSnap, alpha);

					currSnapData->_targetObject->SetLocalRotateVector((float)lerpVector2.x, (float)lerpVector2.y);
				}
			}
			if (currSnapData->_scaleSnapExist || nextSnapData->_scaleSnapExist)
			{
				if (!currSnapData->_scaleSnapExist)
				{
					for (int idx = nextFrame - 1; idx >= 0; idx--)
					{
						if (_animationSnaps[idx]._snapDatas[i]._scaleSnapExist)
						{	
							prevFrame = idx;
							break;
						}
					}
				}
				else if (!nextSnapData->_scaleSnapExist)
				{
					for (unsigned int idx = nextFrame; idx < _animationSnaps.size(); idx++)
					{
						if (_animationSnaps[idx]._snapDatas[i]._scaleSnapExist)
						{
							nextFrame = idx;
							break;
						}
					}
				}

				if (0 <= prevFrame && nextFrame < (int)_animationSnaps.size())
				{
					prevSnapData = &_animationSnaps[prevFrame]._snapDatas[i];
					nextSnapData = &_animationSnaps[nextFrame]._snapDatas[i];
					alpha = (float)(currTimer - _animationSnaps[prevFrame]._time)
						/ (_animationSnaps[nextFrame]._time - _animationSnaps[prevFrame]._time);

					lerpVector2 = prevSnapData->_scaleSnap.Lerp(nextSnapData->_scaleSnap, alpha);
					currSnapData->_targetObject->SetLocalScaleVector((float)lerpVector2.x, (float)lerpVector2.y);
				}
			}
			if (currSnapData->_eventSnapExist)
			{
				AnimationEvent(*currSnapData);
			}
		}
	}
}

void AnimationClip::AnimationEvent(SnapData& snapData)
{
	if(snapData._isDone) 
		return;

	if (EventSystem::AnimationEvent(snapData._targetObject, snapData._component, snapData._event))
	{
		snapData._isDone = true;
	}
}
