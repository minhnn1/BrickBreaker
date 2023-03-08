#include "pch.h"
#include "Paddle.h"
#include "Barrier.h"
using namespace sf;
using namespace std;

void Paddle::initVariable()
{
	this->velocity = 0.f;
	this->acceleration = 0.2f;
	this->maxSpeed = 10.f;
}

void Paddle::initShape()
{
	this->shape.setFillColor(Color::Red);
	this->shape.setSize(Vector2f(100.f, 10.f));

	this->leftCir.setFillColor(Color::Blue);
	this->leftCir.setRadius(8.f);

	this->rightCir.setFillColor(Color::Green);
	this->rightCir.setRadius(8.f);
}

void Paddle::initPos(RenderTarget *target)
{
	Vector2u winSize = target->getSize();

	//Set paddle's origin at the middle of the paddle
	FloatRect paddleBounds = this->shape.getGlobalBounds();
	this->shape.setOrigin(paddleBounds.width / 2, -paddleBounds.height/2);
	this->shape.setPosition((float)winSize.x / 2, (float)winSize.y * 5 / 6);

	//Set side circles' origin at the middle of the circle shape
	FloatRect sideBounds = this->leftCir.getGlobalBounds();
	this->leftCir.setOrigin(sideBounds.width / 2, sideBounds.width / 2);
	this->leftCir.setPosition((float)winSize.x / 2 - paddleBounds.width / 2, (float)winSize.y * 5 / 6 + paddleBounds.height);

	this->rightCir.setOrigin(sideBounds.width / 2, sideBounds.width / 2);
	this->rightCir.setPosition((float)winSize.x / 2 + paddleBounds.width / 2, (float)winSize.y * 5 / 6 + paddleBounds.height);

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
CircleShape Paddle::getLeft()
{
	return this->leftCir;
}

CircleShape Paddle::getRight()
{
	return this->rightCir;
}

RectangleShape Paddle::getShape()
{
	return this->shape;
}

float Paddle::getSpeed()
{
	return this->velocity;
}

int Paddle::checkSidesCollision(sf::CircleShape ball)
{
	/*
		Sides collision flag:
		2 if hit left side
		-2 if hit right side
		0 if no collision
	*/
	if (CirToCirCollision(this->leftCir, ball))
		return 2;
	if (CirToCirCollision(this->rightCir, ball))
		return -2;
	return 0;
}

int Paddle::checkMidCollision(sf::CircleShape ball)
{
	if (this->shape.getGlobalBounds().intersects(ball.getGlobalBounds()))
		return -1;
	return 0;
}

//Functions
void Paddle::updateCollision(int flag)
{
	if (flag)
	{
		this->shape.move(-this->velocity, 0.f);
		this->leftCir.move(-this->velocity, 0.f);
		this->rightCir.move(-this->velocity, 0.f);
	}
		
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

	this->velocity = round(this->velocity);
	this->leftCir.move(this->velocity, 0.f);
	this->rightCir.move(this->velocity, 0.f);
	this->shape.move(this->velocity, 0.f);
}

//Functions
void Paddle::update(Barrier *barriers)
{
	this->updateMovement();
	this->updateCollision(barriers->checkCollision(this->leftCir.getGlobalBounds()) | barriers->checkCollision(this->rightCir.getGlobalBounds()));
}

void Paddle::render(RenderTarget *target)
{
	target->draw(this->leftCir);
	target->draw(this->rightCir);
	target->draw(this->shape);
}
