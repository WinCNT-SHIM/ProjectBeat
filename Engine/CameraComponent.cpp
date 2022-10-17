#include "stdafx.h"
#include "CameraComponent.h"

CameraComponent::CameraComponent(GameObject* _GameObject):
    Component(_GameObject),
    m_tr(_GameObject->m_tr)
{
    // 카메라 크기(=화면 크기) 디폴트 값
    this->Init();
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Init(float _PosX /*= 0*/, float _PosY /*= 0*/, float _SizeX /*= 1920*/, float _SizeY /*= 1080*/, float _ZoomX /*= 1*/, float _ZoomY /*= 1*/, float _Degree /*= 0*/)
{
    SetPos(Vector2D(_PosX, _PosY));
    SetSize(Vector2D(_SizeX, _SizeY));
    SetZoom(Vector2D(_ZoomX, _ZoomY));
    SetRotation(_Degree);
}

void CameraComponent::Update()
{
}

void CameraComponent::Render(D2DEngine* _pEngine)
{
    Vector2D _pos = m_tr->GetWorldTranslate();
    Vector2D _size = m_Size;
    Vector2D _pivot = m_tr->m_Pivot;
    Vector2D _zoom = m_tr->GetWorldScale();
    Vector2D _rot = m_tr->GetWorldRotate();
    _pEngine->SetEngineCamera(_pos.x, _pos.y, _size.x, _size.y, _zoom.x, _zoom.y, _rot.x, _rot.y);
}

Vector2D CameraComponent::GetPos()
{
    //return m_tr->GetWorldTranslate();
    return m_tr->GetLocalTranslate();
}

void CameraComponent::SetPos(Vector2D _Pos)
{
    m_tr->SetLocalTranslateVector(_Pos);
    Vector2D _Pivoit = this->m_tr->m_Pivot;
}

Vector2D CameraComponent::GetSize()
{
    return m_Size;
}

void CameraComponent::SetSize(Vector2D _Size)
{
    this->m_Size = _Size;
    this->m_tr->m_Pivot = { _Size.x / 2, _Size.y / 2 };
}

Vector2D CameraComponent::GetZoom() const
{
    // 카메라에서 스케일의 역행렬을 하기 때문에
    // 줌 획득에서 스케일 값을 역으로 바꿔준다
    //return m_tr->GetWorldScale();
    Vector2D _res =m_tr->GetLocalScale();

    if (_res.x <= 0) _res.x = 0;
    else _res.x = 1 / _res.x;

    if (_res.y <= 0) _res.y = 0;
    else _res.y = 1 / _res.y;

    return _res;
}

void CameraComponent::SetZoom(Vector2D val)
{
    // 카메라에서 스케일의 역행렬을 하기 때문에
    // 줌 설정에서 스케일 값을 역으로 바꿔준다
    if (val.x <= 0) val.x = 0;
    else val.x = 1 / val.x;

    if (val.y <= 0) val.y = 0;
    else val.y = 1 / val.y;

    m_tr->SetLocalScaleVector(val);
}

Vector2D CameraComponent::GetRotation() const
{
    //return m_tr->GetWorldRotate();
    return m_tr->GetLocalRotate();
}

void CameraComponent::SetRotation(float _Degree)
{
    m_tr->SetLocalRotateVector(_Degree);
}
