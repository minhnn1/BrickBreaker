#pragma once
class Brick
{
private:
	//Variables
	sf::RectangleShape shape;
	int state;
	/* state of the brick
		1 if the brick still exists in the stage
		0 if the brick is going to be removed
	 */

	//Private functions
	void initVariable();
	void initShape();
	void initPos(sf::Vector2f pos);

public:
	//Constructors & Destructors
	Brick(sf::Vector2f pos);
	virtual ~Brick();

	//Accessors
	int getState();

	//Functions
	int checkCollision(sf::CircleShape ball);

	void update();
	void render(sf::RenderTarget* target);
};

