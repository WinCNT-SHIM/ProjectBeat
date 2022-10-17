#pragma once
class OutroIcon : public Component
{
public:
	OutroIcon(GameObject* _GameObject);
	virtual ~OutroIcon();
private:
	SpriteRenderer* m_Renderer = nullptr;
	float m_isPlay = false;
	float m_Timer = 0;
	float m_Size = 1.0f;
	int m_PlayerIndex = 1;
	string m_SpriteName;
public:
	//1 or 2
	void Play(int _PlayerIndex);
public:
	virtual void Start();
	virtual void Update();
	virtual void SetName();
};

