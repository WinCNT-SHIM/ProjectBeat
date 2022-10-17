#pragma once

#include "Component.h"
class AudioClip;

/// <summary>
/// 오디오 컴포넌트
/// 
/// 한 개의 오디오 클립을 가진다.
/// 컴포넌트 시스템을 따른다.
/// 
/// 2022.02.19 LeHideHome
/// </summary>
class AudioSource : public Component
{
public:
	AudioSource(GameObject* pGameObject);
	virtual ~AudioSource();


public:
	// 플레이
	void Play(bool isLoop = false);

	// 정지
	void Stop();
	//void Pause();		// 일시정지와 재개는 필요성이 있으면 만들 예정
	//void Resume();

private:
	// 오디오 파일
	AudioClip* m_pAudioClip;

	// 아래는 속성
	bool m_IsLoop;		// 반복여부
	bool m_IsMute;		// 무음
	// 피치
	// 볼륨
	// 3D/2D
	// 리버브
	// 에코
	// ...
};

