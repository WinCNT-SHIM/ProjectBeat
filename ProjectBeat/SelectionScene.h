#pragma once
#include "IScene.h"

//class InGameUIManager;	// 인게임 UI 매니저
class UIObject;

class SelectionScene : public IScene
{
public:
	SelectionScene();
	~SelectionScene();
	// 변수
private:
	// 인게임 UI 매니저지만 비슷한 기능이 있어서 그대로 사용
	// ...하려고 했지만 취소함
	//InGameUIManager* m_InGameUIManager;
	// UI의 카메라 오브젝트 숏컷
	CameraObject* m_SceneCamera;

	// 셀렉트 시간 관련
	float m_DeltaTime = 0;
	int m_CurSelectTime = 60;
	// 셀렉트 시간 UI
	UIObject* m_RoundTimeUI_TenDigit[10];
	UIObject* m_RoundTimeUI_OneDigit[10];

	list<SpriteRenderer*> m_RendererList;
	float m_FadeAlpha = 0.0f;
	float m_FadeSpeed = 0.5f;
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(D2DEngine* m_Engine) override;

private:
	/// <summary>
	/// 셀렉트 제한 시간의 UI를 끄고 켜는 함수
	/// </summary>
	void SetSelectTimeUI(int _CurRoundTime, bool _IsShow = true);

	bool FadeIn();
	bool FadeOut();
};

