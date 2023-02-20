#include "pch.h"
#include "Ball.h"

using namespace sf;
using namespace std;

//Private functions
void Ball::initVariable()
{
	this->velocity = Vector2f(0.f, 0.f);
}

void Ball::initShape()
{
	this->shape.setRadius(5.f);
	this->shape.setFillColor(Color::White);
	this->shape.setOutlineThickness(1);
}

void Ball::initPos(float x, float y)
{
	float radius = this->shape.getRadius();
	this->shape.setOrigin(radius, radius);
	this->shape.setPosition(x, y);
}

//Constructors & Destructors
Ball::Ball(float x, float y)
{
	this->initVariable();
	this->initShape();
	this->initPos(x, y);
}

Ball::~Ball()
{

}
//Functions
const CircleShape Ball::getShape() const
{
	return this->shape;
}

void Ball::updateAttached(sf::Vector2f paddlePos)
{
	this->shape.setPosition(paddlePos);
}

void Ball::updateDetached(float x)
{
	this->shape.move(0, -6.f);
	this->velocity = Vector2f(x, -5.f);	
}

void Ball::updateWindowBoundsCollision(const RenderTarget* target)
{
	//Get ball's bounding box
	FloatRect ballBounds = this->shape.getGlobalBounds();
	
	//Ball hits left or right barrier
	if (ballBounds.left <= 0.f || ballBounds.left + ballBounds.width >= target->getSize().x)
	{
		this->velocity.x = -this->velocity.x;
	}

	//Ball hits top/ceiling barrier
	if (ballBounds.top <= 0.f)
	{
		this->velocity.y = -this->velocity.y;
	}
}

void Ball::updateCollision()
{
	this->velocity.y = -this->velocity.y;
}

void Ball::update(const RenderTarget* target)
{
	//Ball movements
	this->shape.move(this->velocity);

	//Window bounds collision. Check after movements to stop from going out of bounds.
	this->updateWindowBoundsCollision(target);
}

void Ball::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}