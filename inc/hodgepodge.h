#ifndef HODGEPODGE_H
#define HODGEPODGE_H

/* Libraries */
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

/* Constants */
#define FALSE 0
#define TRUE 1

#define PI 3.14159265
#define TWO_PI 6.28318530

#define TILE_SIZE 64
#define MAP_WIDTH 19
#define MAP_HEIGHT 19
#define NUM_TEXTURES 8

#define MINIMAP_SCALE_FACTOR 0.20

#define WINDOW_WIDTH (MAP_WIDTH * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_HEIGHT * TILE_SIZE)

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

#define FOV_ANGLE (60 * (PI / 180))

#define NUM_RAYS WINDOW_WIDTH

#define FPS 30
#define FRAME_TIME_LENGTH (1000 / FPS)


/* Error Constants */
#define SDL_INIT_FAIL "SDL could not initialize! SDL_Error: %s\n"
#define CREATE_WINDOW_FAIL "Window could not be created! SDL_Error: %s\n"
#define CREATE_RENDERER_FAIL "Renderer could not be created! SDL_Error: %s\n"

extern SDL_Window *window;
extern SDL_Renderer *renderer;

extern const int map[MAP_WIDTH][MAP_HEIGHT];

extern int gameRunning;

extern int ticksLastFrame;
extern Uint32 *colorBuffer;
extern SDL_Texture *colorBufferTexture;
extern Uint32 *wallTexture;
extern Uint32 *textures[NUM_TEXTURES];

/* Structures */

/**
 * struct SDL_Instance - SDL instance/object
 * @window: Screen
 * @renderer: 2D rendering context for the window.
 */
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/**
 * Player - Viewer
 * @posX: X player coordinate
 * @posY: Y player coordinate
 * @height: Player height
 * @width: Player width
 * @rotAngle: Angle of rotation
 * @moveSpeed: Player speed of movement
 * @turnSpeed: Player rotation speed
 * @turnDir: Player turning direction
 * @moveDir: Player movement direction
 */
struct Player
{
	double posX;
	double posY;
	double height;
	double width;
	double rotAngle;
	double moveSpeed;
	double turnSpeed;
	int turnDir;
	int moveDir;
};
extern struct Player p;

struct Ray {
	double rayAngle;
	double hitX;
	double hitY;
	double distance;
	double verticalHit;
	int rayFacingUp;
	int rayFacingDown;
	int rayFacingLeft;
	int rayFacingRight;
	int wallHitContent;
} rays[NUM_RAYS];
extern struct Ray rays[NUM_RAYS];

/* Functions */
int init(SDL_Instance *);
void close_up(SDL_Instance instance);
void setupPlayer(SDL_Instance instance);
void renderPlayer(SDL_Instance instance);
int mapHasWallAt(double x, double y);
void movePlayer(double tyme);
int poll_events(void);
void clearColorBuffer(Uint32 color);
void renderColorBuffer(SDL_Instance instance);
void gen3DProjection(void);
void renderRays(SDL_Instance instance);
void renderMap(SDL_Instance instance);
void castAllRays(void);
void castRay(double rayAngle, int stripId);
double distanceBetweenPoints(double x1, double y1, double x2, double y2);
double normalizeAngle(double angle);
void refresh(void);

//double refresh(double time, double oldTime)

#endif /*HODGEPODGE_H*/
