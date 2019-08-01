#include "graphics.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Graphics* Graphics::_instance = nullptr;
std::map<std::string, SDL_Surface *> Graphics::_spriteSheets = std::map<std::string, SDL_Surface *>();
std::map<std::string, SDL_Texture *> Graphics::_textureSheets = std::map<std::string, SDL_Texture *>();

Graphics::Graphics()
{}

Graphics::~Graphics()
{
	for (auto &textureSheet : _textureSheets)
	{
		SDL_DestroyTexture(textureSheet.second);
	}
	for(auto &spriteSheet : _spriteSheets)
	{
		SDL_FreeSurface(spriteSheet.second);
	}
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
}

void Graphics::setWindowMode(const char *windowTitle, bool fullscreen, int screenWidth, int screenHeight)
{
	if (fullscreen)
	{
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		screenWidth = DM.w;
		screenHeight = DM.h;
	}
	_window = SDL_CreateWindow(windowTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
	SDL_SetWindowTitle(_window, windowTitle);
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	if (fullscreen)
	{
		SDL_SetWindowFullscreen(this->_window, SDL_WINDOW_FULLSCREEN);
	}
}

void Graphics::blitSurface(SDL_Texture *texture, SDL_Rect *source, SDL_Rect *destination)
{
	SDL_RenderCopy(_renderer, texture, source, destination);
}

void Graphics::flip()
{
	SDL_RenderPresent(_renderer);
}

void Graphics::fillBackground()
{
	SDL_RenderClear(_renderer);
}

SDL_Renderer *Graphics::getRenderer() const
{
	return _renderer;
}

void Graphics::setRenderColor(Color color)
{
	SDL_SetRenderDrawColor(
			_renderer,
			color.getRed(),
			color.getGreen(),
			color.getBlue(),
			color.getAlpha());
}

SDL_Surface *Graphics::loadImage(const std::string &path)
{
	if (!_spriteSheets.count(path))
	{
		_spriteSheets[path] = IMG_Load(path.c_str());
	}
	return _spriteSheets[path];
}

SDL_Texture* Graphics::getTextureFromImage(const char *path)
{
	if (_textureSheets.count(std::string(path)))
	{
		_textureSheets[(std::string)path] = SDL_CreateTextureFromSurface(this->getRenderer(), this->loadImage(path));
	}
	return _textureSheets[(std::string)path];
}