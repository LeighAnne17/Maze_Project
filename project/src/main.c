#include <SDL2/SDL.h>
#include <stdio.h>
#include "raycasting.h"

// Function prototypes
void handle_input(int *quit, float *dirX, float *dirY, float *planeX, float *planeY);

int main(void)
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int quit = 0;
    SDL_Event event;

     // Camera parameters
    float posX = 3.0, posY = 3.0; // Starting position
    float dirX = -1.0, dirY = 0.0; // Initial direction
    float planeX = 0.0, planeY = 0.66; // Camera plane

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

    // Main game loop
    while (!quit)
    {
        handle_input(&quit, &dirX, &dirY, &planeX, &planeY);

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
void handle_input(int *quit, float *dirX, float *dirY, float *planeX, float *planeY)
{
    SDL_Event event;
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
            }
        }
    }
}
