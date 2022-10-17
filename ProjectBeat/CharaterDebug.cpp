#include "GamePCH.h"
#include "CharaterDebug.h"
#include "../Engine/Animator.h"
#include "../Engine/TextComponent.h"

#include "CommandComponent.h"
#include "StateComponent.h"
#include "CharactorInfoComponent.h"
static const char* StateString[] =
{
	"STATE_IDLE",
	"STATE_MOVEFW",
	"STATE_MOVEBK",
	"STATE_JUMP",
	"STATE_ATTACK",
	"STATE_GUARD",
	"STATE_HIT",
	"STATE_DEATH"
};

CharaterDebug::CharaterDebug(GameObject* gameobject) :
	Component(gameobject)
{
}

CharaterDebug::~CharaterDebug()
{
}

void CharaterDebug::Init(GameObject* charaterObject)
{
	_charater = charaterObject;
	_animator = _charater->GetComponent<Animator>();
	_textComponent = GetComponent<TextComponent>();

	_textComponent->_horizontalAlignment = HorizontalAlignment::Left;
	_textComponent->_verticalAlignment = VerticalAlignment::Center;

	_charInfo = _charater->GetComponent<StateComponent>();
	_cmdComponent = _charater->GetComponent<CommandComponent>();
	_CharactorInfoComponent = _charater->GetComponent<CharactorInfoComponent>();
}

void CharaterDebug::Update()
{

	if (GetDebugMod())
		_textComponent->SetActive(true);
	else
		_textComponent->SetActive(false);
	_debugInfo = "";

	std::string animatorTime = std::to_string(_animator->_currTimer);
	std::string currClip = _animator->_animatorController->_currAnimationNode->_animationClipName;
	std::string currState = StateString[_charInfo->GetState()];
	std::string firstAtk = std::to_string(_cmdComponent->getFirstHit());
	std::string ComboCnt = std::to_string(_cmdComponent->getCanInput());
	std::string Hp = std::to_string((int)_CharactorInfoComponent->getHp());
	std::string MaxHp = std::to_string((int)_CharactorInfoComponent->getMaxHp());
	std::string commandque = std::to_string((unsigned int)_cmdComponent->CommandCount);

	_debugInfo += "HP : " + Hp + "/";
	_debugInfo += MaxHp + '\n';
	_debugInfo += "AnimatorTimer : " + animatorTime + '\n';
	_debugInfo += "currClip : " + currClip + '\n';
	_debugInfo += "AtkInput : " + firstAtk + '\n';
	_debugInfo += "CanInput : " + ComboCnt + '\n';
	_debugInfo += "CurrState : " + currState + '\n';
	_debugInfo += "cmdQue : " + commandque;


	_textComponent->_text = _debugInfo;
}
