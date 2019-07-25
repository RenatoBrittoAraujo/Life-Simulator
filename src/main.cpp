#include "game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

bool verbose = false;
int framerate = 60;
bool fullscreen = false;

void customRun()
{
	std::cout<<"Game ran on custom mode"<<std::endl;
	std::cout<<"Set custom settings before running the game"<<std::endl;
	char op = '.';
	std::cout<<"Do you want to run fullscreen? (y/n) ";
	while(std::cin>>op, !(op == 'y' or op == 'n')) {}
	fullscreen = op == 'y';
	op = '.';
	std::cout<<"Do you want to run verbose? (y/n) ";
	while(std::cin>>op, !(op == 'y' or op == 'n')) {}
	verbose = op == 'y';
	std::cout << "Framerate: ";
	std::cin>>framerate;
}

int main(int argc, char **argv)
{
	if (argc > 1 and argv[1][1] == 'c')
	{
		customRun();
	}
	else if(argc > 1 and argv[1][1] == 'v')
	{
		verbose = true;
	}
	else if (argc > 1 and argv[1][1] == 'f')
	{
		fullscreen = true;
	}

	try
	{
		Game game;

		game.setFramerate(framerate);
		game.setVerbose(verbose);

		if (game.init(fullscreen))
		{
			game.run();
		}

		game.exit();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	


	return 0;
}