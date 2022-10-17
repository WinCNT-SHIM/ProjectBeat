#include "GamePCH.h"
#include "OpeningScene.h"
#include "Opening.h"

OpeningScene::OpeningScene()
{
}

OpeningScene::~OpeningScene()
{
}

void OpeningScene::Start()
{
	GameObject* _Main = new GameObject();
	_Main->AddComponent<Opening>();
	GetObjManager()->InsertObject(_Main);
}

void OpeningScene::Update()
{
	GetObjManager()->Update();
}

void OpeningScene::Render(D2DEngine* m_Engine)
{
	GetObjManager()->Render(m_Engine);
}
