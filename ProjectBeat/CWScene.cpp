#include "GamePCH.h"
#include "CWScene.h"
#include "testPlayer.h"


CWScene::CWScene() : IScene()
{
	GetObjManager()->InsertObject(new testPlayer(Vector2D(250, 250), 30, 'W', 'S', 'A', 'D', 'J', 'K'));
	GetObjManager()->InsertObject(new testPlayer(Vector2D(600, 600), 30, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, 'N', 'M'));






}

CWScene::~CWScene()
{

}

void CWScene::Update()
{
	GetObjManager()->Update();
}

void CWScene::Render(D2DEngine* m_Engine)
{
	GetObjManager()->Render(m_Engine);
}

