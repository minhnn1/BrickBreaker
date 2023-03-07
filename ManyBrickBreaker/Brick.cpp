#include "pch.h"
#include "Brick.h"
using namespace sf;


//Private functions
void Brick::initVariable(int state)
{
	this->state = state;
}

void Brick::initShape()
{
	this->shape.setFillColor(Color::Magenta);
	this->shape.setSize(Vector2f(58.f, 23.f));
	this->shape.setOutlineColor(Color::Black);
	this->shape.setOutlineThickness(2.f);
}

void Brick::initPos(Vector2f pos)
{
	this->shape.setOrigin(-20.f, -30.f);
	this->shape.setPosition(pos);
}

//Constructors & Destructors
Brick::Brick(Vector2f pos, int state)
{
	this->initVariable(state);
	this->initShape();
	this->initPos(pos);
}

Brick::~Brick()
{
	
}

//Accessors
int Brick::getState()
{
	return this->state;
}

//Functions
int Brick::checkCollision(sf::CircleShape ball, int ballState)
{
	FloatRect ballBounds = ball.getGlobalBounds();
	Vector2f ballCent = ball.getPosition();
	float ballRad = ball.getRadius();

	FloatRect brickBounds = this->shape.getGlobalBounds();
	
	//Check if the ball's and brick's bounding box overlapps
	if (brickBounds.intersects(ballBounds))
	{
		//If the ball hit the top/bottom of the brick (vertical collision)
		if (brickBounds.contains(ballCent.x, ballBounds.top) || brickBounds.contains(ballCent.x, ballBounds.top + ballBounds.height))
		{
			//Check if the ball has already coliided with another brick
			if (ballState == 1) 
				//Marks the brick to remove it later
				this->state--; 
			return -1;
		}

		//If the ball hit the left/right side of the brick (horizontal collision)
		else if (brickBounds.contains(ballBounds.left, ballCent.y) || brickBounds.contains(ballBounds.left + ballBounds.width, ballCent.y))
		{
			if (ballState == 1)
				this->state--;
			return 1;
		}

		//Edge collision
		//Top left edge
		else if (pow(ballCent.x - brickBounds.left, 2) + pow(ballCent.y - brickBounds.top, 2) < pow(ballRad, 2))
		{
			if (ballState == 1)
				this->state--;
			return 2;
		}

		//Top right edge
		else if (pow(ballCent.x - (brickBounds.left + brickBounds.width), 2) + pow(ballCent.y - brickBounds.top, 2) < pow(ballRad, 2))
		{
			if (ballState == 1)
				this->state--;
			return 2;
		}

		//Botom left edge
		else if (pow(ballCent.x - brickBounds.left, 2) + pow(ballCent.y - (brickBounds.top + brickBounds.height), 2) < pow(ballRad, 2))
		{
			if (ballState == 1)
				this->state--;
			return 2;
		}

		//Bottom right edge
		else if (pow(ballCent.x - (brickBounds.left + brickBounds.width), 2) + pow(ballCent.y - (brickBounds.top + brickBounds.height), 2) < pow(ballRad, 2))
		{
			if (ballState == 1)
				this->state--;
			return 2;
		}
	}

	//No collision
	return 0;
}

void Brick::update()
{
	if (this->state == 1)
		this->shape.setFillColor(Color::Blue);
	else if (this->state == 2)
		this->shape.setFillColor(Color::Red);
}

void Brick::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
