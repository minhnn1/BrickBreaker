#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


/*
	Paddle class.
	Controlled by players, moving side to side.
	Can collide with balls.
*/
class Paddle
{
private:
	//Variables
	sf::RectangleShape Rect;
	sf::CircleShape leftCir, rightCir;
	float velocity;
	float acceleration;

	//Private functions
	void initVariable();
	void initShape();
	void initPos(float x, float y);

public:
	Paddle(float x = 450.f, float y = 650.f);
	virtual ~Paddle();

	//Functions
	sf::Vector2f getPos();
	float getSpeed();

	//Paddle Movements
	void updateInput();

	//Collision handle
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	bool checkCollision(const sf::CircleShape ball);

	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

