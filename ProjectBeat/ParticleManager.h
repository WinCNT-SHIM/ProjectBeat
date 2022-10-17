#pragma once
class Effect;


enum class Particle
{
	Effect,
	Hit,
	Motion
};
class ParticleManager
{
public:
	//생성 안해도 됨.
	ParticleManager();
	~ParticleManager();
private:

	static Effect* m_Effect[5];
	static Effect* m_HitEffect[5];
	static Effect* m_MotionEffect[5];

public:
	//초기화 후 바로 사용.
	static void Init();
	static void Play(bool _isPlayer1, int _CharIndex,Vector2D _pos, Particle _particle, float _Damage = 0,string _SpriteName = "");
};

