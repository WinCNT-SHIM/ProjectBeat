#pragma once
#include "Component.h"

// ���� ������Ʈ�� Ʈ������(����)
class Transform;

/// <summary>
/// ī�޶� ������Ʈ
/// �̵�, ȸ��, �� ����
/// GameObject�� AddComponent�� ī�޶� ������Ʈ��
/// �� ��� ��Ʈ���ϸ鼭 ����� ��
/// 2022.02.11 �ɽ¼�
/// </summary>
class CameraComponent :
    public Component
{
//������
public:
    CameraComponent(GameObject* _GameObject);
    virtual ~CameraComponent();
    void Init(float _PosX = 0, float _PosY = 0, float _SizeX = 1920, float _SizeY = 1080, float _ZoomX = 1, float _ZoomY = 1, float _Degree = 0);
// ����
private:
    // ī�޶��� ��ġ �� GameObject�� Transform���� ȹ������
    Transform* m_tr;
    // ī�޶��� ũ��
    /// ī�޶��� ũ��� ȭ�� ũ�� �� ��ü��
    /// ���� ���߿� ����� ������ ����
    /// (ȭ���� ����ǵ� �������� ������ �� ī�޶��� ũ��� �״��)
    Vector2D m_Size;
    
//�Լ�
public:
    // ���� ���� �Լ� ����
    void Update() override;
    void Render(D2DEngine* _pEngine) override;
    void SetName() override { m_Name = "CameraComponent"; };
    // ī�޶� ���� �Լ�
    Vector2D GetPos();
    void SetPos(Vector2D _Pos);
    Vector2D GetSize();
    void SetSize(Vector2D _Size);
    Vector2D GetZoom() const;
    void SetZoom(Vector2D val);
    Vector2D GetRotation() const;
    void SetRotation(float _Degree);
};

