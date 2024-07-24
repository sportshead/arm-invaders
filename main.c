#include "lfb.h"
#include "uart.h"

void main() {
  // set up serial console
  uart_init();
  lfb_init();

  lfb_showpicture();

  uart_puts("Image displayed\n");

  // echo everything back
  while (1) {
    uart_send(uart_getc());
  }
}
