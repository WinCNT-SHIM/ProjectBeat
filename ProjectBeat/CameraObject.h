#pragma once
#include "GameObject.h"

class CameraComponent;

/// <summary>
/// �⺻ ī�޶� ������Ʈ
/// �⺻������ ī�޶� ����ϰ� ���� ��(�� ��)�� �ʱ�ȭ ��,
/// �ش� Ŭ������ ��ü�� �����ؼ� ������  
/// ������Ʈ �Ŵ����� �� �������� �־��ָ� �ȴ�.
/// 
/// 2022.02.11 �ɽ¼�
/// </summary>
class CameraObject :
    public GameObject
{
public:
    CameraObject(Vector2D _pos = Vector2D(0, 0), Vector2D _Rc = Vector2D(0, 0));
    virtual ~CameraObject();
    // ī�޶� ��Ʈ���ϱ� ���� ī�޶� ������Ʈ�� Shortcut
    CameraComponent* m_CameraComponent;
};

