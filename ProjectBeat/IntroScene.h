#pragma once
#include "IScene.h"
#include "SpriteObject.h"

/// <summary>
/// 인트로(타이틀) 씬
/// 2022.02.14 심승수
/// </summary>
class IntroScene : public IScene
{
// 생성자
public:
	IntroScene();
	~IntroScene();
// 변수
private:
	//// 타이틀 화면
 //   SpriteObject* m_Title;
	//// 타이틀 화면 커서
	//SpriteObject* m_Cursor;
	//// 커서 좌표
	//Vector2D m_CursorPos;
    // 커서 이동 관련
	int m_MenuCnt = 0;
	const int m_MenuMax = 3;
	const float m_CursorMoveLen = 123.0f;
// 함수
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(D2DEngine* m_Engine) override;
};

