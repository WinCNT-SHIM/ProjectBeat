#pragma once
class CharacterSpriteObject :
	public GameObject
{
public:
	CharacterSpriteObject();
	virtual ~CharacterSpriteObject();
public:
	SpriteRenderer* sr;

};

class Character : public GameObject
{
public:
	Character(
		string _teg, 
		unsigned char up, unsigned char down, unsigned char left, unsigned char right,
		unsigned char punch, unsigned char kick, unsigned int characterType);
	virtual ~Character();

public:
	virtual void Update() override;
public:
	virtual void Start(GameObject* target, int index);
	
	void Setting(int idx);

};