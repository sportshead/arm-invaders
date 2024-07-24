#include "lfb.h"
#include "uart.h"

void main() {
  // set up serial console
  uart_init();
  uart_printf("Hello World! %d\n", 123);
  lfb_init();

  lfb_print(0, 0, "HELLO WORLD?", 0xFFFFFF);

  lfb_print(0, 8, "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789 <>=*?-", 0xFFFFFF);
  lfb_print(0, 24, "RED", 0xFF0000);
  lfb_print(4 * 8, 24, "GREEN", 0x00FF00);
  lfb_print(10 * 8, 24, "BLUE", 0x0000FF);

  lfb_print(0, 68, "IN THE MIDDLE OF THE SCREEN AND WITH WRAPPING AS WELL",
            0xFFFFFF);

  lfb_print(30, 140, "LEFT MARGIN\nIS RESPECTED", 0xFFFFFF);

  lfb_print(0, 160, "CARRIAGE RETURN\rOVERWRITES", 0xFFFFFF);

  lfb_print(0, 256 - 8,
            "THIS TEXT IS GOING TO GO OFF THE SCREEN BECAUSE IT IS TOO LONG",
            0xFFFFFF);
  lfb_print(0, 300, "THIS TEXT WONT BE PRINTED", 0xFFFFFF);
  uart_puts("No segfault!\n");

  // echo everything back
  while (1) {
    uart_send(uart_getc());
  }
}
