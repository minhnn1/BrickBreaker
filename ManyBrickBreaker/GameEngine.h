#pragma once
#include "pch.h"
#include "Paddle.h"
#include "Ball.h"
#include "Barrier.h"

class GameEngine
{
private:
	//Windows
	sf::RenderWindow *window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Variables
	Barrier *barriers;
	Paddle *paddle;
	std::vector<Ball> balls;

	//Private functions
	void initVariables();
	void initWindow();
	void initStage();

public:
	//Constructors & Destructors
	GameEngine();
	virtual ~GameEngine();

	//Accessors
	const bool isRunning() const;

	//Functions
	void pollEvents();
	void spawnBall();
	void updateBall();
	void renderBall();

	void update();
	void render();
};

