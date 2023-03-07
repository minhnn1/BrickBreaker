#pragma once
#include "pch.h"

class PhysicEngine
{
public:

	float linear_interpolation(float x, float y, float z);
	float signnum(float x);

	sf::Vector2f normalize(sf::Vector2f v);
	float dot(sf::Vector2f v1, sf::Vector2f v2);
	sf::Vector2f multiply(sf::Vector2f v, float f);

	bool CirToCirCollision(sf::CircleShape obj1, sf::CircleShape obj2);
	sf::Vector2f CirToCirCollisionHandle(sf::CircleShape obj1, sf::Vector2f vel1, sf::CircleShape obj2, sf::Vector2f vel2);

};
