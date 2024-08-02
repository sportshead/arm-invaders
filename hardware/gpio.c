#include "hardware/gpio.h"
#include "game/state.h"
#include "hardware/uart.h"

#define MASK_2_7 0b11111100;
/**
 * Set all the pins we use to input, pulled up
 * Pins 2, 3, 4, 5, 6, 7
 */
void gpio_init() {
  register unsigned int r;
  r = *GPFSEL0;
  // clear bits 23:21, 20:18, 17:15, 14:12, 11:9, 8:6
  r &= ~((0b111 << 21) | (0b111 << 18) | (0b111 << 15) | (0b111 << 12) |
         (0b111 << 9) | (0b111 << 6));
  *GPFSEL0 = r;

  // set pull up
  *GPPUD = 0b10;
  r = 150;
  while (r--) {
    asm volatile("nop");
  }
  *GPPUDCLK0 = MASK_2_7;
  r = 150;
  while (r--) {
    asm volatile("nop");
  }

  *GPPUD = 0;
  *GPPUDCLK0 = 0;

  // event detection modes
  // enable rising edge
  r = *GPREN0;
  r |= MASK_2_7;
  *GPREN0 = r;

  // disable falling edge
  r = *GPFEN0;
  r &= ~MASK_2_7;
  *GPFEN0 = r;

  // disable high
  r = *GPHEN0;
  r &= ~MASK_2_7;
  *GPHEN0 = r;

  // disable low
  r = *GPLEN0;
  r &= ~MASK_2_7;
  *GPLEN0 = r;

  // disable async rising edge
  r = *GPAREN0;
  r &= ~MASK_2_7;
  *GPAREN0 = r;

  // disable async falling edge
  r = *GPAFEN0;
  r &= ~MASK_2_7;
  *GPFEN0 = r;
}

void gpio_tick() {
  if ((*GPEDS0 >> CREDIT_PIN) & 1) {
    uart_puts("Credit button pushed\n");
    state.credits++;
  }
}
