#include "graphics/font.h"
#include "hardware/delays.h"
#include "hardware/mbox.h"
#include "hardware/uart.h"

unsigned int width, height, pitch, isrgb; /* dimensions and channel order */
unsigned char *lfb;                       /* raw frame buffer address */

void lfb_init() {
  /* newer qemu segfaults if we don't wait here a bit */
  wait_msec(100000);

  mbox[0] = 35 * 4;
  mbox[1] = MBOX_REQUEST;

  mbox[2] = 0x48003; // set phy wh
  mbox[3] = 8;
  mbox[4] = 8;
  mbox[5] = 224; // FrameBufferInfo.width
  mbox[6] = 256; // FrameBufferInfo.height

  mbox[7] = 0x48004; // set virt wh
  mbox[8] = 8;
  mbox[9] = 8;
  mbox[10] = 224; // FrameBufferInfo.virtual_width
  mbox[11] = 256; // FrameBufferInfo.virtual_height

  mbox[12] = 0x48009; // set virt offset
  mbox[13] = 8;
  mbox[14] = 8;
  mbox[15] = 0; // FrameBufferInfo.x_offset
  mbox[16] = 0; // FrameBufferInfo.y.offset

  mbox[17] = 0x48005; // set depth
  mbox[18] = 4;
  mbox[19] = 4;
  mbox[20] = 32; // FrameBufferInfo.depth

  mbox[21] = 0x48006; // set pixel order
  mbox[22] = 4;
  mbox[23] = 4;
  mbox[24] = 1; // RGB, not BGR preferably

  mbox[25] = 0x40001; // get framebuffer, gets alignment on request
  mbox[26] = 8;
  mbox[27] = 8;
  mbox[28] = 4096; // FrameBufferInfo.pointer
  mbox[29] = 0;    // FrameBufferInfo.size

  mbox[30] = 0x40008; // get pitch
  mbox[31] = 4;
  mbox[32] = 4;
  mbox[33] = 0; // FrameBufferInfo.pitch

  mbox[34] = MBOX_TAG_LAST;

  // this might not return exactly what we asked for, could be
  // the closest supported resolution instead
  if (mbox_call(MBOX_CH_PROP) && mbox[20] == 32 && mbox[28] != 0) {
    mbox[28] &= 0x3FFFFFFF; // convert GPU address to ARM address
    width = mbox[5];        // get actual physical width
    height = mbox[6];       // get actual physical height
    pitch = mbox[33];       // get number of bytes per line
    isrgb = mbox[24];       // get the actual channel order
    lfb = (void *)((unsigned long)mbox[28]);
  } else {
    uart_puts("Unable to set screen resolution\n");
  }
}

#define BACKGROUND_COLOR 0x0
void draw_glyph(int x, int y, char (*glyph)[8], const unsigned int color) {
  int i, j;
  for (i = 0; i < 8; i++) {
    int offset = (y + i) * pitch + (x * 4) + 4;
    for (j = 0; j < 8; j++) {
      if ((*glyph)[i] & (0b10000000 >> j)) {
        *((unsigned int *)(lfb + offset)) = color;
      } else {
        *((unsigned int *)(lfb + offset)) = BACKGROUND_COLOR;
      }
      offset += 4;
    }
  }
}

/**
 * Display a string using the embedded bitmap font
 */
void lfb_print(const int X, const int Y, char *s, const unsigned int color) {
  int x, y = 0;
  while (*s) {
    if (y + Y >= height) {
      uart_printf("Ran out of space! Last char printed was %c at 0x%16x\n", *s,
                  s);
      uart_printf("(X,Y) = (%d,%d)\n", X, Y);
      uart_printf("(x,y) = (%d,%d)\n", x, y);

      return;
    }

    char(*glyph)[8] = 0x0;
    if (*s >= 'A' && *s <= 'Z') {
      glyph = &font_chars[*s - 'A'];
    } else if (*s >= '0' && *s <= '9') {
      glyph = &font_chars[*s - '0' + 26];
    } else if (*s >= '<' && *s <= '?') {
      glyph = &font_chars[*s - '<' + 36];
    } else if (*s == '*') {
      glyph = &font_chars[40];
    } else if (*s == '-') {
      glyph = &font_chars[41];
    } else if (*s == '\r') {
      x = -8;
    } else if (*s == '\n') {
      x = -8;
      y += 8;
    } else if (*s != ' ') {
      uart_printf("Unknown character: %c (0x%02x)\n", *s, *s);
      // ignore error, keep going
    }
    if (glyph) {
      draw_glyph(x + X, y + Y, glyph, color);
    }

    x += 8;

    if (x + X >= width) {
      x = 0;
      y += 8;
    }
    s++;
  }
}
