#pragma once
#include "IScene.h"
class EndingScene :
    public IScene
{
public:
	EndingScene();
	~EndingScene();
	void Init(int _CharIndex = 0);
private:
	// ���� ȭ��
	//SpriteObject* m_EndingSprite;
	vector<SpriteObject*> m_EndingSprite;
	const int m_MaxEndingScene = 3;
	// ����� ���� ȭ�� �̸�
	//string m_SheetName = "0022_EndingDrum";
	//string m_SpriteAll = "0022_EndingDrum1";
	vector<string> m_SpriteAll;
	// ���� ��� ��Ʈ����Ʈ
	int m_CurSprite = 0;
	// ���� ��� Ÿ�̸�
	float m_SceneChangeTimer = 0;
	// ���̵� �� �ƿ� ����
	float m_FadeTimer = 0;
	float m_FadeAlpha = 0;
	float m_FadeSpeed = 0.5f;
// �Լ�
public:
	void Start() override;
	void Update() override;
	void Render(D2DEngine* m_Engine) override;
private:
	void FadeIn(SpriteObject* _Sprite);
	void FadeOut(SpriteObject* _Sprite);
};

