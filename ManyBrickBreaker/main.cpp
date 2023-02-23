#include "pch.h"
#include "GameEngine.h"
using namespace std;

int main()
{
	//Init game engine
	GameEngine engine;
	
	//Main game loop
	while (engine.isRunning())
	{
		//Update
		engine.update();

		//Render
		engine.render();
	}

	return 0;
} 