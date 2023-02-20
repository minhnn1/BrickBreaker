#include "pch.h"
#include "Paddle.h"

using namespace sf;
using namespace std;

//Private functions
void Paddle::initVariable()
{
	this->velocity = 0.f;
	this->acceleration = 0.2f;
}

void Paddle::initShape()
{
	//Middle rectangle color & shape
	this->Rect.setFillColor(Color::Red);			
	this->Rect.setSize(Vector2f(100.f, 10.f));

	//Leftside circle color & shape
	this->leftCir.setFillColor(Color::Blue);		
	this->leftCir.setRadius(5.f);


	//Rightside circle color & shape
	this->rightCir.setFillColor(Color::Green);		
	this->rightCir.setRadius(5.f);
}

void Paddle::initPos(float x, float y)
{
	FloatRect RectBounds = this->Rect.getGlobalBounds();

	//Middle rectangle origin & position
	this->Rect.setOrigin(RectBounds.width / 2, 0);
	this->Rect.setPosition(x, y);

	//Leftside circle origin & position
	this->leftCir.setOrigin(RectBounds.height / 2, RectBounds.height / 2);														
	this->leftCir.setPosition(x - RectBounds.width / 2, y + RectBounds.height / 2);

	//Rightside circle origion & position
	this->rightCir.setOrigin(RectBounds.height / 2, RectBounds.height / 2);
	this->rightCir.setPosition(x + RectBounds.width / 2, y + RectBounds.height / 2);
}

//Constructors & Destructors
Paddle::Paddle(float x, float y)
{
	this->initVariable();
	this->initShape();
	this->initPos(x, y);
}

Paddle::~Paddle()
{

}

//Functions
float linear_interpolation(float x, float y, float z)
{
	//current speed, max speed, acceleration
	return ((1.0f - z) * x) + (z * y);
}

Vector2f Paddle::getPos()
{
	return this->Rect.getPosition();
}

float Paddle::getSpeed()
{
	return this->velocity;
}

void Paddle::updateInput()
{
	//Keyboard input
	//Left
	if (Keyboard::isKeyPressed(Keyboard::Left))
	{
		this->velocity = -linear_interpolation(-velocity, 10.f, this->acceleration);
		this->Rect.move(this->velocity, 0.f);
		this->leftCir.move(this->velocity, 0.f);
		this->rightCir.move(this->velocity, 0.f);
	}

	//Right
	else if (Keyboard::isKeyPressed(Keyboard::Right))
	{
		this->velocity = linear_interpolation(velocity, 10.f, this->acceleration);
		this->Rect.move(this->velocity, 0.f);
		this->leftCir.move(this->velocity, 0.f);
		this->rightCir.move(this->velocity, 0.f);
	}

	else
	{
		this->velocity = 0.f;
	}
}

void Paddle::updateWindowBoundsCollision(const RenderTarget* target)
{	
	FloatRect leftCirBounds = this->leftCir.getGlobalBounds();
	FloatRect rightCirBounds = this->rightCir.getGlobalBounds();

	//Left
	if (leftCirBounds.left <= 0.f)
	{
		this->Rect.move(this->velocity, 0.f);
		this->leftCir.move(this->velocity, 0.f);
		this->rightCir.move(this->velocity, 0.f);
	}
		
	//Right
	else if (rightCirBounds.left + rightCirBounds.width >= target->getSize().x)
	{
		this->Rect.move(-this->velocity, 0.f);
		this->leftCir.move(-this->velocity, 0.f);
		this->rightCir.move(-this->velocity, 0.f);
	}
}

bool Paddle::checkCollision(const sf::CircleShape ball)
{
	//Get the ball's bounds
	FloatRect ballBounds = ball.getGlobalBounds();

	//Get paddle bounds
	FloatRect rectBounds = this->Rect.getGlobalBounds();
	FloatRect leftCirBounds = this->leftCir.getGlobalBounds();
	FloatRect rightCirBounds = this->rightCir.getGlobalBounds();

	if (rectBounds.intersects(ballBounds) || leftCirBounds.intersects(ballBounds) || rightCirBounds.intersects(ballBounds))
		return true;
	return false;
}

void Paddle::update(const RenderTarget* target)
{
	//Paddle movements
	this->updateInput();
	
	//Window bounds collision. Check after movements to stop from going out of bounds.
	this->updateWindowBoundsCollision(target);
}

void Paddle::render(RenderTarget* target)
{
	target->draw(this->Rect);
	target->draw(this->leftCir);
	target->draw(this->rightCir);
}

