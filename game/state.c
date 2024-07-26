#include "game/state.h"
#include "graphics/lfb.h"

State state = {
    NO_PLAYER,
    true, // P2 score (0000) is displayed in main menu
};

char number[5] = {};
void format_number(int n) {
  number[0] = '0' + (n / 1000) % 10;
  number[1] = '0' + (n / 100) % 10;
  number[2] = '0' + (n / 10) % 10;
  number[3] = '0' + (n) % 10;
}

void update_state() {
  format_number(state.score_p1);
  lfb_print(8 * 3, 16, number, 0xFFFFFF);

  format_number(state.high_score);
  // this would be centred properly if it was 8 * 12
  // but the original is off centre /shrug
  lfb_print(8 * 11, 16, number, 0xFFFFFF);

  if (state.two_players) {
    format_number(state.score_p2);
  } else {
    number[0] = ' ';
    number[1] = ' ';
    number[2] = ' ';
    number[3] = ' ';
  }
  lfb_print(8 * 21, 16, number, 0xFFFFFF);

  format_number(state.credits);
  lfb_print(8 * 23, 256 - 8 - 4, &number[2], 0xFFFFFF); // credit is two digit

  if (state.player != NO_PLAYER) {
    number[3] = '0' + state.lives % 10;
    lfb_print(8, 256 - 8 - 4, &number[3], 0xFFFFFF);
  }
}

void init_state() {
  lfb_print(8, 4, "SCORE<1> HI-SCORE SCORE<2>", 0xFFFFFF);
  lfb_print(8 * 16, 256 - 8 - 4, "CREDIT", 0xFFFFFF);

  update_state();
}
