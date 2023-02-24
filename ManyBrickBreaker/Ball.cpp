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
	if (this->state == 1)
	{
		this->state = 0;
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
	/*
		Collision flag
		-1 if vertical collision
		0 if no collision
		1 if horizontal collision
		2 if complex collision (circle-to-circle)
	*/
	if (flag == 1)
		this->velocity.x += 2 * vel.x;
	else if (flag == -1)
		this->velocity.y += 2 * vel.y;
	else if (flag == 2)
	{
		this->velocity.x += 2 * vel.x;
		this->velocity.y += 2 * vel.y;
	}
}

void Ball::updateBarriersCollision(Barrier *barriers)
{
	this->updateCollision(-this->velocity, barriers->checkCollision(this->shape.getGlobalBounds()));
}

void Ball::updatePaddleCollision(Paddle *paddle)
{
	int flag = paddle->checkSidesCollision(this->shape);
	if (flag != 0)
	{
		Vector2f newVel;
		if (flag == 2)
			// ###### remmber to put all of this into a new physics engine class later ########
			newVel = ctcCollisionHandle(this->shape, this->velocity, paddle->getLeft(), Vector2f(paddle->getSpeed(), 0.f));
		else if (flag == -2)
			newVel = ctcCollisionHandle(this->shape, this->velocity, paddle->getRight(), Vector2f(paddle->getSpeed(), 0.f));
		this->updateCollision(newVel, abs(flag));
		this->shape.move(this->velocity);
	}
	else
		this->updateCollision(-this->velocity, paddle->checkMidCollision(this->shape));
}

void Ball::updateBricksCollision(std::vector<std::vector<Brick *>> bricks)
{
	for (int i = 0; i < bricks.size(); i++)
		for (int j = 0; j < bricks[i].size(); j++)
			this->updateCollision(-this->velocity, bricks[i][j]->checkCollision(this->shape));
}

void Ball::update(sf::RenderTarget *target, Paddle *paddle, Barrier *barriers, vector<vector<Brick *>> bricks)
{
	//Update the ball's position if it is attached to the paddle
	if (this->state == 1)
		this->updateAttached(paddle->getShape());
	else 
	{
		//DEBUG cout << this->velocity.x << " " << this->velocity.y << endl;
		
		//Cap the ball's speed so there will be less bugs =w=
		if (this->velocity.x > this->maxSpeed.x or this->velocity.x < -this->maxSpeed.x)
			this->velocity.x = signnum(this->velocity.x) * this->maxSpeed.x;
		if (this->velocity.y > this->maxSpeed.y or this->velocity.y < -this->maxSpeed.y)
			this->velocity.y = signnum(this->velocity.y) * this->maxSpeed.y;
		
		//Update the ball's position if it is detached from the paddle
		this->updateDetached();

		//Update the ball after collision with barriers
		this->updateBarriersCollision(barriers);
		
		//Update the ball after collision with paddle
		this->updatePaddleCollision(paddle);

		this->updateBricksCollision(bricks);
	}

	Vector2f ballPos = this->shape.getPosition();
	if (ballPos.x < 0.f || ballPos.x > target->getSize().x || ballPos.y > target->getSize().y || ballPos.y < 0.f)
		this->state = -1;
}

void Ball::render(RenderTarget *target)
{
	target->draw(this->shape);
}
