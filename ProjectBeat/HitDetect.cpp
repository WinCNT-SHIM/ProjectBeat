#include "GamePCH.h"
#include "HitDetect.h"
#include "CommandComponent.h"
HitDetect::HitDetect(GameObject* _GameObject)
	:Component(_GameObject)
{

}

void HitDetect::OnEnterCollider(GameObject* Other)
{

	CObject = m_GameObject->GetTopParent();
	T_Cinfo = CObject->GetComponent<CharactorInfoComponent>()->getTarget()->GetComponent<CharactorInfoComponent>();
	Cinfo = CObject->GetComponent<CharactorInfoComponent>();



	if (Other->GetTopParent() != nullptr)
	{
		if (CObject->GetComponent<StateComponent>()->GetState() == 4)
		{
			if (m_GameObject->GetName() == "LeftHand" || m_GameObject->GetName() == "RightHand" 
				|| m_GameObject->GetName() == "LeftTiptoe" || m_GameObject->GetName() == "RightTiptoe"
				|| m_GameObject->GetName() == "LeftFoot" || m_GameObject->GetName() == "RightFoot")
			{
				if (Cinfo->StrongHit == true)
				{
					CObject->GetComponent<CharactorInfoComponent>()->ApplyDmgtoTarget(3);
				}
				else
				{
					CObject->GetComponent<CharactorInfoComponent>()->ApplyDmgtoTarget(1);
				}

			}
		}
	}


}

void HitDetect::OnExitCollider(GameObject* Other)
{

}

void HitDetect::OnStayCollider(GameObject* Other)
{
	

}

void HitDetect::DetectHitPart(GameObject* Other)
{

}
