#pragma once

class BeatBurstComponent;

class BeatBurstScene : public IScene
{
public:
	BeatBurstScene();
	~BeatBurstScene();

private:
	BeatBurstComponent* m_BeatBurst;
public:
	virtual void Start();
	virtual void Update();
	virtual void Render(D2DEngine* m_Engine);
	void init(Character* _Caster, Character* victim, bool _isPlayer1First, int _Index,int _PlayerChar1Index, int _PlayerChar2Index, int _BeatCount = 7);


};

