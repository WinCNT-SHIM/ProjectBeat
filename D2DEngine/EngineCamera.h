#pragma once
#include "D2DEngineMacro.h"

/// <summary>
/// 엔진 카메라 클래스
/// 게임에서 카메라 오브젝트의 정보(위치 등)을 받아
/// 그래픽스 엔진이 매 렌더 프레임(정확히는 BeginRender)에
/// 카메라 행렬을 계산하는 클래스
/// (카메라 행렬의 직접적인 적용은 그래픽스 엔진의 SetTransform에서 처리)
/// 
/// 2022.02.10 심승수
/// </summary>
class EngineCamera
{
// 생성자
public:
    EngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY);
    ~EngineCamera();
// 변수
private:
    // 파이
    const float PI = (float)3.14159265358979323846;
    // 엔진 카메라의 변수(SetEngineCamera로 설정함)
    // 위치
    float m_PosX;
    float m_PosY;
    // 크기
    float m_SizeX;
    float m_SizeY;
    // 줌
    float m_ZoomX;
    float m_ZoomY;
    // 회전
    float m_RotX;
    float m_RotY;
    //float m_Degree;
    //float m_Radian;
    // 엔진 카메라 행렬
    D2D1_MATRIX_3X2_F m_EngineCameraTM;
// 함수
public:
    /// <summary>
    /// 그래픽스 엔진의 카메라를 설정한다
    /// </summary>
    /// <param name="_PosX">카메라의 X좌표 위치</param>
    /// <param name="_PosY">카메라의 Y좌표 위치</param>
    /// <param name="_SizeX">카메라의 X좌표 크기</param>
    /// <param name="_SizeY">카메라의 Y좌표 크기</param>
    /// <param name="_ZoomX">카메라의 X좌표 비율</param>
    /// <param name="_ZoomY">카메라의 Y좌표 비율</param>
    /// <param name="_RotX">카메라의 X좌표 회전값(각도=>좌표로 변환한 값)</param>
    /// <param name="_RotY">카메라의 Y좌표 회전값(각도=>좌표로 변환한 값)</param>
    void SetEngineCamera(float _PosX, float _PosY, float _SizeX, float _SizeY, float _ZoomX = 1, float _ZoomY = 1, float _RotX = 1, float _RotY = 0);
    /// <summary>
    /// 입력받아 놓은 정보로 변환 행렬을 만든다.
    /// </summary>
    void MakeEngineCameraTM();
    D2D1_MATRIX_3X2_F GetCameraTM();
private:
    D2D1::Matrix3x2F MakeTranslateMX(float x, float y);
    D2D1::Matrix3x2F MakeRotateMX(float x, float y);
    D2D1::Matrix3x2F MakeScaleMX(float x, float y);
};

