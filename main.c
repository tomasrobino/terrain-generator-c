#include <stdint.h>
#include "generation.h"

int main(void) {
    uint8_t matrix[20][20] = {0};
    diffusion_limited_aggregation(20, 20, matrix, 100);
}
