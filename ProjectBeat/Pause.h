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
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해주기.
	virtual void SetName() { m_Name = "Pause"; }
};

