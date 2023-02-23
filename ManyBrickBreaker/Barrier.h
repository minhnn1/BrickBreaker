#pragma once
#include "pch.h"

class Barrier
{
private:
	//Variables
	sf::RectangleShape leftBar;
	sf::RectangleShape rightBar;
	sf::RectangleShape topBar;

	//Private functions
	void initShape();
	void initPos();
public:
	//Constructors & Destructors
	Barrier();
	virtual ~Barrier();

	//Functions
	int checkCollision(sf::FloatRect objBounds);

	void update();
	void render(sf::RenderTarget *target);
};

