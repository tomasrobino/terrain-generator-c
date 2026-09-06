#include <stdint.h>
#include "generation.h"
#include "stb_image_write.h"

#define HEIGHT 20
#define WIDTH 20
#define PIXEL_AMOUNT (HEIGHT*WIDTH*0.4)

int main(void) {
    uint8_t matrix[HEIGHT][WIDTH] = {0};
    diffusion_limited_aggregation(WIDTH, HEIGHT, matrix, PIXEL_AMOUNT);
    uint8_t greyscale_matrix[WIDTH][HEIGHT];
    binary_colors_matrix(WIDTH, HEIGHT, matrix, greyscale_matrix);
    save_pgm("output.pgm", WIDTH, HEIGHT, greyscale_matrix);


    uint8_t matrix_3d[WIDTH][HEIGHT][3];
    direction_colors_matrix(WIDTH, HEIGHT, matrix, matrix_3d);
    stbi_write_bmp("output_3d.png", WIDTH, HEIGHT, 3, matrix_3d);
}
