#pragma once
#include "IUIComponent.h"
enum class SliderMode
{
    Vertical,
    Horizontal
};
class SpriteRenderer;

class Slider :
    public IUIComponent
{
public:
    Slider(GameObject* gameObject);
    virtual ~Slider();

private:
	std::vector<EventData> m_Events;
    float m_Slider;

    // 화면 좌표 기준
    Vector2D m_Min;
    Vector2D m_Max;
    Vector2D m_Cen;

    SliderMode m_Mode;

    RECT bgRect;

	// 슬라이더 BG
	GameObject* m_BGObj;
	SpriteRenderer* m_BgSr;
    // 슬라이더 바
    GameObject* m_BarObj;
    SpriteRenderer* m_BarSr;
    // 슬라이더 버튼
    GameObject* m_SliderObj;

 
public:
    // 슬라이더 버튼, 슬라이더 바, 슬라이더 범위, 슬라이더 방향(0 수직 1 수평), 초기 슬라이더 값
    void Init(GameObject* m_SliderObj, GameObject* m_BarObj, GameObject* bgObj, RECT minMax, int mode, float initValue);

    virtual void Update();
    virtual void SetName() { m_Name = "Slider"; }

    // 0~1 사이 값 슬라이더 조절
    void SetSlider(float alpha);
    float GetSlider();

	virtual void SetFocus(bool focus) override;
	virtual void OnLButtonClick(float mousePosx, float mousePosy) override;
	virtual void OnLButtonDown(float mousePosx, float mousePosy) override;
	virtual void OnLButtonUp(float mousePosx, float mousePosy) override;
	virtual void OnMouseMove(float mousePosx, float mousePosy) override;
	virtual void AddEvent(EventData eventData) override;

	virtual RECT GetRect() override;
};

