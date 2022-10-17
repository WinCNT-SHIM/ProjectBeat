#include "EngineCamera.h"

EngineCamera::EngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY)
{
    SetEngineCamera(_PosX, _PosY, _SizeX, _SizeY);
}

EngineCamera::~EngineCamera()
{
}

void EngineCamera::SetEngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY, float _ZoomX /*= 1*/, float _ZoomY /*= 1*/, float _RotX /*= 1*/, float _RotY /*= 0*/)
{
    this->m_PosX = _PosX;
    this->m_PosY = _PosY;
    this->m_SizeX = _SizeX;
    this->m_SizeY = _SizeY;
    this->m_ZoomX = _ZoomX;
    this->m_ZoomY = _ZoomY;
    this->m_RotX = _RotX;
    this->m_RotY = _RotY;
}

void EngineCamera::MakeEngineCameraTM()
{
    D2D1::Matrix3x2F _resMX = D2D1::Matrix3x2F::Identity();
    D2D1::Matrix3x2F _TranslateMX = MakeTranslateMX(m_PosX, m_PosY);
    // 카메라 위치의 역행렬 => 원점으로 옮기기
    D2D1::Matrix3x2F _CenterMX = MakeTranslateMX(m_SizeX / 2, m_SizeY / 2);
    _CenterMX.Invert();
    // 카메라의 회전
    D2D1::Matrix3x2F _RotateMX = MakeRotateMX(m_RotX, m_RotY);
    // 카메라의 스케일(줌)
    D2D1::Matrix3x2F _ScaleMX = MakeScaleMX(m_ZoomX, m_ZoomY);

    // 카메라를 원점으로 옮겨서 회전함
    _resMX = _resMX * _ScaleMX;
    _resMX = _resMX * _RotateMX;
    _CenterMX.Invert();
    _resMX = _resMX * _TranslateMX;

    // 카메라 행렬의 역행렬을 보관
    _resMX.Invert();
    m_EngineCameraTM = _resMX;
}

D2D1_MATRIX_3X2_F EngineCamera::GetCameraTM()
{
    return m_EngineCameraTM;
}

D2D1::Matrix3x2F EngineCamera::MakeTranslateMX(float x, float y)
{
    D2D1::Matrix3x2F mx;
    mx.m11 = 1;  mx.m12 = 0;
    mx.m21 = 0;  mx.m22 = 1;
    mx.dx  = x;  mx.dy  = y;
    return mx;
}

// 
//D2D1::Matrix3x2F EngineCamera::MakeRotateMX(float Deg)
//{
//    float Rad = Deg * PI / 180.0f;
//    D2D1::Matrix3x2F mx;
//    mx.m11 = cos(Rad);   mx.m12 = sin(Rad);
//    mx.m21 = -sin(Rad);  mx.m22 = cos(Rad);
//    mx.dx  = 0;          mx.dy  = 0;
//    return mx;
//}

D2D1::Matrix3x2F EngineCamera::MakeRotateMX(float x, float y)
{
    D2D1::Matrix3x2F mx;
    mx.m11 = x;   mx.m12 = y;
    mx.m21 = -y;  mx.m22 = x;
    mx.dx = 0;    mx.dy = 0;
    return mx;
}

D2D1::Matrix3x2F EngineCamera::MakeScaleMX(float x, float y)
{
    D2D1::Matrix3x2F mx;
    mx.m11 = x;  mx.m12 = 0;
    mx.m21 = 0;  mx.m22 = y;
    mx.dx  = 0;  mx.dy  = 0;
    return mx;
}
