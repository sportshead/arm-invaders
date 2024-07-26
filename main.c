#include "game/state.h"
#include "graphics/lfb.h"
#include "hardware/uart.h"

void main() {
  // set up serial console
  uart_init();
  lfb_init();

  init_state();

  // echo everything back
  while (1) {
    uart_send(uart_getc());
    state.score_p1 += 10;
    update_state();
  }
}
