//
// Created by Michal Bartoň on 27.05.2022.
//

#ifndef BAR0692_CHESS_GAME_H
#define BAR0692_CHESS_GAME_H

#include "Board.h"

class Game {
private:
    Color turn;
    Board board{};
    bool check_white;
    bool check_black;
public:
    Game();
    ~Game();
    int indexFromColumn(char column);
    void play();
};


#endif //BAR0692_CHESS_GAME_H
