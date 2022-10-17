#include "GamePCH.h"
#include "TestHumanCtrl.h"
#include "DeBugPrint.h"
#include "../Engine/Animator.h"
#include "../Engine/SpriteRenderer.h"

TestHumanCtrl::TestHumanCtrl(GameObject* _GameObject)
:Component(_GameObject)
{
}

TestHumanCtrl::~TestHumanCtrl()
{
}

void TestHumanCtrl::Init()
{
	_animator = GetComponent<Animator>();
	_sr = m_GameObject->GetComponent<SpriteRenderer>();

}

void TestHumanCtrl::TestFunc()
{

}

void TestHumanCtrl::TestFunc2()
{
	int a = 0;
}

void TestHumanCtrl::Update()
{
	/*if (KEYBORAD->KeyPress(VK_RIGHT))
	{
		_animator->SetBool("Run", true);
		_animator->SetBool("Back", false);
	}
	else if (KEYBORAD->KeyPress(VK_LEFT))
	{
		_animator->SetBool("Run", false);
		_animator->SetBool("Back", true);
	}
	else if (KEYBORAD->GetDownKey() == VK_DOWN)
	{
		_animator->SetSpeed(_animator->GetSpeed() + 0.1f);
	}
	else if (KEYBORAD->GetDownKey() == VK_UP)
	{
		_animator->SetSpeed(_animator->GetSpeed() - 0.1f);
	}
	else
	{
		_animator->SetBool("Run", false);
		_animator->SetBool("Back", false);
	}*/
}
