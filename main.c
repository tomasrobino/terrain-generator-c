#include <stdint.h>
#include "generation.h"

int main(void) {
    uint8_t matrix[100][100] = {0};
    diffusion_limited_aggregation(100, 100, matrix, 100);
}
