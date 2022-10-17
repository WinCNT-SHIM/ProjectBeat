#pragma once
#include "IScene.h"

//class InGameUIManager;	// �ΰ��� UI �Ŵ���
class UIObject;

class SelectionScene : public IScene
{
public:
	SelectionScene();
	~SelectionScene();
	// ����
private:
	// �ΰ��� UI �Ŵ������� ����� ����� �־ �״�� ���
	// ...�Ϸ��� ������ �����
	//InGameUIManager* m_InGameUIManager;
	// UI�� ī�޶� ������Ʈ ����
	CameraObject* m_SceneCamera;

	// ����Ʈ �ð� ����
	float m_DeltaTime = 0;
	int m_CurSelectTime = 60;
	// ����Ʈ �ð� UI
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
	/// ����Ʈ ���� �ð��� UI�� ���� �Ѵ� �Լ�
	/// </summary>
	void SetSelectTimeUI(int _CurRoundTime, bool _IsShow = true);

	bool FadeIn();
	bool FadeOut();
};

