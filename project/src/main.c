#include <SDL2/SDL.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "raycasting.h"

// Function prototypes
void handle_input(int *quit, float *posX, float *posY, float *dirX, float *dirY, float *planeX, float *planeY, char worldMAP[MAP_WIDTH][MAP_HEIGHT])
{
	SDL_Event event;
    const float moveSpeed = 0.1; // Adjust movement speed as needed
    const float rotationSpeed = 0.05; // Adjust rotation speed as needed
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            *quit = 1;
        }
    }

    // Rotation
    if (state[SDL_SCANCODE_LEFT]) {
        // Rotate left
        *dirX = *dirX * cos(rotationSpeed) - *dirY * sin(rotationSpeed);
        *dirY = *dirX * sin(rotationSpeed) + *dirY * cos(rotationSpeed);
        *planeX = *planeX * cos(rotationSpeed) - *planeY * sin(rotationSpeed);
        *planeY = *planeX * sin(rotationSpeed) + *planeY * cos(rotationSpeed);
    }
    if (state[SDL_SCANCODE_RIGHT]) {
        // Rotate right
        *dirX = *dirX * cos(-rotationSpeed) - *dirY * sin(-rotationSpeed);
        *dirY = *dirX * sin(-rotationSpeed) + *dirY * cos(-rotationSpeed);
        *planeX = *planeX * cos(-rotationSpeed) - *planeY * sin(-rotationSpeed);
        *planeY = *planeX * sin(-rotationSpeed) + *planeY * cos(-rotationSpeed);
    }

    // Movement
    if (state[SDL_SCANCODE_W]) {
        if (worldMap[(int)(*posX + *dirX * moveSpeed)][(int)(*posY)] == '0')
            *posX += *dirX * moveSpeed;
        if (worldMap[(int)(*posX)][(int)(*posY + *dirY * moveSpeed)] == '0')
            *posY += *dirY * moveSpeed;
    }
    if (state[SDL_SCANCODE_S]) {
        if (worldMap[(int)(*posX - *dirX * moveSpeed)][(int)(*posY)] == '0')
            *posX -= *dirX * moveSpeed;
        if (worldMap[(int)(*posX)][(int)(*posY - *dirY * moveSpeed)] == '0')
            *posY -= *dirY * moveSpeed;
    }
    if (state[SDL_SCANCODE_A]) {
        if (worldMap[(int)(*posX - *planeX * moveSpeed)][(int)(*posY)] == '0')
            *posX -= *planeX * moveSpeed;
        if (worldMap[(int)(*posX)][(int)(*posY - *planeY * moveSpeed)] == '0')
            *posY -= *planeY * moveSpeed;
    }
    if (state[SDL_SCANCODE_D]) {
        if (worldMap[(int)(*posX + *planeX * moveSpeed)][(int)(*posY)] == '0')
            *posX += *planeX * moveSpeed;
        if (worldMap[(int)(*posX)][(int)(*posY + *planeY * moveSpeed)] == '0')
            *posY += *planeY * moveSpeed;
    }
}
int load_map(const char *filename, char worldMap[MAP_WIDTH][MAP_HEIGHT]);

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		printf("Usage: %s <map_file>\n", argv[0]);
		return 1;
	}


    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int quit = 0;

     // Camera parameters
    float posX = 3.0, posY = 3.0; // Starting position
    float dirX = -1.0, dirY = 0.0; // Initial direction
    float planeX = 0.0, planeY = 0.66; // Camera plane

    // World map
    char worldMap[MAP_WIDTH][MAP_HEIGHT];

    if (!load_map(argv[1], worldMap))
    {
	    printf("Failed to load map from %s\n", argv[1]);
	    return 1;
    }

     // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create window
    window = SDL_CreateWindow("Raycasting Demo",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create renderer for window
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

     char worldMap[MAP_WIDTH][MAP_HEIGHT];
    if (argc < 2 || !load_map(argv[1], worldMap))
    {
        return 1; // Exit if map loading fails or no file is specified
    }

    // Main game loop
    while (!quit)
    {
        handle_input(&quit, &posX, &posY, &dirX, &dirY, &planeX, &planeY, worldMap);

        // Render scene
        render_scene(renderer, posX, posY, dirX, dirY, planeX, planeY);

        // Update screen
        SDL_RenderPresent(renderer);

        // Delay to limit frame rate
        SDL_Delay(16); // Approximately 60 FPS
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

// Handle keyboard input for rotation
void handle_input(int *quit, float *posX, float *posY, float *dirX, float *dirY, float *planeX, float *planeY, char worldMap[MAP_WIDTH][MAP_HEIGHT])
{
    SDL_Event event;
    const float moveSpeed = 0.1; // Adjust movement speed as needed
    const float rotationSpeed = 0.05; // Adjust rotation speed as needed

    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
        {
            *quit = 1;
        }

        if (event.type == SDL_KEYDOWN)
        {
            float oldDirX, oldPlaneX;

            switch (event.key.keysym.sym)
            {
                case SDLK_LEFT:
                    // Rotate left
                    oldDirX = *dirX;
                    *dirX = *dirX * cos(rotationSpeed) - *dirY * sin(rotationSpeed);
                    *dirY = oldDirX * sin(rotationSpeed) + *dirY * cos(rotationSpeed);
                    oldPlaneX = *planeX;
                    *planeX = *planeX * cos(rotationSpeed) - *planeY * sin(rotationSpeed);
                    *planeY = oldPlaneX * sin(rotationSpeed) + *planeY * cos(rotationSpeed);
                    break;

                case SDLK_RIGHT:
                    // Rotate right
                    oldDirX = *dirX;
                    *dirX = *dirX * cos(-rotationSpeed) - *dirY * sin(-rotationSpeed);
                    *dirY = oldDirX * sin(-rotationSpeed) + *dirY * cos(-rotationSpeed);
                    oldPlaneX = *planeX;
                    *planeX = *planeX * cos(-rotationSpeed) - *planeY * sin(-rotationSpeed);
                    *planeY = oldPlaneX * sin(-rotationSpeed) + *planeY * cos(-rotationSpeed);
                    break;

		    // Move forward
                case SDLK_w:
                    if (worldMap[(int)(*posX + *dirX * moveSpeed)][(int)(*posY)] == '0')
                        *posX += *dirX * moveSpeed;
                    if (worldMap[(int)(*posX)][(int)(*posY + *dirY * moveSpeed)] == '0')
                        *posY += *dirY * moveSpeed;
                    break;

                // Move backward
                case SDLK_s:
                    if (worldMap[(int)(*posX - *dirX * moveSpeed)][(int)(*posY)] == '0')
                        *posX -= *dirX * moveSpeed;
                    if (worldMap[(int)(*posX)][(int)(*posY - *dirY * moveSpeed)] == '0')
                        *posY -= *dirY * moveSpeed;
                    break;

                // Strafe left
                case SDLK_a:
                    if (worldMap[(int)(*posX - *planeX * moveSpeed)][(int)(*posY)] == '0')
                        *posX -= *planeX * moveSpeed;
                    if (worldMap[(int)(*posX)][(int)(*posY - *planeY * moveSpeed)] == '0')
                        *posY -= *planeY * moveSpeed;
                    break;

                // Strafe right
                case SDLK_d:
                    if (worldMap[(int)(*posX + *planeX * moveSpeed)][(int)(*posY)] == '0')
                        *posX += *planeX * moveSpeed;
                    if (worldMap[(int)(*posX)][(int)(*posY + *planeY * moveSpeed)] == '0')
                        *posY += *planeY * moveSpeed;
		    break;
            }
        }
    }
}
