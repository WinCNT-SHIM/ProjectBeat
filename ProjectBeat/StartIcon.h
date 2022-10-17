#pragma once
class StartIcon : public Component
{
public:
	StartIcon(GameObject* _GameObject);
	virtual ~StartIcon();
private:
	SpriteRenderer* m_Renderer = nullptr;
	float m_isPlay = false;
	float m_Timer = 0;
	float m_Size = 1.0f;
public:
	void Play();
public:
	virtual void Start();
	virtual void Update();
	virtual void SetName();
};

