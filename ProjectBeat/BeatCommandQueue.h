#pragma once
#include <queue>

class BeatCommandQueue
{
public:
	BeatCommandQueue(char _KeyA, char _KeyS, string _SheetName, Vector2D _BeatBurstPos, int _CharIndex , int _BeatCount , int _PlayerIndex);
	~BeatCommandQueue();

private:
	//1,2 플레이어 몇 인지
	int m_PlayerIndex;
	int m_BeatCount;
	queue<SpriteObject*> m_CommandSprite;
	queue<char> m_CommandChar;

	char m_KeyA;
	char m_KeyS;

	int m_CharIndex = 0;
	string m_SoundName;

	Vector2D m_CommandPos;
	Vector2D m_BeatBurstPos;
	string m_SheetName;
	SpriteObject* m_BeatBurstObject;
	float m_Size = 0.5f;

	int m_CommandBarSize;
public:
	float GetSize() { return m_Size; }
	void SetSize(float _Size);
public:
	bool CompareOther(BeatCommandQueue* _Other);
	virtual void Update(); // 키보드 업데이트를 받기위해서임! 씬에서 직접 돌려주자.

};

