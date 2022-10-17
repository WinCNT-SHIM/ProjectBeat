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

    // ȭ�� ��ǥ ����
    Vector2D m_Min;
    Vector2D m_Max;
    Vector2D m_Cen;

    SliderMode m_Mode;

    RECT bgRect;

	// �����̴� BG
	GameObject* m_BGObj;
	SpriteRenderer* m_BgSr;
    // �����̴� ��
    GameObject* m_BarObj;
    SpriteRenderer* m_BarSr;
    // �����̴� ��ư
    GameObject* m_SliderObj;

 
public:
    // �����̴� ��ư, �����̴� ��, �����̴� ����, �����̴� ����(0 ���� 1 ����), �ʱ� �����̴� ��
    void Init(GameObject* m_SliderObj, GameObject* m_BarObj, GameObject* bgObj, RECT minMax, int mode, float initValue);

    virtual void Update();
    virtual void SetName() { m_Name = "Slider"; }

    // 0~1 ���� �� �����̴� ����
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

