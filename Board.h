//
// Created by Michal Bartoň on 26.04.2022.
//
#include <iostream>
#include <vector>
#include <optional>

#ifndef BAR0692_CHESS_BOARD_H
#define BAR0692_CHESS_BOARD_H
#include "Figure.h"
#include "Position.h"

class Board {
private:
    std::vector<std::optional<Figure>> figures;
    const int count_rows;
    const int count_columns;
public:
    Board();
    ~Board();
    void drawBoard();
    std::vector<std::optional<Figure>> getFigures();
    const int getColumns();
    bool isFigure(Position position);
    bool canDiscard(Position from, Position to);
    bool freeWayDiagonalDown(Position from, Position to);
    bool freeWayDiagonalUp(Position from, Position to);
    bool freeWayRows(Position from, Position to);
    bool freeWayColumns(Position from, Position to);

    bool moving(int index_from, int index_to);

    bool move(Position from, Position to);

    bool move_bishop(Position from, Position to);

    bool move_knight(Position from, Position to);

    bool move_rook(Position from, Position to);

    bool move_king(Position from, Position to);

    bool move_pawn(Position from, Position to);

    bool move_queen(Position from, Position to);

    bool isCheck(Color color, Position from);

    bool isCheck(Color color);

    bool controlDiagonal(Color color, Position from);

    bool controlStraight(Color color, Position from);

    bool controlPawn(Color color, Position from);

    bool controlKnight(Color color, Position from);

    bool controlKnightPosition(int row, int column, Color color);

    bool controlKing(Color color, Position from);

    bool controlKingPosition(int row, int column, Color color);

    Position getPositionOfKing(Color color);

    bool isCheckMate(Color color);

    bool isCheckMatePosition(Color color, int row, int column);
};


#endif //BAR0692_CHESS_BOARD_H
