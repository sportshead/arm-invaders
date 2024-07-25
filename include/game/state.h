typedef enum {
  NO_PLAYER = 0,
  P1 = 1,
  P2 = 2,
} Player;

typedef struct {
  Player player;
  int score_p1;
  int score_p2;
  int high_score;
  int lives;
  int credits;
} State;

extern State state;

void init_state();
void update_state();
