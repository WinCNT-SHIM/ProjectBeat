#include "GamePCH.h"
#include "IScene.h"

IScene::IScene()
{
	m_ObjManager = new ObjectManager();
}

IScene::~IScene()
{
	delete m_ObjManager;
}

ObjectManager* IScene::GetObjManager()
{
	return m_ObjManager;

}
