#include <stdint.h>
#include "generation.h"

#define HEIGHT 20
#define WIDTH 20
#define PIXEL_AMOUNT (HEIGHT*WIDTH*0.4)

int main(void) {
    uint8_t matrix[HEIGHT][WIDTH] = {0};
    diffusion_limited_aggregation(WIDTH, HEIGHT, matrix, PIXEL_AMOUNT);
    binary_colors_matrix(WIDTH, HEIGHT, matrix);
    save_pgm("output.pgm", WIDTH, HEIGHT, matrix);
}
