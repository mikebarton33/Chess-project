//
// Created by Michal Bartoň on 01.05.2022.
//

#ifndef BAR0692_CHESS_FIGURE_H
#define BAR0692_CHESS_FIGURE_H
#include <iostream>

enum class Type {
    KING,
    QUEEN,
    ROOK,
    KNIGHT,
    BISHOP,
    PAWN
};

enum class Color {
    WHITE,
    BLACK
};


class Figure {
private:
    const Type type;
    const Color color;
public:
    Figure(Type type, Color color);
    ~Figure();
    Type getType();
    Color getColor();
};


#endif //BAR0692_CHESS_FIGURE_H
