#pragma once

#include "CBase.h"
#include <windows.h>
#include <xinput.h>
#pragma comment(lib, "xinput.lib")

#define UP 1
#define PRESS 2
#define DOWN 3
#define KEYBORAD CPlayerInput::GetPlayerInput()


// �÷��̾� ���� ���� ��Ʈ�ѷ� Ű�� ���(�̸�)�� �����ϰ� �;��� ���̶� �׳� enum ���
// 2022.02.24 �ɽ¼�
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
/// Ű, ���콺 �Է� ������.
/// 2022.01.02 �ż���
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

	unsigned char cur[256];//���� Ű
	unsigned char old[256];//������ Ű
	unsigned char map[256];//���� Ű�� ����. Press, Down, Up
	void KeyCheck();
	
	/// <summary>
	/// XBox ��Ʈ�ѷ� üũ��
	/// 2022.02.24 �ɽ¼�
	/// </summary>
	std::map<int, vector<unsigned char>> m_OldPadState;
	std::map<int, vector<unsigned char>> m_CurPadState;
	std::map<int, vector<unsigned char>> m_MapPadState;
	//XINPUT_STATE m_MapPadState[4];
	void XBoxControllerCheck();

public:
	static CPlayerInput* GetPlayerInput() { return Instance; }
	void Update();
	//���콺 ��ġ ��ȯ
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

	// XBox ��Ʈ�ѷ���
	bool XBoxPadDown(int _PlayerIndex, XBoxPadInput _Input);
	bool XBoxPadUp(int _PlayerIndex, XBoxPadInput _Input);
	bool XBoxPadPress(int _PlayerIndex, XBoxPadInput _Input);
	unsigned char IsXBoxPadKeyDown(int _PlayerIndex);
	unsigned char IsXBoxPadUpDown(int _PlayerIndex);

	void SetXBoxPadVibration(int _PlayerIndex, WORD _LeftMotorSpeed = 65535, WORD _RightMotorSpeed = 65535);
	void StopXBoxPadVibration(int _PlayerIndex);
};

