#include "stdafx.h"
#include "CPlayerInput.h"

CPlayerInput* CPlayerInput::Instance = nullptr;

CPlayerInput::CPlayerInput(HWND hWnd) : m_hWnd(hWnd)
{
	if (Instance == nullptr)
	{
		Instance = this;
	}
	else
		delete this;

	// XBox 컨트롤러 체크 관련 초기화
	vector<unsigned char> _tmp;
	for (int i = 0; i < XBoxPadInput::XInputKeyMax; i++)
		_tmp.push_back(0);
	for (int i = 0; i < XBoxPadPlayer::PlayerMax; i++)
	{
		m_OldPadState.insert({ i , _tmp });
		m_CurPadState.insert({ i , _tmp });
		m_MapPadState.insert({ i , _tmp });
	}
}

CPlayerInput::~CPlayerInput()
{
}

void CPlayerInput::Update()
{
	KeyCheck();
}


void CPlayerInput::KeyCheck()
{
	// XBox 컨트롤러 체크
	XBoxControllerCheck();

	//현재 값 과거로 복사
	memcpy(old, cur, sizeof(cur));

	//현재 값, 현재 키보드 입력값 초기화.
	memset(cur, 0, sizeof(cur));
	memset(map, 0, sizeof(cur));

	//현재 값 불러오기.
	GetKeyboardState(cur);

	for (int i = 0; i < 256; i++)
	{
		
		unsigned char _cur = cur[i] & 0x80 ? 1 : 0;
		unsigned char _old = old[i] & 0x80 ? 1 : 0;


		//Press
		if (_cur && _old)
			map[i] = PRESS;
		//Down
		else if (_cur && !_old)
			map[i] = DOWN;
		//Up
		else if (!_cur && _old)
			map[i] = UP;
		else
			map[i] = 0;
			
	}
}

void CPlayerInput::XBoxControllerCheck()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT - 2; i++)
	{
		//현재 값 과거로 복사
		fill((*m_OldPadState.find(i)).second.begin(), (*m_OldPadState.find(i)).second.end(), 0);
		std::copy((*m_CurPadState.find(i)).second.begin(), (*m_CurPadState.find(i)).second.end(), (*m_OldPadState.find(i)).second.begin());

		//현재 값, 현재 컨트롤러 입력값 초기화
		fill((*m_CurPadState.find(i)).second.begin(), (*m_CurPadState.find(i)).second.end(), 0);
		fill((*m_MapPadState.find(i)).second.begin(), (*m_MapPadState.find(i)).second.end(), 0);

		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		// XInput에서 컨트롤러의 상태를 획득한다
		// Simply get the state of the controller from XInput
		dwResult = XInputGetState(i, &state);

		// 아날로그 스틱 데드 존 설정
		//float INPUT_DEADZONE = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
		float LX = state.Gamepad.sThumbLX;
		float LY = state.Gamepad.sThumbLY;

		//determine how far the controller is pushed
		float magnitude = sqrt(LX * LX + LY * LY);

		//determine the direction the controller is pushed
		float normalizedLX = LX / magnitude;
		float normalizedLY = LY / magnitude;

		float normalizedMagnitude = 0;

		//check if the controller is outside a circular dead zone
		if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			//clip the magnitude at its expected maximum value
			if (magnitude > 32767) magnitude = 32767;

			//adjust magnitude relative to the end of the dead zone
			magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

			//optionally normalize the magnitude with respect to its expected range
			//giving a magnitude value of 0.0 to 1.0
			normalizedMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		}
		else //if the controller is in the deadzone zero out the magnitude
		{
			magnitude = 0.0;
			normalizedMagnitude = 0.0;
		}

		//repeat for right thumb stick


		// 컨트롤러 연결 성공
		if (dwResult == ERROR_SUCCESS)
		{
			// Up
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP
				//|| state.Gamepad.sThumbLY > 0)
				|| (state.Gamepad.sThumbLY > 0 && normalizedMagnitude == 1))
				(*m_CurPadState.find(i)).second[XBoxPadInput::Up] = 1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::Up] = 0;
			// Down
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN
				//|| state.Gamepad.sThumbLY < 0)
				|| (state.Gamepad.sThumbLY < 0 && normalizedMagnitude == 1))
				(*m_CurPadState.find(i)).second[XBoxPadInput::Down] = 1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::Down] = 0;
			// Left
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT
				//|| state.Gamepad.sThumbLX < 0)
				|| (state.Gamepad.sThumbLX < 0 && normalizedMagnitude == 1))
				(*m_CurPadState.find(i)).second[XBoxPadInput::Left] = 1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::Left] = 0;
			// Right
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT
				//|| state.Gamepad.sThumbLX > 0)
				|| (state.Gamepad.sThumbLX > 0 && normalizedMagnitude == 1))
				(*m_CurPadState.find(i)).second[XBoxPadInput::Right] = 1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::Right] = 0;

			// 버튼
			// A버튼
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
				(*m_CurPadState.find(i)).second[XBoxPadInput::ButtonA] = (unsigned char)1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::ButtonA] = 0;
			// B버튼
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
				(*m_CurPadState.find(i)).second[XBoxPadInput::ButtonB] = 1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::ButtonB] = 0;
			// X버튼
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
				(*m_CurPadState.find(i)).second[XBoxPadInput::ButtonX] = 1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::ButtonX] = 0;
			// Y버튼
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
				(*m_CurPadState.find(i)).second[XBoxPadInput::ButtonY] = 1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::ButtonY] = 0;
			// Start버튼
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_START)
				(*m_CurPadState.find(i)).second[XBoxPadInput::Start] = 1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::Start] = 0;
			// Back버튼
			if (state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)
				(*m_CurPadState.find(i)).second[XBoxPadInput::Back] = 1;
			else
				(*m_CurPadState.find(i)).second[XBoxPadInput::Back] = 0;

			// KeyUp, KeyDown, KeyPress 체크
			for (int cnt = 0; cnt < XBoxPadInput::XInputKeyMax; cnt++)
			{
				if ((*m_CurPadState.find(i)).second[cnt] && (*m_OldPadState.find(i)).second[cnt])
					(*m_MapPadState.find(i)).second[cnt] = PRESS;
				else if ((*m_CurPadState.find(i)).second[cnt] && !((*m_OldPadState.find(i)).second[cnt]))
					(*m_MapPadState.find(i)).second[cnt] = DOWN;
				else if (!((*m_CurPadState.find(i)).second[cnt]) && (*m_OldPadState.find(i)).second[cnt])
					(*m_MapPadState.find(i)).second[cnt] = UP;
				else
					(*m_MapPadState.find(i)).second[cnt] = 0;
			}
			// CPU 점유을 100%를 방지하기 위해 넣으려 했으나 프레임 드랍이 너무 심해서 삭제
			//Sleep(30);
			dwResult = XInputGetState(0, &state);	// 다음 상태 얻어오기
		}
		// 컨트롤러 연결 실패
		else
		{
#ifdef _DEBUG
			string _tmp = to_string(i) + "컨트롤러: 연결 실패!!!!!\n";
#endif // _DEBUG
			// CPU 점유을 100%를 방지하기 위해 넣으려 했으나 프레임 드랍이 너무 심해서 삭제
			//Sleep(30);	// CPU 점유을 100%를 방지하기 위해
			dwResult = XInputGetState(0, &state);	// 다음 상태 얻어오기
		}
	}
}

