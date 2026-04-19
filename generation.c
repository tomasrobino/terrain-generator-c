//
// Created by Tomas on 19/4/2026.
//

#include "generation.h"
#include <stdlib.h>

void diffusion_limited_aggregation(const uint32_t width, const uint32_t height, uint8_t matrix[height][width], const uint32_t pixel_amount) {
    // Root, 5 means no attachment direction
    matrix[arc4random_uniform(height)][arc4random_uniform(width)] = 5;

    for (uint32_t i = 1; i < pixel_amount; ++i) {
        uint32_t y_coord = arc4random_uniform(height);
        uint32_t x_coord = arc4random_uniform(width);
        // Ensure generated pixel spawns in empty space
        while (matrix[y_coord][x_coord] != 0) {
            y_coord = arc4random_uniform(height);
            x_coord = arc4random_uniform(width);
        }

        // Loop until attaching to something
        while (matrix[y_coord][x_coord] == 0) {
            const uint8_t up = matrix[y_coord+1][x_coord];
            const uint8_t right = matrix[y_coord][x_coord+1];
            const uint8_t down = matrix[y_coord-1][x_coord];
            const uint8_t left = matrix[y_coord][x_coord-1];


            if (up == 0 && right == 0 && down == 0 && left == 0) {
                // 1 up, 2 right, 3 down, 4 left
                const uint8_t direction = arc4random_uniform(4) + 1;
                switch (direction) {
                    case 1:
                        y_coord++;
                        break;
                    case 2:
                        x_coord++;
                        break;
                    case 3:
                        y_coord--;
                        break;
                    case 4:
                        x_coord--;
                        break;
                    default: return;
                }
            } else {
                // Fixing pixel
                if (up != 0) {
                    matrix[y_coord][x_coord] = 1;
                } else if (right != 0) {
                    matrix[y_coord][x_coord] = 2;
                } else if (down != 0) {
                    matrix[y_coord][x_coord] = 3;
                } else {
                    matrix[y_coord][x_coord] = 4;
                }
            }
        }
    }
}
