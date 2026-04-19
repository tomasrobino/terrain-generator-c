//
// Created by Tomas on 19/4/2026.
//

#ifndef TERRAIN_GENERATION_C_GENERATION_H
#define TERRAIN_GENERATION_C_GENERATION_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void binary_colors_matrix(uint32_t width, uint32_t height, uint8_t matrix[height][width]);

void save_pgm(const char *filename, uint32_t width, uint32_t height, uint8_t matrix[height][width]);

void print_matrix(uint32_t width, uint32_t height, uint8_t matrix[height][width]);

/**
 *
 * @param width Width of the matrix
 * @param height Height of the matrix
 * @param matrix Empty stack-allocated matrix to apply DLA to
 * @param pixel_amount
 */
void diffusion_limited_aggregation(uint32_t width, uint32_t height, uint8_t matrix[height][width], uint32_t pixel_amount);

#endif //TERRAIN_GENERATION_C_GENERATION_H