//
// Created by Tomas on 19/4/2026.
//

#include "generation.h"


void binary_colors_matrix(const uint32_t width, const uint32_t height, uint8_t matrix[height][width], uint8_t new_matrix[height][width]) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (matrix[i][j] != 0) {
                new_matrix[i][j] = 255;
            } else new_matrix[i][j] = 0;
        }
    }
}

void direction_colors_matrix(const uint32_t width, const uint32_t height, uint8_t matrix[height][width], uint8_t matrix_3d[height][width][3]) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            switch (matrix[i][j]) {
                case 1: // up
                    matrix_3d[i][j][0] = 230;
                    matrix_3d[i][j][1] = 16;
                    matrix_3d[i][j][2] = 16;
                    break;
                case 2: // right
                    matrix_3d[i][j][0] = 7;
                    matrix_3d[i][j][1] = 230;
                    matrix_3d[i][j][2] = 18;
                    break;
                case 3: // down
                    matrix_3d[i][j][0] = 255;
                    matrix_3d[i][j][1] = 208;
                    matrix_3d[i][j][2] = 0;
                    break;
                case 4: // left
                    matrix_3d[i][j][0] = 0;
                    matrix_3d[i][j][1] = 28;
                    matrix_3d[i][j][2] = 186;
                    break;
                case 5: // root
                    matrix_3d[i][j][0] = 186;
                    matrix_3d[i][j][1] = 0;
                    matrix_3d[i][j][2] = 177;
                    break;
                case 0: // nothing
                    matrix_3d[i][j][0] = 0;
                    matrix_3d[i][j][1] = 0;
                    matrix_3d[i][j][2] = 0;
                    break;
                default:
                    printf("x: %d, y: %d, value: %d\n", i, j, matrix[i][j]);
            }
        }
    }
}


void save_pgm(const char *filename, uint32_t width, uint32_t height, uint8_t matrix[height][width]) {
    FILE *f = fopen(filename, "wb");
    if (!f) return;

    // Header
    fprintf(f, "P5\n%d %d\n255\n", width, height);

    // Raw pixel data
    fwrite(matrix, sizeof(unsigned char), width * height, f);

    fclose(f);
}


void print_matrix(uint32_t width, uint32_t height, uint8_t matrix[height][width]) {
    for (int k = 0; k < height; ++k) {
        printf("[");
        for (int j = 0; j < width; ++j) {
            switch (matrix[k][j]) {
                case 1:
                    printf("\033[31m%d\033[0m, ", matrix[k][j]);
                    break;
                case 2:
                    printf("\033[32m%d\033[0m, ", matrix[k][j]);
                    break;
                case 3:
                    printf("\033[33m%d\033[0m, ", matrix[k][j]);
                    break;
                case 4:
                    printf("\033[34m%d\033[0m, ", matrix[k][j]);
                    break;
                case 5:
                    printf("\033[35m%d\033[0m, ", matrix[k][j]);
                    break;
                default: printf("%d, ", matrix[k][j]);
            }
        }
        printf("],\n");
    }
    printf("--------------------------------\n\n\n");
}


void diffusion_limited_aggregation(const uint32_t width, const uint32_t height, uint8_t matrix[height][width], const uint32_t pixel_amount) {
    // Root, 5 means no attachment direction
    uint8_t h = arc4random_uniform(height);
    uint8_t w = arc4random_uniform(width);
    matrix[h][w] = 5;

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
            const uint8_t up = (y_coord > 0) ? matrix[y_coord - 1][x_coord] : 0;
            const uint8_t right = (x_coord + 1 < width) ? matrix[y_coord][x_coord + 1] : 0;
            const uint8_t down = (y_coord + 1 < height) ? matrix[y_coord + 1][x_coord] : 0;
            const uint8_t left = (x_coord > 0) ? matrix[y_coord][x_coord - 1] : 0;

            if (up == 0 && right == 0 && down == 0 && left == 0) {
                // 1 up, 2 right, 3 down, 4 left
                uint8_t possible_directions[4];
                uint8_t direction_count = 0;

                if (y_coord + 1 < height) {
                    possible_directions[direction_count++] = 1;
                }
                if (x_coord + 1 < width) {
                    possible_directions[direction_count++] = 2;
                }
                if (y_coord > 0) {
                    possible_directions[direction_count++] = 3;
                }
                if (x_coord > 0) {
                    possible_directions[direction_count++] = 4;
                }

                if (direction_count == 0) {
                    return;
                }

                const uint8_t direction = possible_directions[arc4random_uniform(direction_count)];
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
                    default:
                        return;
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
        print_matrix(width, height, matrix);
    }
}
