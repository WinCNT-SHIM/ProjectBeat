#include "GamePCH.h"
#include "CameraObject.h"

CameraObject::CameraObject(Vector2D _pos /*= Vector2D(0, 0)*/, Vector2D _Rc /*= Vector2D(0, 0)*/):
    GameObject(_pos)
{
    SetName("CameraObject");
    //AddComponent<RectRender>()->Init(-_Rc.x, -_Rc.y, _Rc.x, _Rc.y);
    m_CameraComponent = AddComponent<CameraComponent>();
    m_CameraComponent->Init();
}

CameraObject::~CameraObject()
{
}
