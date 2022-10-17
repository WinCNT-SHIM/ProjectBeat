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

	int m_Player1Index; //캐릭터 인덱스. 초상화를 띄우기 위함
	int m_Player2Index;//캐릭터 인덱스. 초상화를 띄우기 위함

	float m_DeltaTime = 0;
	int m_CurSelectTime = 3; // 타이머 몇 초?

	bool _isPlayer1Input = false;
	bool _isPlayer2Input = false;

	bool m_isFirst = false;
	Character* m_Caster; //공격자.
	Character* m_victim; //방어자.

	int m_Index = 0; //누가 시전했는가. 0 == 드럼 1 == 탬버린 2 == 기타 3 == 신디사이저
	string m_SheetName; // 시전자에 따른 시트 교체

	float SizeDeltaTime = 0;
	bool ChangeSize(BeatCommandQueue* _Player, float _Size);


	SpriteObject* TextBox1;
	SpriteObject* TextBox2;

	UIObject* m_RoundTimeUI_TenDigit[10];
	UIObject* m_RoundTimeUI_OneDigit[10];

	CameraObject* m_SceneCamera;

public:
	//시전자. 피격당하는 사람,
	void Init(Character* _Caster, Character* victim, bool _isPlayer1First, int _Index, int _Player1Index, int _Player2Index, int _BeatCount = 7);
	virtual void Start();
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void Render(D2DEngine* _pEngine); // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더
	void SetSelectTimeUI(int _CurRoundTime);
	virtual void SetName() { m_Name = "BeatBurstComponent"; }

};

