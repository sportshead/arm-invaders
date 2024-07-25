#include "game/state.h"
#include "graphics/lfb.h"

State state = {
    NO_PLAYER, 0, 0, 0, 0, 0,
};

void init_state() {
  lfb_print(0, 0, "SCORE<1> HI-SCORE SCORE<2>", 0xFFFFFF);
  lfb_print(0, 256, "CREDIT", 0xFFFFFF);
}
