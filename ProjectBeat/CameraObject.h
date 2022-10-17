#pragma once
#include "GameObject.h"

class CameraComponent;

/// <summary>
/// 기본 카메라 오브젝트
/// 기본적으로 카메라를 사용하고 싶은 곳(씬 등)의 초기화 시,
/// 해당 클래스의 객체를 생성해서 가지고  
/// 오브젝트 매니저에 맨 마지막에 넣어주면 된다.
/// 
/// 2022.02.11 심승수
/// </summary>
class CameraObject :
    public GameObject
{
public:
    CameraObject(Vector2D _pos = Vector2D(0, 0), Vector2D _Rc = Vector2D(0, 0));
    virtual ~CameraObject();
    // 카메라를 컨트롤하기 위한 카메라 컴포넌트의 Shortcut
    CameraComponent* m_CameraComponent;
};

