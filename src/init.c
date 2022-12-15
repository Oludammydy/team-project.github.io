#include "../inc/hodgepodge.h"

/**
 * init - Starts up SDL and creates window
 * @instance: A new SDL instance
 * Return: 1 on success and 0 on Failure
 */
int init(SDL_Instance *instance)
{
	/* Initializing SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf(SDL_INIT_FAIL, SDL_GetError());
		return (1);
	}
	else
	{	/* Create a new window */
		instance->window = SDL_CreateWindow("Hodgepodge",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_RESIZABLE);
		if (instance->window == NULL)
		{
			printf(CREATE_WINDOW_FAIL, SDL_GetError());
			SDL_Quit();
			return (1);
		}
		else
		{	/* Create a new Renderer linked to the window */
			instance->renderer = SDL_CreateRenderer(
				instance->window, -1,
				SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (instance->renderer == NULL)
			{
				SDL_DestroyWindow(instance->window);
				printf(CREATE_RENDERER_FAIL, SDL_GetError());
				SDL_Quit();
				return (1);
			}
		}
	}
	return (0);
}
