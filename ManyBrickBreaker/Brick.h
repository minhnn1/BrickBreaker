#pragma once
class Brick : public PhysicEngine
{
private:
	//Variables
	sf::RectangleShape shape;
	int state;
	/* state of the brick
		0 if the brick is going to be removed
		>= 1 if the brick still exists in the stage
	 */

	//Private functions
	void initVariable(int state);
	void initShape();
	void initPos(sf::Vector2f pos);

public:
	//Constructors & Destructors
	Brick(sf::Vector2f pos, int state);
	virtual ~Brick();

	//Accessors
	int getState();

	//Functions
	int checkCollision(sf::CircleShape ball, int ballState);

	void update();
	void render(sf::RenderTarget* target);
};

