//
// Created by Michal Bartoň on 27.05.2022.
//

#include <iostream>

#include "Game.h"

Game::Game() : turn(Color::WHITE), check_black(false), check_white(false) {}

Game::~Game() {}

int Game::indexFromColumn(char column) {
    if (column >= 'A' and column <= 'H'){
        return column - 65;
    }
    if (column >= 'a' and column <= 'h'){
        return column - 97;
    }
    return -1;
}

void Game::play() {
    bool end = false;
    std::string str;

    while (!end){
        this->board.drawBoard();
        if (this->turn == Color::BLACK){
            std::cout << "Na tahu je ČERNÁ" << std::endl;
        } else {
            std::cout << "Na tahu je BÍLÁ" << std::endl;
        }

        std::cout << "Zadej svůj tah [from postion],[to position] - např. A1,H8:" << std::endl;

        std::getline(std::cin, str);
        //str = "A7,A6";
        int from_column = this->indexFromColumn(str[0]);
        int to_column = this->indexFromColumn(str[3]);
        int from_row = str[1] - 49;
        int to_row = str[4] - 49;
        int from_index = from_row * board.getColumns() + from_column;
        auto b = this->board.getFigures();
        if (from_column == -1 or to_column == -1
            or from_row > 7 or from_row < 0 or to_row > 7 or to_row < 0
            or b[from_index] == std::nullopt
            or b[from_index]->getColor() != this->turn
            or !board.move(Position{from_row, from_column}, Position{to_row, to_column})){
            std::cout << "Neplatný tah!" << std::endl;
            continue;
        }
        else {
            if (this->turn == Color::WHITE){
                this->turn = Color::BLACK;
            }
            else {
                this->turn = Color::WHITE;
            }
            if (board.isCheck(Color::WHITE)){
                this->check_white = true;
                std::cout << "Bílá je v šachu!" << std::endl;
            }
            if (board.isCheck(Color::BLACK)){
                this->check_black = true;
                std::cout << "Černá je v šachu!" << std::endl;
            }
            if (board.isCheckMate(Color::WHITE)){
            //sach mat nebere v potaz, ze se nektera figurka muze pohnout tak, ze v dalsim tahu ochrani krále nebo vyhodi figurku, ktera udela sach
                std::cout << "Černá vyhrála!" << std::endl;
                end = true;
                continue;
            }
            if (board.isCheckMate(Color::BLACK)){
                std::cout << "Bílá vyhrála!" << std::endl;
                end = true;
                continue;
            }
        }
    }
}

