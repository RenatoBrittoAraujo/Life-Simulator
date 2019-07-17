#include "game.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

int main(int argc, char **argv)
{
	bool verbose = false;
	int framerate = 60;
	bool fullscreen = false;

	for (int i = 1; i < argc; i++)
	{
		if (strlen(argv[i]) > 1 and argv[i][1] == 'v')
		{
			verbose = true;
		}
		if (strlen(argv[i]) > 1 and argv[i][1] == 'f')
		{
			fullscreen = true;
		}
		if (strlen(argv[i]) > 2 and argv[i][1] == 'r')
		{
			framerate = atoi(argv[i] + 1);
		}
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