#pragma once
#include "IScene.h"
#include "SpriteObject.h"

/// <summary>
/// ��Ʈ��(Ÿ��Ʋ) ��
/// 2022.02.14 �ɽ¼�
/// </summary>
class IntroScene : public IScene
{
// ������
public:
	IntroScene();
	~IntroScene();
// ����
private:
	//// Ÿ��Ʋ ȭ��
 //   SpriteObject* m_Title;
	//// Ÿ��Ʋ ȭ�� Ŀ��
	//SpriteObject* m_Cursor;
	//// Ŀ�� ��ǥ
	//Vector2D m_CursorPos;
    // Ŀ�� �̵� ����
	int m_MenuCnt = 0;
	const int m_MenuMax = 3;
	const float m_CursorMoveLen = 123.0f;
// �Լ�
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void Render(D2DEngine* m_Engine) override;
};

