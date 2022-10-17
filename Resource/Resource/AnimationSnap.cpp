#include "AnimationSnap.h"
#include "../../Engine/SpriteRenderer.h"
#include "../../Engine/GameObject.h"

AnimationSnap::AnimationSnap()
{
}

AnimationSnap::~AnimationSnap()
{
}



void AnimationSnap::AddSnapData(SnapData snapData)
{
	_snapDatas.push_back(SnapData(snapData));
}

void AnimationSnap::AttachObject(map<string,GameObject*>& objects)
{
	for (auto& iter : _snapDatas)
	{
		if(objects.find(iter._objectName) == objects.end()) continue;
		GameObject* object = objects[iter._objectName];
		if (object)
		{
			iter._targetObject = object;
		}
	}
}

void AnimationSnap::Init()
{
}

void AnimationSnap::Play()
{
	for (auto snapData : _snapDatas)
	{
		if (snapData._spriteSnapExist)
		{
			snapData._targetObject->GetComponent<SpriteRenderer>()->SetSprite(snapData._sheetName, snapData._spriteName);
		}
		if (snapData._positionSnapExist)
		{
			snapData._targetObject->SetLocalTranslateVector((float)snapData._positionSnap.x, (float)snapData._positionSnap.y);
		}
		if (snapData._rotateSnapExist)
		{
			snapData._targetObject->SetLocalRotateVector((float)snapData._rotateSnap.x, (float)snapData._rotateSnap.y);
		}
		if (snapData._scaleSnapExist)
		{
			snapData._targetObject->SetLocalScaleVector((float)snapData._scaleSnap.x, (float)snapData._scaleSnap.y);
		}
	}
}

void AnimationSnap::InitEvent()
{
	for (auto& iter : _snapDatas)
	{
		if (iter._eventSnapExist && iter._isDone)
		{
			iter._isDone = false;
		}
	}
}
