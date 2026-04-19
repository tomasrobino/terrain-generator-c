//
// Created by Tomas on 19/4/2026.
//

#ifndef TERRAIN_GENERATION_C_GENERATION_H
#define TERRAIN_GENERATION_C_GENERATION_H

#include <stdint.h>

/**
 *
 * @param width Width of the matrix
 * @param height Height of the matrix
 * @param matrix Empty stack-allocated matrix to apply DLA to
 * @param pixel_amount
 */
void diffusion_limited_aggregation(uint32_t width, uint32_t height, uint8_t matrix[height][width], uint32_t pixel_amount);

#endif //TERRAIN_GENERATION_C_GENERATION_H