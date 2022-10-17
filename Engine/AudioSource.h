#pragma once

#include "Component.h"
class AudioClip;

/// <summary>
/// ����� ������Ʈ
/// 
/// �� ���� ����� Ŭ���� ������.
/// ������Ʈ �ý����� ������.
/// 
/// 2022.02.19 LeHideHome
/// </summary>
class AudioSource : public Component
{
public:
	AudioSource(GameObject* pGameObject);
	virtual ~AudioSource();


public:
	// �÷���
	void Play(bool isLoop = false);

	// ����
	void Stop();
	//void Pause();		// �Ͻ������� �簳�� �ʿ伺�� ������ ���� ����
	//void Resume();

private:
	// ����� ����
	AudioClip* m_pAudioClip;

	// �Ʒ��� �Ӽ�
	bool m_IsLoop;		// �ݺ�����
	bool m_IsMute;		// ����
	// ��ġ
	// ����
	// 3D/2D
	// ������
	// ����
	// ...
};

