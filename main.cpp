#include <iostream>
#include <dream.h>
#include "game.h"

#define W 800
#define H 600

Game game;

int main()
{
	LoadWindow((char*)"Mario Clone",W,H);

	while(!done())
	{
		DrawScreen();
		switch(game.state)
		{
			case 1:
				game.menu();
				break;

			case 2:
				game.init();
				break;
		
			case 3:
				game.update();
				game.draw();
				break;

			default:
				break;
		}
		Render(70);
	}
	//kill();
	CloseWindow();
}
