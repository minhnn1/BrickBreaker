#include "pch.h"
#include "EventHandler.h"

using namespace sf;
using namespace std;

//Private functions
void EventHandler::initVariables()
{
	this->videoMode = VideoMode(1000, 800);
	this->window = nullptr;
	this->gameOver = false;
	this->isAttached = false;
}

void EventHandler::initWindow()
{
	this->window = new RenderWindow(this->videoMode, "Brick breaker", Style::Titlebar | Style::Close);
	this->window->setFramerateLimit(60);
}

//Constructors & Destructors
EventHandler::EventHandler()
{
	this->initVariables();
	this->initWindow();
}

EventHandler::~EventHandler()
{
	delete this->window;
}

//Accessors
const bool EventHandler::isRunning() const
{
	return this->window->isOpen();
}

//Functions
void EventHandler::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		//Closing the game
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

void EventHandler::spawnBall()
{
	if (this->balls.size() == 0)
	{
		Vector2f spawnPos = this->paddle.getPos();
		this->balls.push_back(Ball(spawnPos.x, spawnPos.y));
		this->isAttached = true;
	}
}

void EventHandler::update()
{
	this->pollEvents();

	this->paddle.update(this->window);

	this->spawnBall();
	
	//Update if the ball has launched (detached)
	if (Keyboard::isKeyPressed(Keyboard::Space))
	{
		this->balls.back().updateDetached(this->paddle.getSpeed());
		this->isAttached = false;

	}

	//Update if the ball has not launched yet (attached)
	if (this->isAttached)
		balls.back().updateAttached(this->paddle.getPos());

	//Update balls' movements
	for (auto& i : balls)
	{
		if (this->paddle.checkCollision(i.getShape()))
			i.updateCollision();
		i.update(this->window);
	}
		
}

void EventHandler::render()
{
	/*
		@return void

		Renders the game objects:
		- clear old frame
		- render objects
		- display new frame
	*/
	//Clear old frame
	this->window->clear(Color::Black);

	//Draw game objects
	this->paddle.render(this->window); //draw the paddle
	for (auto &i : this->balls)
		i.render(this->window);
	
	//Display new frame
	this->window->display();
}
