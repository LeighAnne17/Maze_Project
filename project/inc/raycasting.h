#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 10
#define MAP_HEIGHT 8

void render_scene(SDL_Renderer *renderer, float posX, float posY, float dirX, float dirY, float planeX, float planeY, char worldMap[MAP_WIDTH][MAP_HEIGHT]);
int load_map(const char *filename, char worldMap[MAP_WIDTH][MAP_HEIGHT]);

#endif /* RAYCASTING_H */

