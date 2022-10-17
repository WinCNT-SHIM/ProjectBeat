#pragma once
#include "GameObject.h"
class testPlayer :
    public GameObject
{
public:
    testPlayer(Vector2D _pos, float _Radius, unsigned char up, unsigned char down, unsigned char left, unsigned char right, unsigned char punch, unsigned char kick);
    virtual ~testPlayer();





};

