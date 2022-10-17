#pragma once
class OpeningScene : public IScene
{
public:
	OpeningScene();
	~OpeningScene();
private:

public:
	virtual void Start();
	virtual void Update();
	virtual void Render(D2DEngine* m_Engine);
};

