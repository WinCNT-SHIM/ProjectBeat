#include "GamePCH.h"
#include "Metronome.h"

Metronome::Metronome(GameObject* _GameObject) : Component(_GameObject)
{
}

Metronome::~Metronome()
{
}

void Metronome::Start()
{
	// �ִϸ��̼� Ŭ��
	SpriteAnimationClip* _SpriteAniClip = new SpriteAnimationClip("METRO", 8);
	_SpriteAniClip->AddSprite("0023_InGameSceneUI", "METRO1");
	_SpriteAniClip->AddSprite("0023_InGameSceneUI", "METRO2");
	_SpriteAniClip->AddSprite("0023_InGameSceneUI", "METRO3");
	_SpriteAniClip->AddSprite("0023_InGameSceneUI", "METRO4");

	//�ִϸ����� Ŭ�� �߰�.
	m_SpriteAnimator = m_GameObject->AddComponent<SpriteAnimator>();
	m_SpriteAnimator->AddAnimationClip(_SpriteAniClip->AniClipName, _SpriteAniClip);
	m_SpriteAnimator->SetLoopPlay(true);
	m_GameObject->SetLayer(100);// m_Layer = 2;

}

void Metronome::Update()
{
}

void Metronome::Stop()
{
	m_SpriteAnimator->StopAnimation();
}

void Metronome::Play()
{
	m_SpriteAnimator->Play();
}


