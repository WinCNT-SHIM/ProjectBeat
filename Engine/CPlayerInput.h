#pragma once

#include "CBase.h"
#include <windows.h>
#include <xinput.h>
#pragma comment(lib, "xinput.lib")

#define UP 1
#define PRESS 2
#define DOWN 3
#define KEYBORAD CPlayerInput::GetPlayerInput()


// 플레이어 유저 수와 컨트롤러 키를 상수(이름)로 관리하고 싶었을 뿐이라 그냥 enum 사용
// 2022.02.24 심승수
enum XBoxPadPlayer
{
	Player1,
	Player2,
	PlayerMax
};

enum XBoxPadInput
{
	Up,
	Down,
	Left,
	Right,
	ButtonA,
	ButtonB,
	ButtonX,
	ButtonY,
	Start,
	Back,
	XInputKeyMax
};

/// <summary>
/// 
/// 키, 마우스 입력 구현중.
/// 2022.01.02 신성현
/// </summary
/// 
/// 
class CPlayerInput
{
public:
	CPlayerInput(HWND hWnd);
	~CPlayerInput();
private:
	HWND m_hWnd;
	static CPlayerInput* Instance;

	unsigned char cur[256];//현재 키
	unsigned char old[256];//이전의 키
	unsigned char map[256];//현재 키의 상태. Press, Down, Up
	void KeyCheck();
	
	/// <summary>
	/// XBox 컨트롤러 체크용
	/// 2022.02.24 심승수
	/// </summary>
	std::map<int, vector<unsigned char>> m_OldPadState;
	std::map<int, vector<unsigned char>> m_CurPadState;
	std::map<int, vector<unsigned char>> m_MapPadState;
	//XINPUT_STATE m_MapPadState[4];
	void XBoxControllerCheck();

public:
	static CPlayerInput* GetPlayerInput() { return Instance; }
	void Update();
	//마우스 위치 반환
	const Vector2D GetPos();

	bool KeyDonw(unsigned char _Key) { return map[_Key] == DOWN ? true : false; }
	bool KeyUp(unsigned char _Key) { return map[_Key] == UP ? true : false; }
	bool KeyPress(unsigned char _Key) { return map[_Key] == PRESS ? true : false; }
	unsigned char GetDownKey()
	{
		for (int i = 0; i < 256; i++)
		{
			if (map[i] == DOWN)
				return i;
		}
		return 0;
	}

	unsigned char GetUpKey()
	{
		for (int i = 0; i < 256; i++)
		{
			if (map[i] == UP)
				return i;
		}
		return 0;
	}

	// XBox 컨트롤러용
	bool XBoxPadDown(int _PlayerIndex, XBoxPadInput _Input);
	bool XBoxPadUp(int _PlayerIndex, XBoxPadInput _Input);
	bool XBoxPadPress(int _PlayerIndex, XBoxPadInput _Input);
	unsigned char IsXBoxPadKeyDown(int _PlayerIndex);
	unsigned char IsXBoxPadUpDown(int _PlayerIndex);

	void SetXBoxPadVibration(int _PlayerIndex, WORD _LeftMotorSpeed = 65535, WORD _RightMotorSpeed = 65535);
	void StopXBoxPadVibration(int _PlayerIndex);
};

