/**************************************************************
 * main.c
 * rev 1.0 27-Aug-2021 ashle
 * Lab5
 * ***********************************************************/

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdio.h>
#include "hardware/pwm.h"

#define CONTENT_OF(addr)        (*(volatile uint32_t*)addr)
#define PAD_CONTROL_BASE         0x4001c000
#define REG_PAD_CONTROL_GPIO15  (PAD_CONTROL_BASE+0x40)
#define CTRL_PDE                0x4
#define CTRL_PUE                0x8
#define BLUE_LED                12
#define RED_LED                 11
#define GREEN_LED               13
#define INPUT_PIN               15

// void set_LED(int red_value, int green_value) {
//   pwm_set_gpio_level(RED_LED, red_value);
//   pwm_set_gpio_level(GREEN_LED, green_value);
// }

int main(void) {

  // Initialise library
  stdio_init_all();

  //  Set PUE and PDE both to off
  CONTENT_OF(REG_PAD_CONTROL_GPIO15) = CONTENT_OF(REG_PAD_CONTROL_GPIO15) & ~((1<<3) | (1<<2));

  // Declare new integer values
  int red_value, green_value;
  int DELTA;

  // Set new value to 0
  red_value = 1;
  green_value = 1;
  DELTA = 25;

  // Initialise Pins
  gpio_init(BLUE_LED);
  gpio_init(INPUT_PIN);
  gpio_init(RED_LED);
  gpio_init(GREEN_LED);

  // Set pin directions
  gpio_set_dir(BLUE_LED, true);
  gpio_set_dir(RED_LED, true);
  gpio_set_dir(GREEN_LED, true);
  gpio_set_dir(INPUT_PIN, false);

  // Set gpio function 
  gpio_set_function(RED_LED, GPIO_FUNC_PWM);
  gpio_set_function(GREEN_LED, GPIO_FUNC_PWM);

  // Slice number
  uint redslice_num = pwm_gpio_to_slice_num(RED_LED);
  uint greenslice_num = pwm_gpio_to_slice_num(GREEN_LED);

  // Enable
  pwm_set_enabled(redslice_num, true);
  pwm_set_enabled(greenslice_num, true);

  while (true) {
    
    // set_LED(red_value, green_value);

    gpio_put(BLUE_LED, gpio_get(INPUT_PIN));

    int ch = getchar_timeout_us(0);
    if (ch != PICO_ERROR_TIMEOUT) {
      switch (ch) {

        case 'u':
          printf("Pin 15 to pullup\r\n");
          CONTENT_OF(REG_PAD_CONTROL_GPIO15) = (CONTENT_OF(REG_PAD_CONTROL_GPIO15) & ~(1<<2)) | (1<<3);
        break;

        case 'd':
          printf("Pin 15 to pulldown\r\n");
          CONTENT_OF(REG_PAD_CONTROL_GPIO15) = (CONTENT_OF(REG_PAD_CONTROL_GPIO15) & ~(1<<3)) | (1<<2);
        break;

        case 'o':
          printf("Pin 15 to pull none\r\n");
          CONTENT_OF(REG_PAD_CONTROL_GPIO15) = CONTENT_OF(REG_PAD_CONTROL_GPIO15) & ~((1<<3) | (1<<2));
        break;

        case 'r':
          red_value += DELTA;
          if (red_value > 255) {
            red_value = 0;
          }
          pwm_set_gpio_level(RED_LED, red_value*red_value);
          printf("Red = %d\r\n", red_value);
        break;

         case 'R':
          red_value -= DELTA;
          if (red_value < 0) {
            red_value = 255;
          }
          pwm_set_gpio_level(RED_LED, red_value*red_value);
          printf("Red = %d\r\n", red_value);
        break;
        
        case 'g':
          green_value += DELTA;
           if (green_value > 255) {
            green_value = 0;
          }
          pwm_set_gpio_level(GREEN_LED, green_value*green_value);
          printf("Green = %d\r\n", green_value);
        break;

         case 'G':
          green_value -= DELTA;
           if (red_value < 0) {
            green_value = 255;
          }
          pwm_set_gpio_level(GREEN_LED, green_value*green_value);
          printf("Green = %d\r\n", green_value);
        break;
      }
    }

    sleep_us(1);

  }

}
