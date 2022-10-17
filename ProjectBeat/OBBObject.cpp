#include "GamePCH.h"
#include "OBBObject.h"



OBBObject::OBBObject(Vector2D _pos, Vector2D _rt, Vector2D _Gradient, Vector2D _Scale, Vector2D _Pivot) :GameObject(_pos, _Gradient, _Scale, _Pivot)
{
	OBBCollider* instance = AddComponent<OBBCollider>();
	collider = instance;
	instance->Init(-_rt.x, -_rt.y, _rt.x, _rt.y);

	m_tr->SetLocalRotateVector(m_tr->GetLocalRotate().Nomalize());

	m_Pyhsics = AddComponent<Physics>();
	m_Pyhsics->init(ColliderType::OBB);
	AddComponent<RectRender>()->Init(-_rt.x, -_rt.y, _rt.x, _rt.y);


	//CircleObject* PivotObject = new CircleObject(_Pivot, 5);
	//PivotObject->SetParent(this);
	//GameProcess::m_pSceneManager->GetScene()->GetObjManager()->InsertObject(PivotObject);
}

OBBObject::~OBBObject()
{

}

