#pragma once
#include "pch.h"
#include "Barrier.h"
#include "Paddle.h"

class Ball
{
private:
	//Variables
	sf::CircleShape shape;
	sf::Vector2f velocity;
	int state; 
	/*	state of the ball:
		-1 if the ball is going to be removed
		1 if the ball is attached
		0 if the ball is detached */

	//Private functions
	void initVariables(int state);
	void initShape();
	void initPos(sf::Vector2f paddleBounds);

public:
	//Constructors & Destructors
	Ball(sf::RectangleShape paddle, int state);
	virtual ~Ball();

	//Accessors
	int getState();

	//Functions
	void launch(float xvel);
	void updateAttached(sf::RectangleShape paddle);
	void updateDetached();
	void updateCollision(int flag);

	void update(sf::RenderTarget *target, Paddle *paddle, Barrier *barriers);
	void render(sf::RenderTarget *target);
};