//마우스의 현재 위치를 리턴.
const Vector2D CPlayerInput::GetPos()
{
	POINT ptMouse;
	GetCursorPos(&ptMouse);
	ScreenToClient(m_hWnd, &ptMouse);
	Vector2D pos = { (float)ptMouse.x/*+ MyEngine::GetCamera()->GetPos().x*/,(float)ptMouse.y/*+ MyEngine::GetCamera()->GetPos().y*/ };

	return pos;
}

bool CPlayerInput::XBoxPadDown(int _PlayerIndex, XBoxPadInput _Input)
{
	return (*m_MapPadState.find(_PlayerIndex)).second[_Input] == DOWN ? true : false;
}

bool CPlayerInput::XBoxPadUp(int _PlayerIndex, XBoxPadInput _Input)
{
	return (*m_MapPadState.find(_PlayerIndex)).second[_Input] == UP ? true : false;
}

bool CPlayerInput::XBoxPadPress(int _PlayerIndex, XBoxPadInput _Input)
{
	return (*m_MapPadState.find(_PlayerIndex)).second[_Input] == PRESS ? true : false;
}

unsigned char CPlayerInput::IsXBoxPadKeyDown(int _PlayerIndex)
{
	for (int i = XBoxPadInput::ButtonA; i < XBoxPadInput::XInputKeyMax; i++)
	{
		if ((*m_MapPadState.find(_PlayerIndex)).second[i] == DOWN)
			return (*m_MapPadState.find(_PlayerIndex)).second[i];
	}
	return 0;
}

unsigned char CPlayerInput::IsXBoxPadUpDown(int _PlayerIndex)
{
	for (int i = XBoxPadInput::ButtonA; i < XBoxPadInput::XInputKeyMax; i++)
	{
		if ((*m_MapPadState.find(_PlayerIndex)).second[i] == UP)
			return (*m_MapPadState.find(_PlayerIndex)).second[i];
	}
	return 0;
}

void CPlayerInput::SetXBoxPadVibration(int _PlayerIndex, WORD _LeftMotorSpeed /*= 32000*/, WORD _RightMotorSpeed /*= 32000*/)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = _LeftMotorSpeed; // use any value between 0-65535 here
	vibration.wRightMotorSpeed = _RightMotorSpeed; // use any value between 0-65535 here
	XInputSetState(_PlayerIndex, &vibration);
}

void CPlayerInput::StopXBoxPadVibration(int _PlayerIndex)
{
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wLeftMotorSpeed = 0; // use any value between 0-65535 here
	vibration.wRightMotorSpeed = 0; // use any value between 0-65535 here
	XInputSetState(_PlayerIndex, &vibration);
}
