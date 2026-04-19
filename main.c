#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include "generation.h"

int main(void) {
    uint64_t matrix[100][100] = {0};
    diffusion_limited_aggregation(100, 100, matrix);
}
