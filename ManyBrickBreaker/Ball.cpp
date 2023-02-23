#include "pch.h"
#include "Ball.h"
using namespace sf;
using namespace std;

//Private functions
void Ball::initVariables(int state)
{
	this->velocity = Vector2f(0.f, 0.f);
	this->state = state;
}

void Ball::initShape()
{
	this->shape.setFillColor(Color::White);
	this->shape.setRadius(5.f);
	this->shape.setOutlineThickness(1);
}

void Ball::initPos(Vector2f paddlePos)
{
	float radius = this->shape.getRadius();
	this->shape.setOrigin(radius, radius);
	this->shape.setPosition(paddlePos);
}

//Constructors & Destructors
Ball::Ball(RectangleShape paddle, int state)
{
	this->initVariables(state);
	this->initShape();
	this->initPos(paddle.getPosition());
}

Ball::~Ball()
{

}

//Accessors
int Ball::getState()
{
	return this->state;
}

//Functions
void Ball::launch(float xvel)
{
	if (this->state == 1)
	{
		this->state = 0;
		this->velocity = Vector2f(xvel, -5.f);
	}	
}

void Ball::updateAttached(RectangleShape paddle)
{
	this->shape.setPosition(paddle.getPosition());
}

void Ball::updateDetached()
{
	this->shape.move(this->velocity);
}

void Ball::updateCollision(int flag)
{
	if (flag == 1)
		this->velocity.x = -this->velocity.x;
	else if (flag == -1)
		this->velocity.y = -this->velocity.y;
}

void Ball::update(sf::RenderTarget *target, Paddle *paddle, Barrier *barriers)
{
	if (this->state == 1)
		this->updateAttached(paddle->getShape());
	else 
	{
		this->updateDetached();
		this->updateCollision(barriers->checkCollision(this->shape.getGlobalBounds()));
		this->updateCollision(paddle->checkCollision(this->shape.getGlobalBounds()));
	}

	if (this->shape.getPosition().y > target->getSize().y)
		this->state = -1;
}

void Ball::render(RenderTarget *target)
{
	target->draw(this->shape);
}
