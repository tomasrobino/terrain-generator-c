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
 */
void diffusion_limited_aggregation(uint64_t width, uint64_t height, uint64_t matrix[height][width]);

#endif //TERRAIN_GENERATION_C_GENERATION_H