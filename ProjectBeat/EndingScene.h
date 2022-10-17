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
	// 엔딩 화면
	//SpriteObject* m_EndingSprite;
	vector<SpriteObject*> m_EndingSprite;
	const int m_MaxEndingScene = 3;
	// 출력할 엔딩 화면 이름
	//string m_SheetName = "0022_EndingDrum";
	//string m_SpriteAll = "0022_EndingDrum1";
	vector<string> m_SpriteAll;
	// 현재 출력 스트라이트
	int m_CurSprite = 0;
	// 엔딩 출력 타이머
	float m_SceneChangeTimer = 0;
	// 페이드 인 아웃 관련
	float m_FadeTimer = 0;
	float m_FadeAlpha = 0;
	float m_FadeSpeed = 0.5f;
// 함수
public:
	void Start() override;
	void Update() override;
	void Render(D2DEngine* m_Engine) override;
private:
	void FadeIn(SpriteObject* _Sprite);
	void FadeOut(SpriteObject* _Sprite);
};

