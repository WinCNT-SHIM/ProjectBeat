#include "stdafx.h"
#include "CTime.h"

UINT32 CTime::m_FPS = 0;
float CTime::m_DeltaTime = 0;
CTime::CTime() :
	m_Frequency(NULL),
	m_PrevCount(NULL),
	m_FrameCount(NULL),
	m_FrameTime(NULL)
{

}

CTime::~CTime()
{
	// ���� �Ұ� ����.
}

void CTime::Initialize()
{
	//���� �ð��� ����
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_Frequency));
	//�ð� ������ ī��Ʈ
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_PrevCount));
}

void CTime::Update()
{
	UINT64 _currentCount;

	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&_currentCount));

	// ���� _currentCount���� �� m_PrevCount�� �� ����
	// m_Frequency�� �������ָ� ����� �ð�(��)�� ���´�.
	m_DeltaTime = (_currentCount - m_PrevCount) / static_cast<float>(m_Frequency);
	m_PrevCount = _currentCount; // preCount�� currentCount�� ����

	m_FrameCount++;				// Update���� 1�ʿ� �� �� ����Ǵ��� üũ�ϱ� ���ؼ� ���� !
	m_FrameTime += m_DeltaTime; // 1 �����ӿ� ��� �� �ʰ� �ɸ����� üũ�ϱ� ���ؼ� ���� !

	if (m_FrameTime > 1.f)		// 1�ʸ� �Ѿ�� ���� (�츰 �ʴ� �� ���� ������Ʈ == �������� ����Ǿ����� �ñ��ϴϱ� ..)
	{
		m_FPS = static_cast<UINT32>(m_FrameCount / m_FrameTime);  // 1�� �� Update���� �� �� ����Ǿ����� ���

		m_FrameTime = 0.f;		// 0���� �ʱ�ȭ
		m_FrameCount = 0;		// 0���� �ʱ�ȭ
	}
}

int CTime::GetFPS()
{
	return m_FPS;
}