#pragma once
class ParticleComponet : public Component
{
public:
	ParticleComponet(GameObject* _GameObject);
	virtual ~ParticleComponet();

public:
	virtual void Start();
	virtual void Update(); // 모든 Object Udpate돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 업데이트 해줌.
	virtual void Render(D2DEngine* _pEngine); // 모든 Object 렌더 돌릴 때 (ObjectManager) 오브젝트가 Components를 가지고 있으면 같이 렌더

	virtual void SetName() { m_Name = "ParticleComponet"; }
};

