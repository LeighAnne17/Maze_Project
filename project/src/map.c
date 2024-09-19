#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "raycasting.h"

int load_map(const char *filename, char worldMap[MAP_WIDTH][MAP_HEIGHT])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open map file %s\n", filename);
        return 0;
    }

    char line[MAP_WIDTH + 2]; // Add 2 for the newline and null terminator
    int row = 0;

    while (fgets(line, sizeof(line), file) && row < MAP_HEIGHT)
    {
        // Ensure the line length matches the expected map width
        if (strlen(line) >= MAP_WIDTH)
        {
            // Copy the line into the map array (ignore newline)
            strncpy(worldMap[row], line, MAP_WIDTH);
            row++;
        }
    }

    fclose(file);

    // Ensure that the map is fully loaded
    if (row != MAP_HEIGHT)
    {
        printf("Error: Map file %s has incorrect dimensions\n", filename);
        return 0;
    }

    return 1;
}

