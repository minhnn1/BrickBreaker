#pragma once
#include "pch.h"

class Barrier
{
private:
	//Variables
	sf::RectangleShape leftBar;
	sf::RectangleShape rightBar;
	sf::RectangleShape topBar;
	float size;

	//Private functions
	void initVariables();
	void initShape(sf::RenderTarget *target);
	void initPos(sf::RenderTarget *target);

public:
	//Constructors & Destructors
	Barrier(sf::RenderTarget *target);
	virtual ~Barrier();

	//Functions
	int checkCollision(sf::FloatRect objBounds);

	void update();
	void render(sf::RenderTarget *target);
};

