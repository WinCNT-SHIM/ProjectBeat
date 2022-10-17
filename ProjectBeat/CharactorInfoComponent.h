#pragma once
#include "..\Engine\Component.h"
#include "StateComponent.h"
class Character;
class Animator;

class CharactorInfoComponent :
	public Component
{

public:
	CharactorInfoComponent(GameObject* _GameObject);
	virtual ~CharactorInfoComponent();
	virtual void SetName() { m_Name = "CharactorInfoComponent"; }
private:
	float Hp;
	float MaxHp;
	float Guage;
	float MaxGuage;
	float speed;
	bool CanDmg = false;

	bool m_isOnSpecial = false;
	bool m_isLowHpSound = false;

	string CharacterName;
	GameObject* target;
	StateComponent* CState;

	// 게임 패드 진동 조절을 위한 타이머
	float m_DeltaTime = 0;

public:

	int CharIndex = 0; //이걸로 무슨캐릭터 확인인지하고 
	int playerIndex = 0;
	bool StrongHit = false;



	void setTarget(GameObject* object) { target = object; }

	GameObject* getTarget() { return target; }


	void ApplyDmgtoTarget(float dmg);

	bool DamageAble() { return (CanDmg == true && CState->GetState() != 5); }
	void SetDamageAble(bool on);

	virtual void Update();

	void Init(int charIdx);

	float getHp() { return Hp; }
	float getMaxHp() { return MaxHp; }
	void setHp(float num) { Hp = num; }

	float getGuage() { return Guage; }
	float getMaxGuage() { return MaxGuage; }
	void setGuage(float num) { Guage = num; }

	float getSpeed() { return speed; }
	void setSpeed(float num) { speed = num; }

	void playHitSound();

	string GetCharacterName() const { return CharacterName; }
	void SetCharacterName(std::string val) { CharacterName = val; }

	void SetSpecial(bool _isOn);
	bool GetSpecial() { return  m_isOnSpecial; }

	void SetisLowHpSound(bool _isSound) { m_isLowHpSound = _isSound; }

	void PlayLowHpSound();
	
};

