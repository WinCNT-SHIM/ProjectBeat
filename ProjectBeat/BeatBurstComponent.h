#pragma once

#include <queue>

class UIObject;
class InGameUIManager;
class BeatCommandQueue;
class Character;

class BeatBurstComponent : public Component
{
public:
	BeatBurstComponent(GameObject* _GameObject);
	virtual ~BeatBurstComponent();
private:
	int m_BeatCount;

	BeatCommandQueue* m_Player1;
	BeatCommandQueue* m_Player2;

	int m_Player1Index; //ĳ���� �ε���. �ʻ�ȭ�� ���� ����
	int m_Player2Index;//ĳ���� �ε���. �ʻ�ȭ�� ���� ����

	float m_DeltaTime = 0;
	int m_CurSelectTime = 3; // Ÿ�̸� �� ��?

	bool _isPlayer1Input = false;
	bool _isPlayer2Input = false;

	bool m_isFirst = false;
	Character* m_Caster; //������.
	Character* m_victim; //�����.

	int m_Index = 0; //���� �����ߴ°�. 0 == �巳 1 == �ƹ��� 2 == ��Ÿ 3 == �ŵ������
	string m_SheetName; // �����ڿ� ���� ��Ʈ ��ü

	float SizeDeltaTime = 0;
	bool ChangeSize(BeatCommandQueue* _Player, float _Size);


	SpriteObject* TextBox1;
	SpriteObject* TextBox2;

	UIObject* m_RoundTimeUI_TenDigit[10];
	UIObject* m_RoundTimeUI_OneDigit[10];

	CameraObject* m_SceneCamera;

public:
	//������. �ǰݴ��ϴ� ���,
	void Init(Character* _Caster, Character* victim, bool _isPlayer1First, int _Index, int _Player1Index, int _Player2Index, int _BeatCount = 7);
	virtual void Start();
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void Render(D2DEngine* _pEngine); // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����
	void SetSelectTimeUI(int _CurRoundTime);
	virtual void SetName() { m_Name = "BeatBurstComponent"; }

};

