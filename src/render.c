#include "../inc/hodgepodge.h"

/**
 * normalizeAngle - normalizing the angle
 * @angle: the angle
 * Return: the normal angle
 */
double normalizeAngle(double angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

/**
 * distanceBetweenPoints - measures distance between points
 * @x1: first x point
 * @y1: first y point
 * @x2: second x point
 * @y2: second y point
 * Return: the distance
 */
double distanceBetweenPoints(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

/**
 * castRay - casts rays
 * @rayAngle: the ray angle
 * @stripld: counter
 */
void castRay(double rayAngle, int stripId)
{
	rayAngle = normalizeAngle(rayAngle);

	int rayFacingDown = rayAngle > 0 && rayAngle < PI;
	int rayFacingUp = !rayFacingDown;

	int rayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
	int rayFacingLeft = !rayFacingRight;

	double xintercept, yintercept;
	double xstep, ystep;

	/* Horizontal ray-grid intersection code */
	int foundHorzWallHit = FALSE;
	double horzWallHitX = 0;
	double horzWallHitY = 0;
	double horzWallContent = 0;

	/* Finding the y-coordinate of the closest horizontal grid intersection */
	yintercept = floor(p.posY / TILE_SIZE) * TILE_SIZE;
	yintercept += rayFacingDown ? TILE_SIZE : 0;

	/* Finding the x-coordinate of the closest horizontal grid intersection */
	xintercept = p.posX + (yintercept - p.posY) / tan(rayAngle);

	/* Calculate the increment xstep and ystep */
	ystep = TILE_SIZE;
	ystep *= rayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (rayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (rayFacingRight && xstep < 0) ? -1 : 1;

	double nextHorzTouchX = xintercept;
	double nextHorzTouchY = yintercept;

	/* Incrementing xstep and ystep until finding a wall */
	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT) 
	{
		double xToCheck = nextHorzTouchX;
		double yToCheck = nextHorzTouchY + (rayFacingUp ? -1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck)) {
			/* found a wall hit */
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundHorzWallHit = TRUE;
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
        	}
    	}

	/* Vertical ray-grid intersection code */
	int foundVertWallHit = FALSE;
	double vertWallHitX = 0;
	double vertWallHitY = 0;
	int vertWallContent = 0;

	/* Finding the x-coordinate of the closest horizontal grid intersection */
	xintercept = floor(p.posX / TILE_SIZE) * TILE_SIZE;
	xintercept += rayFacingRight ? TILE_SIZE : 0;

	/* Finding the y-coordinate of the closest horizontal grid intersection */
	yintercept = p.posY + (xintercept - p.posX) * tan(rayAngle);

	/* Calculating the increment xstep and ystep */
	xstep = TILE_SIZE;
	xstep *= rayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (rayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (rayFacingDown && ystep < 0) ? -1 : 1;

	double nextVertTouchX = xintercept;
	double nextVertTouchY = yintercept;

	/* Incrementing xstep and ystep until finding a wall */
	while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT)
	{
		double xToCheck = nextVertTouchX + (rayFacingLeft ? -1 : 0);
		double yToCheck = nextVertTouchY;

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			/* found a wall hit */
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundVertWallHit = TRUE;
			break;
		}
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	}

	/* Calculate both horizontal and vertical hit distances and choose the smallest one */
	double horzHitDistance = foundHorzWallHit
		? distanceBetweenPoints(p.posX, p.posY, horzWallHitX, horzWallHitY)
		: INT_MAX;
	double vertHitDistance = foundVertWallHit
		? distanceBetweenPoints(p.posX, p.posY, vertWallHitX, vertWallHitY)
		: INT_MAX;

	if (vertHitDistance < horzHitDistance) {
		rays[stripId].distance = vertHitDistance;
		rays[stripId].hitX = vertWallHitX;
		rays[stripId].hitY = vertWallHitY;
		rays[stripId].wallHitContent = vertWallContent;
		rays[stripId].verticalHit = TRUE;
	}
	else
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].hitX = horzWallHitX;
		rays[stripId].hitY = horzWallHitY;
		rays[stripId].wallHitContent = horzWallContent;
		rays[stripId].verticalHit = FALSE;
	}
	rays[stripId].rayAngle = rayAngle;
	rays[stripId].rayFacingDown = rayFacingDown;
	rays[stripId].rayFacingUp = rayFacingUp;
	rays[stripId].rayFacingLeft = rayFacingLeft;
	rays[stripId].rayFacingRight = rayFacingRight;
}

/**
 * renderMap - rendering rays
 */
void castAllRays(void)
{
	int stripld;
	double rayAngle;

	rayAngle = p.rotAngle - (FOV_ANGLE / 2);

	for (stripld = 0; stripld < NUM_RAYS; stripld++)
	{
		castRay(rayAngle, stripld);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}

/**
* renderMap - rendering the map
* @instance: sdl instance
*/
void renderMap(SDL_Instance instance)
{
	int i, j;
	int tileX, tileY, tileColor;

	for (i = 0; i < MAP_WIDTH; i++)
	{
		for (j = 0; j < MAP_HEIGHT; j++)
		{
			tileX = j * TILE_SIZE;
			tileY = i * TILE_SIZE;
			tileColor = map[i][j] != 0 ? 255 : 0;

			SDL_SetRenderDrawColor(instance.renderer, tileColor, tileColor, tileColor, 255);
			SDL_Rect mapTileRect = {
				tileX * MINIMAP_SCALE_FACTOR,
				tileY * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR
			};
			SDL_RenderFillRect(instance.renderer, &mapTileRect);
		}
	}
}

/**
 * renderRays - renders rays
 */
void renderRays(SDL_Instance instance)
{
	int i;

	SDL_SetRenderDrawColor(instance.renderer, 255, 0, 0, 255);
	for (i = 0; i < NUM_RAYS; i++)
	{
		SDL_RenderDrawLine(
				instance.renderer,
				MINIMAP_SCALE_FACTOR * p.posX,
				MINIMAP_SCALE_FACTOR * p.posY,
				MINIMAP_SCALE_FACTOR * rays[i].hitX,
				MINIMAP_SCALE_FACTOR * rays[i].hitY
			);
	}
}
