#pragma once
#include <Windows.h>

class CTime
{
public:
	CTime();
	virtual ~CTime();

private:

	//�ð��� ����?
	UINT64 m_Frequency;

	//���ݵ��� ī��Ʈ Ƚ��
	UINT64 m_PrevCount;

	// ���� �����ӿ��� ���� �����ӱ��� ����� �ð�
	static float m_DeltaTime;

	// �ʴ� �� ���� ������Ʈ�� �̷�������� üũ�ϱ� ���� ����
	UINT32 m_FrameCount;
	float m_FrameTime;

	// ��� �ʴ� ������ ��
	static UINT32 m_FPS;

public:


	void Initialize();
	
	void Update();

	static int GetFPS();

	static float GetDeltaTime() { return m_DeltaTime; }
};

