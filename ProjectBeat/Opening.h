#pragma once

class Opening : public Component
{
public:
	Opening(GameObject* _GameObject);
	virtual ~Opening();

private:
	float m_FadeAlpha = 1.0f;
	SpriteRenderer* m_Renderer;
	int m_SheetIndex = 28;
	int m_SheetCount = 1;
	int m_Count = 1;
	float m_FadeSpeed = 0.5f;

	bool m_isFade = false;

	int m_TimeKey[14] = {5,3,3,3,4,2,3,4,2,3,4,2,3,7};
	int m_TimeIndex;
	float m_Timer = 0;

	// 게임 패드 진동 타이머
	float m_VibrationTimer = 0;
public:
	virtual void Start();
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render(D2DEngine* _pEngine); // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더
	virtual void SetName() { m_Name = "Opening"; };

	void NextScene();
	bool FadeIn();
	bool FadeOut();
	void FadeObj(GameObject* parent);
};

