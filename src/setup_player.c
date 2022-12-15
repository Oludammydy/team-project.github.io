#include "../inc/hodgepodge.h"
#include "../inc/textures.h"

/**
 * setupPlayer - Sets player's characteristics
 */

void setupPlayer(SDL_Instance instance)
{
	p.posX = WINDOW_WIDTH / 2;
	p.posY = WINDOW_HEIGHT / 2;
	p.height = 10;
	p.width = 10;
	p.rotAngle = PI / 2;
	p.moveSpeed = 100;
	p.turnSpeed = 45 * (PI / 180);

	colorBuffer = (Uint32*) malloc(sizeof(Uint32) * (Uint32)WINDOW_WIDTH * (Uint32)WINDOW_HEIGHT);

	colorBufferTexture = SDL_CreateTexture(
			instance.renderer,
			SDL_PIXELFORMAT_ARGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WINDOW_WIDTH, WINDOW_HEIGHT
		);

	/* loading textures from the textures.h */
	textures[0] = (Uint32 *) REDBRICK_TEXTURE;
	textures[1] = (Uint32 *) PURPLESTONE_TEXTURE;
	textures[2] = (Uint32 *) MOSSYSTONE_TEXTURE;
	textures[3] = (Uint32 *) GRAYSTONE_TEXTURE;
	textures[4] = (Uint32 *) COLORSTONE_TEXTURE;
	textures[5] = (Uint32 *) BLUESTONE_TEXTURE;
	textures[6] = (Uint32 *) WOOD_TEXTURE;
	textures[7] = (Uint32 *) EAGLE_TEXTURE;
}

/**
 * renderPlayer - renders the player
 * @instance: sdl instance
 */
void renderPlayer(SDL_Instance instance)
{
	SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 255);
	SDL_Rect playerRect = {
		p.posX * MINIMAP_SCALE_FACTOR,
		p.posY * MINIMAP_SCALE_FACTOR,
		p.width * MINIMAP_SCALE_FACTOR,
		p.height * MINIMAP_SCALE_FACTOR
	};
	SDL_RenderFillRect(instance.renderer, &playerRect);

	SDL_RenderDrawLine(
			instance.renderer,
			MINIMAP_SCALE_FACTOR * p.posX,
			MINIMAP_SCALE_FACTOR * p.posY,
			MINIMAP_SCALE_FACTOR * (p.posX + cos(p.rotAngle) * 40),
			MINIMAP_SCALE_FACTOR * (p.posY + sin(p.rotAngle) * 40)
    );
}

/**
 * mapHasWallAt - detects wall collision
 * @x: position x
 * @y: position y
 * Return: 0 if true, 1 if false
 */
int mapHasWallAt(double x, double y)
{
    int mapGridX, mapGridY;

    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
    {
	    return (FALSE);
    }

    mapGridX = floor(x / TILE_SIZE);
    mapGridY = floor(y / TILE_SIZE);
    return (map[mapGridY][mapGridX] != 0);
}

/**
 * movePlayer - moving player
 * @tyme: time
 */
void movePlayer(double tyme)
{
	double moveStep, newPlayerX, newPlayerY;

	p.rotAngle += p.turnDir * p.turnSpeed * 1.10 * tyme;

	moveStep = p.moveDir * p.moveSpeed * tyme;

	newPlayerX = p.posX + cos(p.rotAngle) * moveStep;
	newPlayerY = p.posY + sin(p.rotAngle) * moveStep;

	if (!mapHasWallAt(newPlayerX, newPlayerY))
	{
		p.posX = newPlayerX;
		p.posY = newPlayerY;
	}
}
