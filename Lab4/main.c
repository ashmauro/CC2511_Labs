/**************************************************************
 * main.c
 * rev 1.0 20-Aug-2021 ashle
 * Lab4
 * ***********************************************************/

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdio.h>

// Define gpio pins for LEDS
#define RED_LED 11
#define GREEN_LED 12
#define BLUE_LED 13

// Function to set LED pins to boolean variables
void set_pins(bool red, bool green, bool blue) {
  gpio_put(RED_LED, red);
  gpio_put(GREEN_LED, green);
  gpio_put(BLUE_LED, blue);
}

int main(void) {
  
  stdio_init_all();

  // Declare boolean variable
  bool red, green, blue; 

  // Set boolean variables to off
  red = false;
  green = false;
  blue = false;

  // Initialise gpio pins
  gpio_init(RED_LED);
  gpio_init(GREEN_LED);
  gpio_init(BLUE_LED);

  // Initialise gpio direction
  gpio_set_dir(RED_LED, true);
  gpio_set_dir(GREEN_LED, true);
  gpio_set_dir(BLUE_LED, true);

  while (true) {
    
    set_pins(red, green, blue); // Call pin boolean function
    
    int ch = getchar_timeout_us(0);
    if (ch != PICO_ERROR_TIMEOUT) {
      switch (ch) {

        case 'r':
          printf("Red LED toggled\r\n");
          // gpio_put(RED_LED, true);
          // gpio_put(RED_LED, !gpio_get(RED_LED));
          red =! red; // toggle LED to the opposit it is currently
        break;

        case 'g':
          printf("Green LED toggled\r\n");
          // gpio_put(GREEN_LED, true);
          // gpio_put(GREEN_LED, !gpio_get(GREEN_LED));
          green =! green; // toggle LED to the opposit it is currently
        break;

        case 'b':
          printf("Blue LED toggled\r\n");
          // gpio_put(BLUE_LED, true);
          // gpio_put(BLUE_LED, !gpio_get(BLUE_LED));
          blue =! blue; // toggle LED to the opposit it is currently
        break;

      }
    }

    sleep_us(10);

  }
}
