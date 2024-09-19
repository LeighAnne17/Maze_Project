 // src/raycasting.c
#include "raycasting.h"
#include <math.h>
#include <SDL2/SDL.h>

SDL_Texture *load_texture(const char *file, SDL_Renderer *renderer)
{
   SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(file));
    if (!texture)
    {
        printf("Error loading texture: %s\n", SDL_GetError());
    }
    return texture;
}

int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1},
};

void render_scene(SDL_Renderer *renderer, float posX, float posY, float dirX, float dirY, float planeX, float planeY)
{
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255); // Sky blue for ceiling
    SDL_RenderClear(renderer);  // Clear screen (ceiling color)

    // Variables for raycasting
    float posX = 3.0, posY = 3.0;  // Player starting position
    float dirX = -1.0, dirY = 0.0; // Player direction (facing left)
    float planeX = 0.0, planeY = 0.66; // Camera plane (FOV)

    // Loop through each vertical stripe (one for each column)
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        float cameraX = 2 * x / (float)SCREEN_WIDTH - 1;
        float rayDirX = dirX + planeX * cameraX;
        float rayDirY = dirY + planeY * cameraX;

        // Current position in the map
        int mapX = (int)posX;
        int mapY = (int)posY;

        // Length of ray from current position to next x or y-side
        float sideDistX;
        float sideDistY;

        // Length of ray from one x or y-side to next x or y-side
        float deltaDistX = fabs(1 / rayDirX);
        float deltaDistY = fabs(1 / rayDirY);
        float perpWallDist;

        // Step direction and initial sideDist
        int stepX, stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (posX - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - posX) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (posY - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - posY) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if (worldMap[mapY][mapX] > 0)
                hit = 1;
        }

        if (side == 0)
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

	 // Calculate the distance to the wall
        if (side == 0)
            perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
        else
            perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

        // Calculate height of line to draw
        int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

        // Calculate lowest and highest pixel to fill in the current stripe
        int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
        if (drawEnd >= SCREEN_HEIGHT)
            drawEnd = SCREEN_HEIGHT - 1;

	  // Load textures based on the wall side
        SDL_Texture *texture;
        if (side == 0)  // NORTH/SOUTH facing walls
        {
            texture = load_texture("assets/textures/wallN.bmp", renderer);
        }
        else  // EAST/WEST facing walls
        {
            texture = load_texture("assets/textures/wallE.bmp", renderer);
        }

        // Set up the texture rect
        SDL_Rect srcRect = {0, 0, TEXTURE_WIDTH, TEXTURE_HEIGHT};  // Assume texture dimensions
        SDL_Rect destRect = {x, drawStart, 1, lineHeight};

        // Draw the texture
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect);

        // Clean up texture (optional, you may want to store it if reused)
        SDL_DestroyTexture(texture);
    }

    // Clear with the sky color
    SDL_SetRenderDrawColor(renderer, 135, 206, 235, 255);
    SDL_RenderClear(renderer);

    // Draw ground texture
    SDL_Rect groundRect = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2};
    SDL_RenderCopy(renderer, groundTexture, NULL, &groundRect);

        // Choose color based on side
	if (side == 1)  // NORTH/SOUTH facing walls
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Red for NORTH/SOUTH
        }
        else  // EAST/WEST facing walls
        {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for EAST/WEST
	}

        // Draw the vertical line for the wall
        SDL_RenderDrawLine(renderer, x, drawStart, x, drawEnd);
    }

    // Ground color
    SDL_SetRenderDrawColor(renderer, 60, 179, 113, 255);  // Greenish for ground
    SDL_RenderPresent(renderer);
}

