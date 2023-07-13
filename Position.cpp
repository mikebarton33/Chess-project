//
// Created by Michal Bartoň on 06.05.2022.
//

#include "Position.h"

Position::Position(int row, int column) : row(row), column(column) {}

Position::~Position(){}

int Position::getRow() const {
    return row;
}

int Position::getColumn() const {
    return column;
}
