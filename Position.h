//
// Created by Michal Bartoň on 06.05.2022.
//

#ifndef BAR0692_CHESS_POSITION_H
#define BAR0692_CHESS_POSITION_H


class Position {
private:
    int row;
public:
    int getRow() const;

    int getColumn() const;

private:
    int column;
public:
    Position(int row, int column);
    ~Position();
};


#endif //BAR0692_CHESS_POSITION_H
