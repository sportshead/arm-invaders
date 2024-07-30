#define WIDTH 224
#define HEIGHT 256

#define REAL_WIDTH 480
#define REAL_HEIGHT 320

#define X_OFFSET (REAL_WIDTH - WIDTH) / 2
#define Y_OFFSET (REAL_HEIGHT - HEIGHT) / 2

void lfb_init();
void lfb_sprite(int x, int y, int width, int height, char *sprite,
                unsigned int color);
void lfb_print(int x, int y, char *s, unsigned int color);
