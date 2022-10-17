#pragma once

class SpriteRenderer;

class Effect : public Component
{
public:
	Effect(GameObject* _GameObject);
	virtual ~Effect();

protected:
	SpriteRenderer* m_Renderer;
	bool m_isPlay = false;
	bool m_isPlayer1;
	int	m_CharIndex;
	float m_Size;
	float m_Alpha;
	float m_Timer;
	float m_EndTimer;
	float m_Damage;

public:
	virtual void Play(bool _isPlayer1, int _CharIndex, float Damage = 0) abstract;
	virtual void Play(bool _isPlayer1, int _CharIndex, string _SpriteName) {};
	void SetisPlay(bool _isbool) { m_isPlay = _isbool; }
	bool GetisPlay() { return m_isPlay; }
};

