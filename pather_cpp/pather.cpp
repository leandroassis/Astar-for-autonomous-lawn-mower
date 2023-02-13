

void A_star(__uint16_t x_dest, __uint16_t y_dest){
    // A* algorithm
    // https://en.wikipedia.org/wiki/A*_search_algorithm

    List<PositionNode> open_list;
    List<PositionNode> closed_list;
    List<PositionNode> neighbors;

    // add the initial position to the open list
    open_list.push_back(*actual_pos);

    while(open_list.size() > 0){
        // get the position with the lowest f cost
        PositionNode *current = &open_list[0];
        for(int i = 0; i < open_list.size(); i++){
            if(open_list[i].f < current->f) current = &open_list[i];
        }

        // if the current position is the destination, the path is found
        if(current->x == x_dest && current->y == y_dest){
            // get the path
            List<PositionNode> path;
            PositionNode *temp = current;
            path.push_back(*temp);
            while(temp->x != X_INIT || temp->y != Y_INIT){
                temp = temp->parent;
                path.push_back(*temp);
            }

            // cut the path
            for(int i = path.size() - 1; i >= 0; i--){
                cut_lawn(path[i].x, path[i].y);
            }
            return;
        }

        // remove the current position from the open list and add it to the closed list
        open_list.remove(*current);
        closed_list.push_back(*current);

        // get the neighbors of the current position
        neighbors = get_neighbors(current->x, current->y);

        // for each neighbor
        for(int i = 0; i < neighbors.size(); i++){
            // if the neighbor is in the closed list, ignore it
            if(closed_list.contains(neighbors[i])) continue;

            // if the neighbor is not in the open list, add it
            if(!open_list.contains(neighbors[i])) open_list.push_back(neighbors[i]);

            // calculate the g cost
            __uint16_t g = current->g + 1;

            // if the g cost is higher than the current g cost, ignore it
            if(g >= neighbors[i].g) continue;

            // update the neighbor
            neighbors[i].parent = current;
            neighbors[i].g = g;
            neighbors[i].f = neighbors[i].g + neighbors[i].h;
        }
    }


    // cut lawn
    // uptade the atual position status
    actual_pos->status = VISITED;

    // updates the actual position
    actual_pos = &map[x_dest][y_dest];
    return;
}