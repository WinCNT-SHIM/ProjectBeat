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

	// ���� �е� ���� Ÿ�̸�
	float m_VibrationTimer = 0;
public:
	virtual void Start();
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render(D2DEngine* _pEngine); // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����
	virtual void SetName() { m_Name = "Opening"; };

	void NextScene();
	bool FadeIn();
	bool FadeOut();
	void FadeObj(GameObject* parent);
};

