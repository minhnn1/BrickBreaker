#include "pch.h"
#include "Barrier.h"
using namespace sf;

//Private Functions
void Barrier::initShape()
{
	this->leftBar.setFillColor(Color::Red);
	this->leftBar.setSize(Vector2f(5.f, 800.f));

	this->rightBar.setFillColor(Color::Blue);
	this->rightBar.setSize(Vector2f(5.f, 800.f));

	this->topBar.setFillColor(Color::Green);
	this->topBar.setSize(Vector2f(1000.f, 5.f));
}

void Barrier::initPos()
{
	this->leftBar.setPosition(0.f, 0.f);
	this->rightBar.setPosition(995.f, 0.f);
	this->topBar.setPosition(0.f, 0.f);
}

//Constructors & Destructors
Barrier::Barrier()
{
	this->initShape();
	this->initPos();
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
