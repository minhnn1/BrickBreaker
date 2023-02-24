#include "pch.h"
#include "Brick.h"
using namespace sf;

void Brick::initVariable()
{
	this->state = 1;
}

//Private functions
void Brick::initShape()
{
	this->shape.setFillColor(Color::Magenta);
	this->shape.setSize(Vector2f(58.f, 23.f));
	this->shape.setOutlineColor(Color::Yellow);
	this->shape.setOutlineThickness(2.f);
}

void Brick::initPos(Vector2f pos)
{
	this->shape.setOrigin(-20.f, -30.f);
	this->shape.setPosition(pos);
}

//Constructors & Destructors
Brick::Brick(Vector2f pos)
{
	this->initVariable();
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
int Brick::checkCollision(sf::CircleShape ball)
{
	FloatRect ballBounds = ball.getGlobalBounds();
	Vector2f ballCent = ball.getPosition();

	FloatRect brickBounds = this->shape.getGlobalBounds();
	
	//Check if the ball's and brick's bounding box overlapps
	if (brickBounds.intersects(ballBounds))
	{
		//If the ball hit the top/bottom of the brick (vertical collision)
		if (brickBounds.contains(ballCent.x, ballBounds.top) || brickBounds.contains(ballCent.x, ballBounds.top + ballBounds.height))
		{
			//Marks the brick to remove it later
			this->state = 0;
			return -1;
		}
		
		//If the ball hit the left/right side of the brick (horizontal collision)
		else if (brickBounds.contains(ballBounds.left, ballCent.y) || brickBounds.contains(ballBounds.left + ballBounds.width, ballCent.y))
		{
			//Marks the bricks to remove it later
			this->state = 0;
			return 1;
		}
	}

	//No collision
	return 0;
}

void Brick::update()
{

}

void Brick::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
