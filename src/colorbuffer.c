#include "../inc/hodgepodge.h"

/**
 * clearColorBuffer - clears the color buffer
 * @color: the color
 */
void clearColorBuffer(Uint32 color)
{
	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		for (int y = 0; y < WINDOW_HEIGHT; y++)
			colorBuffer[(WINDOW_WIDTH * y) + x] = color;
	}
}

/**
 * renderColorBuffer - renders the color buffer
 */
void renderColorBuffer(SDL_Instance instance)
{
	SDL_UpdateTexture(
			colorBufferTexture,
			NULL, colorBuffer,
			(int)((Uint32)WINDOW_WIDTH * sizeof(Uint32))
			);
	SDL_RenderCopy(instance.renderer, colorBufferTexture, NULL, NULL);
}
