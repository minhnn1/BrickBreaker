#include "pch.h"
#include "Ball.h"
using namespace sf;
using namespace std;

//Private functions
void Ball::initVariables(int state)
{
	this->velocity = Vector2f(0.f, 0.f);
	this->state = state;
	this->maxSpeed = Vector2f(5.f, 5.f);
}

void Ball::initShape()
{
	this->shape.setFillColor(Color::White);
	this->shape.setRadius(5.f);
	this->shape.setOutlineThickness(1);
}

void Ball::initPos(Vector2f paddlePos)
{
	float radius = this->shape.getRadius();
	this->shape.setOrigin(radius, radius);
	this->shape.setPosition(paddlePos);
}

//Constructors & Destructors
Ball::Ball(RectangleShape paddle, int state)
{
	this->initVariables(state);
	this->initShape();
	this->initPos(paddle.getPosition());
}

Ball::~Ball()
{

}

//Accessors
int Ball::getState()
{
	return this->state;
}

//Functions
void Ball::launch(float xvel)
{
	if (this->state == 0)
	{
		this->state = 1;
		this->velocity = Vector2f(xvel, -5.f);
	}	
}

void Ball::updateAttached(RectangleShape paddle)
{
	this->shape.setPosition(paddle.getPosition());
}

void Ball::updateDetached()
{
	this->shape.move(this->velocity);
}

void Ball::updateCollision(Vector2f vel, int flag)
{
	//If the ball has already collided
	if (this->state == 2)
		return;
	/*
			Collision flag
		-1 if vertical collision
		0 if no collision
		1 if horizontal collision
		2 if complex collision (circle-to-circle)
	*/
	if (flag == 1)
	{
		if (this->velocity.x == 0)
			this->velocity.y += 2 * vel.y;
		else
			this->velocity.x += 2 * vel.x;
		this->state = 2;
		this->shape.move(this->velocity);
	}
		
	else if (flag == -1)
	{
		this->velocity.y += 2 * vel.y;
		this->state = 2;
		this->shape.move(this->velocity);
	}
		
	else if (flag == 2)
	{
		this->velocity.x += 2 * vel.x;
		this->velocity.y += 2 * vel.y;
		this->state = 2;
		this->shape.move(this->velocity);
	}
}

void Ball::updateBarriersCollision(Barrier *barriers)
{
	this->updateCollision(-this->velocity, barriers->checkCollision(this->shape.getGlobalBounds()));
}

void Ball::updatePaddleCollision(Paddle *paddle)
{

	if (CirToCirCollision(paddle->getLeft(), this->shape))
	{
		Vector2f newVel = CirToCirCollisionHandle(this->shape, this->velocity, paddle->getLeft(), Vector2f(paddle->getSpeed(), 0.f));
		this->updateCollision(newVel, 2);
	}
	else if (CirToCirCollision(paddle->getRight(), this->shape))
	{

		Vector2f newVel = CirToCirCollisionHandle(this->shape, this->velocity, paddle->getRight(), Vector2f(paddle->getSpeed(), 0.f));
		this->updateCollision(newVel, 2);
	}
	else
		this->velocity = BallPaddleCollisionHandle(this->velocity, this->shape, paddle->getShape());
}

void Ball::updateBricksCollision(std::vector<std::vector<Brick *>> bricks)
{
	for (int i = 0; i < bricks.size(); i++)
		for (int j = 0; j < bricks[i].size(); j++)
			this->updateCollision(-this->velocity, bricks[i][j]->checkCollision(this->shape, this->state));
}

void Ball::update(sf::RenderTarget *target, Paddle *paddle, Barrier *barriers, vector<vector<Brick *>> bricks)
{
	//Update the ball's position if it is attached to the paddle
	if (this->state == 0)
		this->updateAttached(paddle->getShape());
	else 
	{
		this->state = 1;
		//DEBUG cout << this->velocity.x << " " << this->velocity.y << endl;
		
		//Update the ball after collision with barriers
		this->updateBarriersCollision(barriers);
		
		//Update the ball after collision with paddle
		this->updatePaddleCollision(paddle);

		this->updateBricksCollision(bricks);

		//Cap the ball's speed so there will be less bugs =w=
		while (abs(this->velocity.x) > 5.f || (this->velocity.y) > 5.f)
		{
			this->velocity.x *= 0.8;
			this->velocity.y *= 0.8;
		}

		//Update the ball's position if it is detached from the paddle
		this->updateDetached();
	}

	Vector2f ballPos = this->shape.getPosition();
	if (ballPos.x < 0.f || ballPos.x > target->getSize().x || ballPos.y > target->getSize().y || ballPos.y < 0.f)
		this->state = -1;
}

void Ball::render(RenderTarget *target)
{
	target->draw(this->shape);
}
