// already knew
#define WALK_CUT    0
#define JUST_WALK    1
#define OBSTACLE   2
#define VISITED     3

// info taken from web portal
#define BLOCK_SIZE   0.3 // diameter of the cutter (30 cm)
#define HEIGHT 20 
#define WIDTH  20 // terrain dimensions (20 x 20 m)

// info calculated
#define LINES (const __uint16_t) (WIDHT/BLOCK_SIZE) // number of blocks sized BLOCK_SIZE in the terrain width
#define COLUMNS (const __uint16_t) (HEIGHT/BLOCK_SIZE) // number of blocks sized BLOCK_SIZE in the terrain height
#define X_INIT LINHAS - 1 
#define Y_INIT COLUNAS - 1 // initial position


class PositionNode;