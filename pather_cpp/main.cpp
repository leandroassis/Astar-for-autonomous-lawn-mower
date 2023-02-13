#include <iostream>
#include <vector>
#include <header.hpp>

PositionNode map[LINES][COLUMNS] = {};
PositionNode *actual_pos = &map[X_INIT][Y_INIT];

int main(){ 

    __uint16_t i, j;

    for(i = 0; i < LINES; i++){
        for(j = 0; j < COLUMNS; j++){
            if(map[i][j].status == WALK_CUT) A_star(i, j); // goes to every position that can be cut
        }
    }

    A_star(X_INIT, Y_INIT); // return to the initial position
    return 0;
}