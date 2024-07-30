#include "game/state.h"
#include "graphics/lfb.h"
#include "hardware/uart.h"

void main() {
  // set up serial console
  uart_init();
  uart_puts("\n\n");
  uart_puts("------------------------\n");
  uart_puts("      ARM-INVADERS      \n");
  uart_puts("------------------------\n");

  lfb_init();

  lfb_print(0, 0, "RED", 0xFF0000);
  // init_state();

  // echo everything back
  while (1) {
    uart_send(uart_getc());
    state.score_p1 += 10;
    // update_state();
  }
}
