#pragma once

#include "Paddle.h"
#include "Ball.h"

/*
	Game engine class. 
	Wrapper class.
*/
class EventHandler
{
private:
	//Window
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Variables
	bool gameOver;
	bool isAttached;
	Paddle paddle;
	std::vector<Ball> balls;

	//Private functions
	void initVariables();
	void initWindow();

public:
	//Constructors & Destructors
	EventHandler();
	virtual ~EventHandler();

	//Accessors
	const bool isRunning() const;

	//Functions
	void pollEvents();
	void spawnBall();

	void update();
	void render();
};

