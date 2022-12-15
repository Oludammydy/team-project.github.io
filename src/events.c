#include "../inc/hodgepodge.h"

/**
* poll_events - gets quit event
* Return: 1 if quitting, 0 if not.
*/
int poll_events(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				return (1);
			case SDL_KEYDOWN: {
				/* If 'ESCAPE' is pressed */
				if (event.key.keysym.sym == SDLK_ESCAPE)
					return (1);

				if (event.key.keysym.sym == SDLK_w)
					p.moveDir = +1;
				if (event.key.keysym.sym == SDLK_s)
					p.moveDir = -1;
				if (event.key.keysym.sym == SDLK_d)
					p.turnDir = +1;
				if (event.key.keysym.sym == SDLK_a)
					p.turnDir = -1;
				if (event.key.keysym.sym == SDLK_UP)
					p.moveDir = +1;
				if (event.key.keysym.sym == SDLK_DOWN)
					p.moveDir = -1;
				if (event.key.keysym.sym == SDLK_RIGHT)
					p.turnDir = +1;
				if (event.key.keysym.sym == SDLK_LEFT)
					p.turnDir = -1;
				break;
			}
			case SDL_KEYUP: {
				if (event.key.keysym.sym == SDLK_w)
					p.moveDir = 0;
				if (event.key.keysym.sym == SDLK_s)
					p.moveDir = 0;
				if (event.key.keysym.sym == SDLK_d)
					p.turnDir = 0;
				if (event.key.keysym.sym == SDLK_a)
					p.turnDir = 0;
				if (event.key.keysym.sym == SDLK_UP)
					p.moveDir = 0;
				if (event.key.keysym.sym == SDLK_DOWN)
					p.moveDir = 0;
				if (event.key.keysym.sym == SDLK_RIGHT)
					p.turnDir = 0;
				if (event.key.keysym.sym == SDLK_LEFT)
					p.turnDir = 0;
				break;
			}
		}
	}
	return (0);
}
