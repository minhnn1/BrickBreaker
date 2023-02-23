#include "pch.h"
#include "Paddle.h"
#include "Barrier.h"
using namespace sf;
using namespace std;

void Paddle::initVariable()
{
	this->velocity = 0.f;
	this->acceleration = 0.2f;
	this->maxSpeed = 7.f;
}

void Paddle::initShape()
{
	this->shape.setFillColor(Color::Red);
	this->shape.setSize(Vector2f(100.f, 10.f));
}

void Paddle::initPos(RenderTarget *target)
{
	//Set Paddle origin at the middle of the paddle
	FloatRect paddleBounds = this->shape.getGlobalBounds();
	this->shape.setOrigin(paddleBounds.width / 2, -paddleBounds.height/2);

	Vector2u winSize = target->getSize();
	this->shape.setPosition((float)winSize.x / 2, (float)winSize.y * 3 / 4);
}

//Constructors & Destructors
Paddle::Paddle(sf::RenderTarget *target)
{
	this->initVariable();
	this->initShape();
	this->initPos(target);
}

Paddle::~Paddle()
{

}

//Accessors
RectangleShape Paddle::getShape()
{
	return this->shape;
}

float Paddle::getSpeed()
{
	return this->velocity;
}

int Paddle::checkCollision(sf::FloatRect objBounds)
{
	if (this->shape.getGlobalBounds().intersects(objBounds))
		return -1;
	return 0;
}

//Functions
void Paddle::updateCollision(int flag)
{
	if (flag)
		this->shape.move(-this->velocity, 0.f);	
}

void Paddle::updateMovement()
{
	//Keyboard input
	//Left
	if (Keyboard::isKeyPressed(Keyboard::Left))
		this->velocity = -linear_interpolation(-velocity, this->maxSpeed, this->acceleration);
	//Right
	else if (Keyboard::isKeyPressed(Keyboard::Right))
		this->velocity = linear_interpolation(velocity, this->maxSpeed, this->acceleration);
	else
		this->velocity = 0.f;
	this->shape.move(this->velocity, 0.f);
}

//Functions
void Paddle::update(Barrier *barriers)
{
	this->updateMovement();
	this->updateCollision(barriers->checkCollision(this->shape.getGlobalBounds()));
}

void Paddle::render(RenderTarget *target)
{
	target->draw(this->shape);
}
