/**************************************************************
 * main.c
 * rev 1.0 24-Sep-2021 ashle
 * Lab9
 * ***********************************************************/

#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdio.h>
#include "hardware/adc.h"
// #include "hardware/irq.h"

#define RED_LED             11
#define GREEN_LED           12
#define BLUE_LED            13
#define LDR_PIN             26

int time_step = 50;
absolute_time_t rising_time;
absolute_time_t falling_time;
int time_on = 0;
uint16_t previous = 0;
uint16_t current = 0;

void time(int time_step){

    gpio_put(RED_LED, true);
    gpio_put(GREEN_LED, true);
    gpio_put(BLUE_LED, true);

    sleep_ms(time_step);

    gpio_put(RED_LED, false);
    gpio_put(GREEN_LED, false);
    gpio_put(BLUE_LED, false);

    sleep_ms(time_step);

}

int main(void) {

  stdio_init_all();
  adc_init();

   // Initialise Pins
  gpio_init(RED_LED);
  gpio_init(GREEN_LED);
  gpio_init(BLUE_LED);
  adc_gpio_init(LDR_PIN);

  // Set pin directions
  gpio_set_dir(RED_LED, true);
  gpio_set_dir(GREEN_LED, true);
  gpio_set_dir(BLUE_LED, true);

  // ADC INPUT
  adc_select_input(0);

  while (true) {

    time(time_step);

    // current = adc_read();
    // previous = current;


    // while (!((current - previous) > 1250)) {
    //    current = adc_read();
    // }

    // rising_time = get_absolute_time();
    // previous = current;

    // while (!((previous - current) > 1250)) {
    //    current = adc_read();
    // }

    // falling_time = get_absolute_time();
    // time_on = absolute_time_diff_us(rising_time, falling_time) / 1000;
    // printf("Pulse Width: %i\r\n", time_on);

    int ch = getchar_timeout_us(0);
    if (ch != PICO_ERROR_TIMEOUT) {
      switch (ch) {

        case 'a':
          time_step = 40; // 40ms
        break;

        case 's':
          time_step = 50; // 50 ms
        break;

        case 'd':
          time_step = 60; // 50 ms
        break;

        case 'e':
          time_step = 500; // 500 ms
        break;
      }
    }
  }
}
