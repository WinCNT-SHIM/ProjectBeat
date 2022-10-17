#include "stdafx.h"
#include "SpriteAnimator.h"
#include "SpriteAnimationClip.h"

SpriteAnimator::SpriteAnimator(GameObject* _GameObject) :
	Component(_GameObject)
{
	Init();
}

SpriteAnimator::~SpriteAnimator()
{
	if (!m_AniClipCollection.empty())
	{
		for (auto iter : m_AniClipCollection)
		{
			delete iter.second;
		}
		m_AniClipCollection.clear();

	}
}

void SpriteAnimator::Init()
{
	m_tr = m_GameObject->m_tr;
	m_curAniClip = nullptr;
	m_SpriteIndex = 0;
	m_SpriteMaxCnt = 0;
	m_CurFPS = 0;
	m_PlayFPS = 0;
	m_isPlaying = true;
	m_isLoop = false;
	m_Fill = { 1, 1 };
	m_Ratio = 1.f;
	m_drawMode = FillMode::Simple;
}

void SpriteAnimator::Update()
{
	// 현재 재생 프레임이 애니메이션 클립 교체 프레임을 넘었을 경우
	if (m_isPlaying)
	{
		if (m_CurFPS > m_PlayFPS)
		{
			m_CurFPS = 0;
			m_SpriteIndex++;
			// 애니메이션 클립의 최대 개수를 넘을 경우
			if (m_SpriteIndex >= m_SpriteMaxCnt)
			{
				if (m_isLoop == true) m_SpriteIndex = 0;
				else StopAnimation();
			}
		}
		m_CurFPS++;
	}
}

void SpriteAnimator::Render(D2DEngine* _pEngine)
{
    if (!m_isPlaying) return;

    switch (m_drawMode)
	{
		case FillMode::Simple:
        {
            m_curAniClip->DrawAniSnap(_pEngine, m_tr, m_SpriteIndex, m_Ratio);
		}
		break;
		case FillMode::Fill:
        {
            m_curAniClip->DrawAniSnap(_pEngine, m_tr, m_SpriteIndex, m_Ratio, m_Fill);
		}
		break;
		default:
        {
            m_curAniClip->DrawAniSnap(_pEngine, m_tr, m_SpriteIndex, m_Ratio);
		}
		break;
	}
}

void SpriteAnimator::AddAnimationClip(string _AniClipName, SpriteAnimationClip* _AniClip)
{
	m_AniClipCollection.insert({ _AniClipName, _AniClip });
	SetAnimationClip(_AniClipName);
}

void SpriteAnimator::SetAnimationClip(string _AniClipName)
{
	if (m_AniClipCollection.find(_AniClipName) != m_AniClipCollection.end())
	{
		// 재생되는 애니메이션 클립을 설정
		m_curAniClip = m_AniClipCollection[_AniClipName];
		// 애니메이션 클립의 스프라이트의 인덱스를 초기화
		m_SpriteIndex = 0;
		// 애니메이션 클립의 스프라이트의 인덱스를 재획득
		m_SpriteMaxCnt = m_curAniClip->GetSpriteMaxCnt();
		// 설정된 애니메이션 클립이 몇 프레임 단위로 재생되는지 획득
		m_PlayFPS = m_curAniClip->GetPlayFPS();
		// 현재 재생 프레임을 초기화
		m_CurFPS = 0;
	}
}

void SpriteAnimator::StopAnimation()
{
	m_SpriteIndex = 0;
	m_isPlaying = false;
}

void SpriteAnimator::SetLoopPlay(bool _isLoop)
{
	m_isLoop = _isLoop;
}

void SpriteAnimator::SetFill(float _FillX, float _FillY)
{
    // Fill의 값이 0~1이 되도록 조정
    if (_FillX < 0) _FillX = 0;
    if (_FillX > 1) _FillX = 1;
    if (_FillY < 0) _FillY = 0;
    if (_FillY > 1) _FillY = 1;

    m_Fill = Vector2D(_FillX, _FillY);
}
void SpriteAnimator::Play()
{
	m_isPlaying = true;
}

