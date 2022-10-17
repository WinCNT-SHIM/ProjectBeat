#pragma once
#include "string"
#include "D2DEngine.h"
#include "DeBugPrint.h"
#include "CTime.h"

#include "Component.h"
#include "GameObject.h"
#include "Collider.h"
#include "Physics.h"
#include "Transform.h"

#include "Effect.h"
#include "RectRender.h"
#include "CircleRender.h"

#include "SpriteRenderer.h"
#include "SpriteAnimationClip.h"
#include "SpriteAnimator.h"

#include "CircleCollider.h"
#include "OBBCollider.h"
#include "AABBCollider.h"

#include "GameManager.h"
#include "CPlayerInput.h"
#include "IScene.h"
#include "SceneManager.h"
#include "GameProcess.h"
#include "D2DSprite.h"
#include "ResourceManager.h"

#include "CameraObject.h"
#include "CameraComponent.h"

#include "OBBObject.h"
#include "RectObject.h"
#include "CircleObject.h"
#include "SpriteObject.h"

#include "ObjectManager.h"

#include "InstanceGetter.h"
#include "ISoundManager.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif