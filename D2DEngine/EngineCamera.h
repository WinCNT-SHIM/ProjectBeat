#pragma once
#include "D2DEngineMacro.h"

/// <summary>
/// ���� ī�޶� Ŭ����
/// ���ӿ��� ī�޶� ������Ʈ�� ����(��ġ ��)�� �޾�
/// �׷��Ƚ� ������ �� ���� ������(��Ȯ���� BeginRender)��
/// ī�޶� ����� ����ϴ� Ŭ����
/// (ī�޶� ����� �������� ������ �׷��Ƚ� ������ SetTransform���� ó��)
/// 
/// 2022.02.10 �ɽ¼�
/// </summary>
class EngineCamera
{
// ������
public:
    EngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY);
    ~EngineCamera();
// ����
private:
    // ����
    const float PI = (float)3.14159265358979323846;
    // ���� ī�޶��� ����(SetEngineCamera�� ������)
    // ��ġ
    float m_PosX;
    float m_PosY;
    // ũ��
    float m_SizeX;
    float m_SizeY;
    // ��
    float m_ZoomX;
    float m_ZoomY;
    // ȸ��
    float m_RotX;
    float m_RotY;
    //float m_Degree;
    //float m_Radian;
    // ���� ī�޶� ���
    D2D1_MATRIX_3X2_F m_EngineCameraTM;
// �Լ�
public:
    /// <summary>
    /// �׷��Ƚ� ������ ī�޶� �����Ѵ�
    /// </summary>
    /// <param name="_PosX">ī�޶��� X��ǥ ��ġ</param>
    /// <param name="_PosY">ī�޶��� Y��ǥ ��ġ</param>
    /// <param name="_SizeX">ī�޶��� X��ǥ ũ��</param>
    /// <param name="_SizeY">ī�޶��� Y��ǥ ũ��</param>
    /// <param name="_ZoomX">ī�޶��� X��ǥ ����</param>
    /// <param name="_ZoomY">ī�޶��� Y��ǥ ����</param>
    /// <param name="_RotX">ī�޶��� X��ǥ ȸ����(����=>��ǥ�� ��ȯ�� ��)</param>
    /// <param name="_RotY">ī�޶��� Y��ǥ ȸ����(����=>��ǥ�� ��ȯ�� ��)</param>
    void SetEngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY, float _ZoomX = 1, float _ZoomY = 1, float _RotX = 1, float _RotY = 0);
    /// <summary>
    /// �Է¹޾� ���� ������ ��ȯ ����� �����.
    /// </summary>
    void MakeEngineCameraTM();
    D2D1_MATRIX_3X2_F GetCameraTM();
private:
    D2D1::Matrix3x2F MakeTranslateMX(float x, float y);
    D2D1::Matrix3x2F MakeRotateMX(float x, float y);
    D2D1::Matrix3x2F MakeScaleMX(float x, float y);
};

