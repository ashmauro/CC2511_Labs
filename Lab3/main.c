/**************************************************************
 * main.c
 * rev 1.0 13-Aug-2021 ashle
 * Lab3
 * ***********************************************************/

#include <stdbool.h>

// Register bases
#define SIO_BASE 0xd0000000
#define PAD_BASE 0x4001c000
#define CTRL_BASE 0x40014000

// Register offsets
#define REG_GPIO_OE_SET (SIO_BASE+0x024)
#define GPIO_OUT_SET (SIO_BASE+0x014)
#define GPIO_OUT_CLR (SIO_BASE+0x018)
#define GPIO_PAD (PAD_BASE+0x068)
#define GPIO_CTRL (CTRL_BASE+0x0cc)
#define LED_PIN       25 // GPIO pin 25

// Define 32 bit unsigned integer
typedef unsigned long uint32_t;
#define CONTENT_OF(addr) (*(volatile uint32_t*)addr)

int main(void) {

  // Turn off Output and turn on input
  CONTENT_OF(GPIO_PAD) = (CONTENT_OF(GPIO_PAD) & ~(1<<7) | (1<<6));
  // Function 5
  CONTENT_OF(GPIO_CTRL) = 5;
  // Data direction
  CONTENT_OF(REG_GPIO_OE_SET) = (1<<25);

  while (true) {

    // turn LED on
    CONTENT_OF(GPIO_OUT_SET) = (1<<25);
    
    // wait a while
    for (uint32_t i = 0; i < 800000; i++) {
      __asm volatile ("nop");
    }
    // turn LED off
    CONTENT_OF(GPIO_OUT_CLR) = (1<<25);
    
    // wait a while
    for (uint32_t i = 0; i < 800000; i++) {
      __asm volatile ("nop");
    }
  }
}
