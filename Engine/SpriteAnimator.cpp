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
	// ���� ��� �������� �ִϸ��̼� Ŭ�� ��ü �������� �Ѿ��� ���
	if (m_isPlaying)
	{
		if (m_CurFPS > m_PlayFPS)
		{
			m_CurFPS = 0;
			m_SpriteIndex++;
			// �ִϸ��̼� Ŭ���� �ִ� ������ ���� ���
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
		// ����Ǵ� �ִϸ��̼� Ŭ���� ����
		m_curAniClip = m_AniClipCollection[_AniClipName];
		// �ִϸ��̼� Ŭ���� ��������Ʈ�� �ε����� �ʱ�ȭ
		m_SpriteIndex = 0;
		// �ִϸ��̼� Ŭ���� ��������Ʈ�� �ε����� ��ȹ��
		m_SpriteMaxCnt = m_curAniClip->GetSpriteMaxCnt();
		// ������ �ִϸ��̼� Ŭ���� �� ������ ������ ����Ǵ��� ȹ��
		m_PlayFPS = m_curAniClip->GetPlayFPS();
		// ���� ��� �������� �ʱ�ȭ
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
    // Fill�� ���� 0~1�� �ǵ��� ����
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

