#pragma once

class Pause : public Component
{
public:
	Pause(GameObject* _GameObject);
	virtual ~Pause();

private:
	SpriteRenderer* m_Renderer;
	float m_DeltaTime;
public:
	virtual void Start();
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ���ֱ�.
	virtual void SetName() { m_Name = "Pause"; }
};

