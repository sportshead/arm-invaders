#include "game/state.h"
#include "graphics/lfb.h"
#include "graphics/sprites.h"
#include "hardware/uart.h"

void main() {
  // set up serial console
  uart_init();
  uart_puts("\n\n");
  uart_puts("\x1b]1337;SetMark\x07"); // iterm marker
  uart_puts("------------------------\n");
  uart_puts("      ARM-INVADERS      \n");
  uart_puts("------------------------\n");

  lfb_init();

  init_state();

  draw_shield(3 * 8, 12 * 16, 0x00FF00);
  draw_shield(9 * 8, 12 * 16, 0x00FF00);
  draw_shield(15 * 8, 12 * 16, 0x00FF00);
  draw_shield(21 * 8, 12 * 16, 0x00FF00);

  // echo everything back
  while (1) {
    uart_send(uart_getc());
    state.score_p1 += 10;
    update_state();
  }
}
