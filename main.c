#include "lfb.h"
#include "uart.h"

void main() {
  // set up serial console
  uart_init();
  lfb_init();

  lfb_print(0, 0, "HELLO WORLD?", 0xFFFFFF);

  lfb_print(0, 8, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 <>=*?-", 0xFFFFFF);

  // echo everything back
  while (1) {
    uart_send(uart_getc());
  }
}
