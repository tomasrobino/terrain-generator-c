#include <stdint.h>
#include "generation.h"

#define HEIGHT 20
#define WIDTH 20

int main(void) {
    uint8_t matrix[HEIGHT][WIDTH] = {0};
    diffusion_limited_aggregation(WIDTH, HEIGHT, matrix, 100);
    binary_colors_matrix(WIDTH, HEIGHT, matrix);
    save_pgm("output.pgm", WIDTH, HEIGHT, matrix);
}
