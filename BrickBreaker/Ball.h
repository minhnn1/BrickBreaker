#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Ball class. Spawn and released from paddle.
	Can collide with paddle, bricks, barriers.
*/

class Ball
{
private:
	//Variables
	sf::CircleShape shape;
	sf::Vector2f velocity;

	//Private functions
	void initVariable();
	void initShape();
	void initPos(float x, float y);

public:
	Ball(float x, float y);
	virtual ~Ball();

	//Functions
	const sf::CircleShape getShape() const;

	//Ball movements
	void updateAttached(sf::Vector2f paddlePos);
	void updateDetached(float x);

	//Collision handle
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void updateCollision();

	//Update & Render
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

