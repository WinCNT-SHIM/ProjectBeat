#pragma once
#include "Component.h"

// 게임 오브젝트의 트랜스폼(숏컷)
class Transform;

/// <summary>
/// 카메라 컴포넌트
/// 이동, 회전, 줌 가능
/// GameObject에 AddComponent한 카메라 오브젝트를
/// 씬 등에서 컨트롤하면서 사용할 것
/// 2022.02.11 심승수
/// </summary>
class CameraComponent :
    public Component
{
//생성자
public:
    CameraComponent(GameObject* _GameObject);
    virtual ~CameraComponent();
    void Init(float _PosX = 0, float _PosY = 0, float _SizeX = 1920, float _SizeY = 1080, float _ZoomX = 1, float _ZoomY = 1, float _Degree = 0);
// 변수
private:
    // 카메라의 위치 등 GameObject의 Transform에서 획득하자
    Transform* m_tr;
    // 카메라의 크기
    /// 카메라의 크기는 화면 크기 그 자체로
    /// 게임 도중에 변경될 예정은 없음
    /// (화면이 변경되도 스케일이 조정될 뿐 카메라의 크기는 그대로)
    Vector2D m_Size;
    
//함수
public:
    // 순수 가상 함수 구현
    void Update() override;
    void Render(D2DEngine* _pEngine) override;
    void SetName() override { m_Name = "CameraComponent"; };
    // 카메라 제어 함수
    Vector2D GetPos();
    void SetPos(Vector2D _Pos);
    Vector2D GetSize();
    void SetSize(Vector2D _Size);
    Vector2D GetZoom() const;
    void SetZoom(Vector2D val);
    Vector2D GetRotation() const;
    void SetRotation(float _Degree);
};

