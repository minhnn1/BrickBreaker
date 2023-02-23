#include "pch.h"
#include "GameEngine.h"
using namespace sf;
using namespace std;

//Private functions
void GameEngine::initVariables()
{
	this->videoMode = VideoMode(1000, 800);
	this->window = nullptr;
	this->barriers = nullptr;
	this->paddle = nullptr;
}

void GameEngine::initWindow()
{
	this->window = new RenderWindow(this->videoMode, "Brick Breaker", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

void GameEngine::initStage()
{
	this->paddle = new Paddle(this->window);
	this->barriers = new Barrier();
}

//Constructors & Destructors
GameEngine::GameEngine()
{
	this->initVariables();
	this->initWindow();
	this->initStage();
}

GameEngine::~GameEngine()
{
	delete this->window;
}

//Accessors
const bool GameEngine::isRunning() const
{
	return this->window->isOpen();
}

//Functions

void GameEngine::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void GameEngine::spawnBall()
{
	if (this->balls.size() == 0)
	{
		Ball newBall = Ball(this->paddle->getShape(), 1);
		this->balls.push_back(newBall);
	}
}

void GameEngine::updateBall()
{
	bool launch_flag = false; //check if Space is pressed so we don't have to use another loop
	if (Keyboard::isKeyPressed(Keyboard::Space))
		launch_flag = true;
	for (int i = 0; i < this->balls.size(); i++)
	{
		if (launch_flag)
			this->balls[i].launch(this->paddle->getSpeed());
		this->balls[i].update(this->window, this->paddle, this->barriers);
		if (this->balls[i].getState() == -1)
			this->balls.erase(this->balls.begin() + i);
	}
		
}

void GameEngine::renderBall()
{
	for (int i = 0; i < this->balls.size(); i++)
		this->balls[i].render(this->window);

}

void GameEngine::update()
{
	this->pollEvents();
	this->paddle->update(this->barriers);

	this->spawnBall();
	this->updateBall();
}

void GameEngine::render()
{
	//Clear old frame
	this->window->clear(Color::Black);

	//Draw game objects
	this->barriers->render(this->window);
	this->paddle->render(this->window);
	this->renderBall();

	//Display new frame
	this->window->display();
}
