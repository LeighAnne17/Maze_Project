#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAP_WIDTH 8
#define MAP_HEIGHT 7

void render_scene(SDL_Renderer *renderer, float posX, float posY, float dirX, float dirY, float planeX, float planeY);

#endif /* RAYCASTING_H */

