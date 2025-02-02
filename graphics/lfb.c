#include "graphics/lfb.h"
#include "graphics/font.h"
#include "hardware/delays.h"
#include "hardware/mbox.h"
#include "hardware/uart.h"

unsigned int pitch, isrgb; /* dimensions and channel order */
unsigned char *lfb;        /* raw frame buffer address */

void lfb_init() {
  /* newer qemu segfaults if we don't wait here a bit */
  wait_msec(100000);

  mbox[0] = 35 * 4;
  mbox[1] = MBOX_REQUEST;

  mbox[2] = 0x48003; // set phy wh
  mbox[3] = 8;
  mbox[4] = 8;
  mbox[5] = REAL_WIDTH;  // FrameBufferInfo.width
  mbox[6] = REAL_HEIGHT; // FrameBufferInfo.height

  mbox[7] = 0x48004; // set virt wh
  mbox[8] = 8;
  mbox[9] = 8;
  mbox[10] = REAL_WIDTH;  // FrameBufferInfo.virtual_width
  mbox[11] = REAL_HEIGHT; // FrameBufferInfo.virtual_height

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
  mbox[24] = 0; // RGB, not BGR preferably

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
    pitch = mbox[33];       // get number of bytes per line
    isrgb = mbox[24];       // get the actual channel order
    lfb = (void *)((unsigned long)mbox[28]);
    uart_printf("Framebuffer: %dx%d, pitch: %d, rgb: %d, ptr: 0x%08x\n",
                mbox[5], mbox[6], pitch, isrgb, lfb);
  } else {
    uart_puts("Unable to set screen resolution\n");
  }
}

#define BACKGROUND_COLOR 0x0
void lfb_sprite(const int x, const int y, const int w, const int h,
                char *sprite, const unsigned int color) {
  uart_printf("lfb_sprite(%d,%d,%d,%d,0x%08x,0x%08x)\n", x, y, w, h, sprite,
              color);

  int idx = 0;
  for (int j = 0; j < h; j++) {
    int offset = ((y + j + Y_OFFSET) * pitch) + ((x + X_OFFSET) * 4);
    for (int i = 0; i < w; i++) {
      for (int bit = 0; bit < 8; bit++) {
        if (sprite[idx] & (0b10000000 >> bit)) {
          *((unsigned int *)(lfb + offset)) = color;
        } else {
          *((unsigned int *)(lfb + offset)) = BACKGROUND_COLOR;
        }
        offset += 4;
      }
      idx++;
    }
  }
}

void draw_glyph(int x, int y, char (*glyph)[8], const unsigned int color) {
  int i, j;
  for (i = 0; i < 8; i++) {
    int offset = ((y + i + Y_OFFSET) * pitch) + ((x + X_OFFSET) * 4);
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
  unsigned int x = 0;
  unsigned int y = 0;
  while (*s) {
    if (y + Y >= HEIGHT) {
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
    } else if (*s == ' ') {
      glyph = &font_chars[42];
    } else if (*s == '\r') {
      x = -8;
    } else if (*s == '\n') {
      x = -8;
      y += 8;
    } else {
      uart_printf("Unknown character: %c (0x%02x)\n", *s, *s);
      // ignore error, keep going
    }
    if (glyph) {
      draw_glyph(x + X, y + Y, glyph, color);
    }

    x += 8;

    if (x + X >= WIDTH) {
      x = 0;
      y += 8;
    }
    s++;
  }
}
