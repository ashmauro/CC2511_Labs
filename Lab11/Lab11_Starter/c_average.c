#include "pico/stdlib.h"
#include <math.h>

int q = 7; // power

uint32_t c_average(uint32_t Q, uint32_t* values) {
  /* TODO - calculate average of the 2^Q unsigned integers in values[] */

  uint64_t sum = 0;
  uint32_t n = (1<<q);

  for (uint32_t i = 0; i <= n; i++) {
    sum += values[i]; // Add values to the sum
  }
  return sum / n;
}
