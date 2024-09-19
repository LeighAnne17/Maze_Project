#ifndef RAYCASTING_H
#define RAYCASTING_H

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 10
#define MAP_HEIGHT 8

SDL_Texture *load_texture(const char *file, SDL_Renderer *renderer);
void render_scene(SDL_Renderer *renderer, float posX, float posY, float dirX, float dirY, float planeX, float planeY, char worldMap[MAP_WIDTH][MAP_HEIGHT]);
int load_map(const char *filename, char worldMap[MAP_WIDTH][MAP_HEIGHT]);
void draw_map(SDL_Renderer *renderer, char worldMap[MAP_WIDTH][MAP_HEIGHT], float posX, float posY, float dirX, float dirY);

#endif /* RAYCASTING_H */

