#include "GamePCH.h"
#include "BeatBurstScene.h"
#include "BeatBurstComponent.h"
BeatBurstScene::BeatBurstScene()
{
}

BeatBurstScene::~BeatBurstScene()
{
}

void BeatBurstScene::Start()
{
	GameObject* _Main = new GameObject();
	m_BeatBurst = _Main->AddComponent<BeatBurstComponent>();
	GetObjManager()->InsertObject(_Main);
}

void BeatBurstScene::Update()
{
	GetObjManager()->Update();

}

void BeatBurstScene::Render(D2DEngine* m_Engine)
{
	if (!GameProcess::m_pSceneManager->m_SceneStack.empty())
		GameProcess::m_pSceneManager->m_SceneStack.top()->GetObjManager()->Render(m_Engine);
	GetObjManager()->Render(m_Engine);
}

void BeatBurstScene::init(Character* _Caster, Character* victim, bool _isPlayer1First, int _Index, int _PlayerChar1Index, int _PlayerChar2Index, int _BeatCount)
{
	m_BeatBurst->Init(_Caster, victim, _isPlayer1First, _Index, _PlayerChar1Index, _PlayerChar2Index, _BeatCount);
}



