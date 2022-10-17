#pragma once
class ParticleComponet : public Component
{
public:
	ParticleComponet(GameObject* _GameObject);
	virtual ~ParticleComponet();

public:
	virtual void Start();
	virtual void Update(); // ��� Object Udpate���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ������Ʈ ����.
	virtual void Render(D2DEngine* _pEngine); // ��� Object ���� ���� �� (ObjectManager) ������Ʈ�� Components�� ������ ������ ���� ����

	virtual void SetName() { m_Name = "ParticleComponet"; }
};

