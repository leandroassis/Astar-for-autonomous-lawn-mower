
class PositionNode {
    public:
        __uint16_t x; // map position
        __uint16_t y;
        __uint8_t status; // 0 = visitable and cutable, 1 = visitable and not cutable, 2 = not visitable, 3 = visited

    
        // costs
        __uint16_t g; // cost from start to current node
        __uint16_t h; // cost from current node to end
        __uint16_t f; // g + h
};