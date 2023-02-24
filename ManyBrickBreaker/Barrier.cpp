#include "pch.h"
#include "Barrier.h"
using namespace sf;
using namespace std;

//Private Functions
void Barrier::initVariables()
{
	this->size = 5.f;
}


void Barrier::initShape(RenderTarget *target)
{
	Vector2u winSize = target->getSize();

	this->leftBar.setFillColor(Color::Green);
	this->leftBar.setSize(Vector2f(this->size, (float)winSize.y));

	this->rightBar.setFillColor(Color::Blue);
	this->rightBar.setSize(Vector2f(this->size, (float)winSize.y));

	this->topBar.setFillColor(Color::Red);
	this->topBar.setSize(Vector2f((float)winSize.x, this->size));
}

void Barrier::initPos(RenderTarget *target)
{
	Vector2u winSize = target->getSize();
		 
	this->leftBar.setPosition(0.f, this->size);
	this->rightBar.setPosition((float)winSize.x - this->size, this->size);
	this->topBar.setPosition(0.f, 0.f);
}

//Constructors & Destructors
Barrier::Barrier(RenderTarget *target)
{
	this->initVariables();
	this->initShape(target);
	this->initPos(target);
}

Barrier::~Barrier()
{

}

int Barrier::checkCollision(sf::FloatRect objBounds)
{
	/*
		Check for barriers collision.
		Return 1 if it's a horizontal collision (hits the left/right barriers)
		return -1 if it's a vertical collision (hits the ceiling barrier)
		return 0 if there's no collision
	*/
	if (this->leftBar.getGlobalBounds().intersects(objBounds) || this->rightBar.getGlobalBounds().intersects(objBounds))
		return 1;
	else if (this->topBar.getGlobalBounds().intersects(objBounds))
		return -1;
	return 0;
}

void Barrier::update()
{

}

void Barrier::render(RenderTarget *target)
{
	target->draw(this->leftBar);
	target->draw(this->rightBar);
	target->draw(this->topBar);
}
