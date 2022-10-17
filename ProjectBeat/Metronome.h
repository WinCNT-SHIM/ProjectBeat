#pragma once
class Metronome : public Component
{
public:
	Metronome(GameObject* _GameObject);
	virtual ~Metronome();

private:
	SpriteAnimator* m_SpriteAnimator;
public:
	virtual void Start();
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void SetName() { m_Name = "Metronome"; };


	void Stop();
	void Play();
};

