#include "../inc/hodgepodge.h"

/**
 * refresh - Updates the screen
 */

void refresh(void)
{
	float tyme;

	while ( !SDL_TICKS_PASSED(SDL_GetTicks(),
		ticksLastFrame + FRAME_TIME_LENGTH)
		);

	tyme = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
	ticksLastFrame = SDL_GetTicks();
	movePlayer(tyme);
	castAllRays();
}
