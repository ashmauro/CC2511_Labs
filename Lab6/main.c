/**************************************************************
 * main.c
 * rev 1.0 03-Sep-2021 ashle
 * Lab6
 * ***********************************************************/

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdio.h>

// Define gpio pins for LEDS
#define STEP 14
#define DIR 15

// Function to set LED pins to boolean variables
void set_pins(bool step, bool dir) {
  gpio_put(STEP, step);
  gpio_put(DIR, dir);
}

int main(void) {

    stdio_init_all();

    // Declare boolean variable
    bool step, dir = false;

    // Initialise gpio pins
    gpio_init(STEP);
    gpio_init(DIR);

    // Initialise gpio direction
    gpio_set_dir(STEP, true);
    gpio_set_dir(DIR, true);

    // bool s = false;

  while (true) {
     
      // sleep_ms(200);
    // set_pins(step, dir); // Call pin boolean function
    
    int ch = getchar_timeout_us(0);
    if (ch != PICO_ERROR_TIMEOUT) {
      switch (ch) {

        case 's':
          printf("STEP toggled\r\n");
           step = !step;
           gpio_put(STEP,step); // toggle LED to the opposit it is currently
        break;

        case 'd':
          printf("DIRECTION toggled\r\n");
          dir =! dir; // toggle LED to the opposit it is currently
          gpio_put(DIR, dir);
        break;

      }
    }
    sleep_us(10);
  }
}
