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
	//���� ���ص� ��.
	ParticleManager();
	~ParticleManager();
private:

	static Effect* m_Effect[5];
	static Effect* m_HitEffect[5];
	static Effect* m_MotionEffect[5];

public:
	//�ʱ�ȭ �� �ٷ� ���.
	static void Init();
	static void Play(bool _isPlayer1, int _CharIndex,Vector2D _pos, Particle _particle, float _Damage = 0,string _SpriteName = "");
};

