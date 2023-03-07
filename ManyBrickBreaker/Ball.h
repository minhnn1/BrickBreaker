#pragma once
#include "pch.h"
#include "Barrier.h"
#include "Paddle.h"
#include "Brick.h"

class Ball : public PhysicEngine
{
private:
	//Variables
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f maxSpeed;
	int state;
	/*	state of the ball:
		-1 if the ball is going to be removed
		0 if the ball is detached 
		1 if the ball is attached
		2 if the ball has collided 
	*/

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
	void updateCollision(sf::Vector2f vel, int flag);
	void updateBarriersCollision(Barrier *barriers);
	void updatePaddleCollision(Paddle *paddles);
	void updateBricksCollision(std::vector<std::vector<Brick *>> bricks);

	void update(sf::RenderTarget *target, Paddle *paddle, Barrier *barriers, std::vector<std::vector<Brick *>> bricks);
	void render(sf::RenderTarget *target);
};

