#include "GamePCH.h"
#include "TestScene.h"

TestScene::TestScene() : IScene()
{

}

TestScene::~TestScene()
{

}

void TestScene::Update()
{
	GetObjManager()->Update();
}

void TestScene::Render(D2DEngine* m_Engine)
{
	GetObjManager()->Render(m_Engine);
}
