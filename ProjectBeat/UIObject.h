#pragma once
#include "GameObject.h"

class CameraObject;
class SpriteRenderer;

/// <summary>
/// UI 오브젝트
/// 2022.02.15 심승수
/// </summary>
class UIObject :
    public GameObject
{
// 생성자 및 초기화
public:
    UIObject(std::string _UIName, CameraObject* _CameraObject, string _SheetName, string _SpriteName, float _alpha = 1.f, float _ratio = 1.f);
    virtual ~UIObject();
    void Init();
// 변수
private:
    // UI 위치에 관한 트랜스폼
    //Transform* m_tr;
    // UI 스프라이트를 컨트롤하기 위한 Shortcut
    SpriteRenderer* m_UIRenderer;
// 함수
public:
    SpriteRenderer* GetUIRenderer() const { return m_UIRenderer; }
    void SetUIRenderer(SpriteRenderer* val) { m_UIRenderer = val; }
};
