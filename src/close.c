#include "../inc/hodgepodge.h"

/**
 * close_up - Does clean up on exit
 */

void close_up(SDL_Instance instance)
{
	/* Destroy Renderer */
	SDL_DestroyRenderer(instance.renderer);
	/* Destroy Window */
	SDL_DestroyWindow(instance.window);
	/* Quit SDL */
	SDL_Quit();
}
