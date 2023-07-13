//
// Created by Michal Bartoň on 26.04.2022.
//

#include "Board.h"

Board::Board() : count_rows(8), count_columns(8) {
    //BLACK
    for (int i = 0; i < this->count_rows * this->count_columns; i++) {
        this->figures.push_back(std::nullopt);
    }
    this->figures[0].emplace(Figure(Type::ROOK, Color::BLACK));
    this->figures[1].emplace(Figure(Type::KNIGHT, Color::BLACK));
    this->figures[2].emplace(Figure(Type::BISHOP, Color::BLACK));
    this->figures[3].emplace(Figure(Type::QUEEN, Color::BLACK));
    this->figures[4].emplace(Figure(Type::KING, Color::BLACK));
    this->figures[5].emplace(Figure(Type::BISHOP, Color::BLACK));
    this->figures[6].emplace(Figure(Type::KNIGHT, Color::BLACK));
    this->figures[7].emplace(Figure(Type::ROOK, Color::BLACK));
    for (int i = 0; i < 8; i++) {
        this->figures[1 * this->count_columns + i].emplace(Figure(Type::PAWN, Color::BLACK));
    }
    //WHITE
    for (int i = 0; i < 8; i++) {
        this->figures[6 * this->count_columns + i].emplace(Figure(Type::PAWN, Color::WHITE));
    }
    this->figures[7 * this->count_columns].emplace(Figure(Type::ROOK, Color::WHITE));
    this->figures[7 * this->count_columns + 1].emplace(Figure(Type::KNIGHT, Color::WHITE));
    this->figures[7 * this->count_columns + 2].emplace(Figure(Type::BISHOP, Color::WHITE));
    this->figures[7 * this->count_columns + 3].emplace(Figure(Type::QUEEN, Color::WHITE));
    this->figures[7 * this->count_columns + 4].emplace(Figure(Type::KING, Color::WHITE));
    this->figures[7 * this->count_columns + 5].emplace(Figure(Type::BISHOP, Color::WHITE));
    this->figures[7 * this->count_columns + 6].emplace(Figure(Type::KNIGHT, Color::WHITE));
    this->figures[7 * this->count_columns + 7].emplace(Figure(Type::ROOK, Color::WHITE));
}

Board::~Board() {}

void Board::drawBoard() {
    for (int i = 0; i < this->count_rows; i++) {
        std::cout << i + 1 << "  ";
        for (int j = 0; j < this->count_columns; j++){
            int index = i * this->count_columns + j;
            if (this->figures[index] == std::nullopt){
                std::cout << ".." << "\t";
            }
            else {
                if (this->figures[index]->getColor() == Color::BLACK){
                    if (this->figures[index]->getType() == Type::ROOK){
                        std::cout << "CV" << "\t";
                    }
                    else if (this->figures[index]->getType() == Type::KNIGHT){
                        std::cout << "CJ" << "\t";
                    }
                    else if (this->figures[index]->getType() == Type::BISHOP){
                        std::cout << "CS" << "\t";
                    }
                    else if (this->figures[index]->getType() == Type::QUEEN){
                        std::cout << "CD " << "\t";
                    }
                    else if (this->figures[index]->getType() == Type::KING){
                        std::cout << "CK" << "\t";
                    }
                    else if (this->figures[index]->getType() == Type::PAWN){
                        std::cout << "CP" << "\t";
                    }
                } else if (this->figures[index]->getColor() == Color::WHITE) {
                    if (this->figures[index]->getType() == Type::ROOK) {
                        std::cout << "BV" << "\t";
                    } else if (this->figures[index]->getType() == Type::KNIGHT) {
                        std::cout << "BJ" << "\t";
                    } else if (this->figures[index]->getType() == Type::BISHOP) {
                        std::cout << "BS" << "\t";
                    } else if (this->figures[index]->getType() == Type::QUEEN) {
                        std::cout << "BD" << "\t";
                    } else if (this->figures[index]->getType() == Type::KING) {
                        std::cout << "BK" << "\t";
                    } else if (this->figures[index]->getType() == Type::PAWN) {
                        std::cout << "BP" << "\t";
                    }
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "   A    B   C   D   E   F   G   H" << std::endl;
}

bool Board::isFigure(Position position) {
    return this->figures[position.getRow() * this->count_columns + position.getColumn()] != std::nullopt;
}

bool Board::canDiscard(Position from, Position to) {
    int index_to = to.getRow() * this->count_columns + to.getColumn();
    if (this->figures[index_to] == std::nullopt){
        return true;
    }
    if (this->figures[index_to]->getType() == Type::KING){
        return false;
    }
    return this->figures[from.getRow() * this->count_columns + from.getColumn()]->getColor() != this->figures[index_to]->getColor();
}

bool Board::move(Position from, Position to) {
    int index_from = from.getRow() * this->count_columns + from.getColumn();
    int index_to = to.getRow() * this->count_columns + to.getColumn();
    bool is_valid;
    if (this->figures[index_from] == std::nullopt){
        return false;
    }

    if (this->figures[index_from]->getType() == Type::BISHOP){
         is_valid = this->move_bishop(from, to);
    }
    else if (this->figures[index_from]->getType() == Type::KNIGHT){
        is_valid = this->move_knight(from, to);
    }
    else if (this->figures[index_from]->getType() == Type::ROOK){
        is_valid = this->move_rook(from, to);
    }
    else if (this->figures[index_from]->getType() == Type::KING){
        is_valid = this->move_king(from, to);
    }
    else if (this->figures[index_from]->getType() == Type::PAWN){
        is_valid = this->move_pawn(from, to);
    }
    else if (this->figures[index_from]->getType() == Type::QUEEN){
        is_valid = this->move_queen(from, to);
    }

    return is_valid;
}

bool Board::freeWayDiagonalDown(Position from, Position to) {
    int count = to.getRow() - from.getRow();
    for (int i = 1; i < count; i++) {
        if (this->figures[(from.getRow() + i) * this->count_columns + from.getColumn() + i] != std::nullopt){
            return false;
        }
    }
    return true;
}

bool Board::freeWayDiagonalUp(Position from, Position to) {
    int count = abs(to.getRow() - from.getRow());
    for (int i = 1; i < count; i++) {
        if (this->figures[(from.getRow() + i) * this->count_columns + from.getColumn() - i] != std::nullopt){
            return false;
        }
    }
    return true;
}

bool Board::move_bishop(Position from, Position to) {
    int index_from = from.getRow() * this->count_columns + from.getColumn();
    int index_to = to.getRow() * this->count_columns + to.getColumn();
    int differency_rows = to.getRow() - from.getRow();
    int differency_columns = to.getColumn() - from.getColumn();
    if (!this->canDiscard(from, to)){
        return false;
    }
    if ((abs(differency_rows) == abs(differency_columns)) and this->canDiscard(from, to)){
        if (differency_columns > 0 and differency_rows > 0){
            if (this->freeWayDiagonalDown(from, to)){
                if (this->moving(index_from, index_to)){
                    return true;
                }
            }
        }
        else if (differency_columns < 0 and differency_rows > 0){
            if (this->freeWayDiagonalUp(from, to)){
                if (this->moving(index_from, index_to)){
                    return true;
                }
            }
        }
        else if (differency_columns > 0 and differency_rows < 0){
            if (this->freeWayDiagonalUp(to, from)){
                if (this->moving(index_from, index_to)){
                    return true;
                }
            }
        }
        else if (differency_columns < 0 and differency_rows < 0){
            if (this->freeWayDiagonalDown(to, from)){
                if (this->moving(index_from, index_to)){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::move_knight(Position from, Position to) {
    int index_from = from.getRow() * this->count_columns + from.getColumn();
    int index_to = to.getRow() * this->count_columns + to.getColumn();
    //zkontrolovat isFigure(to)
    int differency_rows = from.getRow() - to.getRow();
    int differency_columns = from.getColumn() - to.getColumn();
    if (!this->canDiscard(from, to)){
        return false;
    }
    if (abs(differency_rows) == 2 and abs(differency_columns) == 1
            or abs(differency_rows) == 1 and abs(differency_columns) == 2){
        if (this->isFigure(to)){
            if (this->figures[index_to]->getColor() != this->figures[index_from]->getColor()){
                if (this->moving(index_from, index_to)){
                    return true;
                }
            }
        } else {
            if (this->moving(index_from, index_to)){
                return true;
            }
        }
    }
    return false;
}

bool Board::freeWayRows(Position from, Position to) {
    for (int i = from.getRow() - 1; i > to.getRow(); i--) {
        if (this->figures[i * this->count_columns + from.getColumn()] != std::nullopt){
            return false;
        }
    }
    return true;
}

bool Board::freeWayColumns(Position from, Position to) {
    for (int i = from.getColumn() - 1; i > to.getColumn(); i--) {
        if (this->figures[from.getRow() * this->count_columns + i] != std::nullopt){
            return false;
        }
    }
    return true;
}

bool Board::move_rook(Position from, Position to) {
    int index_from = from.getRow() * this->count_columns + from.getColumn();
    int index_to = to.getRow() * this->count_columns + to.getColumn();
    if (!this->canDiscard(from, to)){
        return false;
    }
    if (from.getRow() > to.getRow() and from.getColumn() == to.getColumn()){
        if (this->canDiscard(from, to) and this->freeWayRows(from, to)) { //kontrola pro pozici tu jestli je discard
            if (this->moving(index_from, index_to)){
                return true;
            }
        }
    }
    else if (from.getRow() < to.getRow() and from.getColumn() == to.getColumn()){
        if (this->canDiscard(from, to) and this->freeWayRows(to, from)) {
            if (this->moving(index_from, index_to)){
                return true;
            }
        }
    }
    else if (from.getRow() == to.getRow() and from.getColumn() > to.getColumn()){
        if (this->canDiscard(from, to) and this->freeWayColumns(from, to)) { //kontrola pro pozici tu jestli je discard
            if (this->moving(index_from, index_to)){
                return true;
            }
        }
    }
    else if (from.getRow() == to.getRow() and from.getColumn() < to.getColumn()){
        if (this->canDiscard(from, to) and this->freeWayColumns(to, from)) {
            if (this->moving(index_from, index_to)){
                return true;
            }
        }
    }
    return false;
}

bool Board::move_king(Position from, Position to) {
    int index_from = from.getRow() * this->count_columns + from.getColumn();
    int index_to = to.getRow() * this->count_columns + to.getColumn();
    int differency_rows = from.getRow() - to.getRow();
    int differency_columns = from.getColumn() - to.getColumn();
    if (!this->canDiscard(from, to)){
        return false;
    }
    if (this->isCheck(this->figures[index_from]->getColor(),to)){//kral nemuze jit do sachu
        return false;
    }
    if (this->canDiscard(from, to) and differency_rows >= -1 and
            differency_rows <= 1 and differency_columns >= -1 and differency_columns <= 1){
        if (this->moving(index_from, index_to)){
            return true;
        }
    }
    return false;
}

bool Board::move_pawn(Position from, Position to) {
    int index_from = from.getRow() * this->count_columns + from.getColumn();
    int index_to = to.getRow() * this->count_columns + to.getColumn();
    if (!this->canDiscard(from, to)){
        return false;
    }
    if (this->figures[index_from]->getColor() == Color::BLACK){
        if (!this->isFigure(to)
                 and from.getColumn() == to.getColumn()
                 and from.getRow() == 6
                 and to.getRow() == 7){
            this->figures[index_to].emplace(Figure(Type::QUEEN, Color::BLACK));
            this->figures[index_from] = std::nullopt;
            return true;
        }
        else if (this->isFigure(to)
                 and abs(from.getColumn() - to.getColumn()) == 1//tady a vsude by melo byt getColumn
                 and from.getRow() == to.getRow() - 1
                 and canDiscard(from, to)
                 and to.getRow() == 7){
            this->figures[index_to].emplace(Figure(Type::QUEEN, Color::BLACK));
            this->figures[index_from] = std::nullopt;
            return true;
        }
        else if (!this->isFigure(to)
                 and from.getColumn() == to.getColumn()
                 and from.getRow() == to.getRow() - 1){
            if (this->moving(index_from, index_to)){
                return true;
            }
        }
        else if (this->isFigure(to)
                and abs(from.getColumn() - to.getColumn()) == 1
                and from.getRow() == to.getRow() - 1
                and canDiscard(from, to)){
            if (this->moving(index_from, index_to)){
                return true;
            }
        }//prvni o dva
        else if (!this->isFigure(to)
                and from.getColumn() == to.getColumn()
                and from.getRow() == to.getRow() - 2
                and from.getRow() == 1){
            if (this->moving(index_from, index_to)){
                return true;
            }
        }//pincl na damu


    } else {
        if (!this->isFigure(to)
                 and from.getColumn() == to.getColumn()
                 and from.getRow() == 1
                 and to.getRow() == 0){
            this->figures[index_to].emplace(Figure(Type::QUEEN, Color::WHITE));
            this->figures[index_from] = std::nullopt;
            return true;
        }
        else if (this->isFigure(to)
                 and abs(from.getColumn() - to.getColumn()) == 1
                 and from.getRow() == to.getRow() + 1
                 and canDiscard(from, to)
                 and to.getRow() == 0){
            this->figures[index_to].emplace(Figure(Type::QUEEN, Color::WHITE));
            this->figures[index_from] = std::nullopt;
            return true;
        }
        else if (!this->isFigure(to)
                 and from.getColumn() == to.getColumn()
                 and from.getRow() == to.getRow() + 1){
            if (this->moving(index_from, index_to)){
                return true;
            }
        }
        else if (this->isFigure(to)
                 and abs(from.getColumn() - to.getColumn()) == 1
                 and from.getRow() == to.getRow() + 1
                 and canDiscard(from, to)){
            if (this->moving(index_from, index_to)){
                return true;
            }
        }//pohyb o 2 od zacatku
        else if (!this->isFigure(to)
                 and from.getColumn() == to.getColumn()
                 and from.getRow() == to.getRow() + 2
                 and from.getRow() == 6){
            if (this->moving(index_from, index_to)){
                return true;
            }
        }

    }

    return false;
}

bool Board::move_queen(Position from, Position to) {
    if (!this->canDiscard(from, to)){
        return false;
    }
    return this->move_bishop(from, to) or this->move_rook(from, to);
}

std::vector<std::optional<Figure>> Board::getFigures() {
    return this->figures;
}

const int Board::getColumns(){
    return this->count_columns;
}

bool Board::moving(int index_from, int index_to) {
    Figure *figure = nullptr;
    if (this->figures[index_to] != std::nullopt){
        figure = new Figure{this->figures[index_to]->getType(), this->figures[index_to]->getColor()};
    }

    this->figures[index_to].emplace(Figure(this->figures[index_from]->getType(), this->figures[index_from]->getColor()));
    this->figures[index_from] = std::nullopt;
    if (this->isCheck(this->figures[index_to]->getColor())){
        this->figures[index_from].emplace(Figure(this->figures[index_to]->getType(), this->figures[index_to]->getColor()));
        if (figure == nullptr){
            this->figures[index_to] = std::nullopt;
        } else {
            this->figures[index_to].emplace(Figure(figure->getType(), figure->getColor()));
            delete figure;
        }
        return false;
    }
    return true;
}

bool Board::controlDiagonal(Color color, Position from) {
    bool isCheck = false;
    int i = 1;
    while (true){//kontrola sachu sikmo dolu doprava
        if ((from.getRow() + i) > 7 or (from.getColumn() + i) > 7){
            break;
        }
        int index = (i + from.getRow()) * this->count_columns + from.getColumn() + i;
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getColor() != color){
                if (this->figures[index]->getType() == Type::QUEEN
                    or this->figures[index]->getType() == Type::BISHOP){
                    isCheck = true;
                }
                else {
                    break;
                }
            } else {
                break;
            }
        }
        i++;
    }
    i = 1;
    while (true){//kontrola sachu sikmo dolu doleva
        if ((from.getRow() + i) > 7 or (from.getColumn() - i) < 0){
            break;
        }
        int index = (i + from.getRow()) * this->count_columns + from.getColumn() - i;
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getColor() != color){
                if (this->figures[index]->getType() == Type::QUEEN
                    or this->figures[index]->getType() == Type::BISHOP){
                    isCheck = true;
                }
                else {
                    break;
                }
            } else {
                break;
            }
        }
        i++;
    }
    i = 1;
    while (true){//kontrola sachu sikmo nahoru doleva
        if ((from.getRow() - i) < 0 or (from.getColumn() - i) < 0){
            break;
        }
        int index = (from.getRow() - i) * this->count_columns + from.getColumn() - i;
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getColor() != color) {
                if (this->figures[index]->getType() == Type::QUEEN
                    or this->figures[index]->getType() == Type::BISHOP) {
                    isCheck = true;
                }
                else {
                    break;
                }
            } else {
                break;
            }
        }
        i++;
    }
    i = 1;
    while (true){//kontrola sachu sikmo nahoru doprava
        if ((from.getRow() - i) < 0 or (from.getColumn() + i) > 7){
            break;
        }
        int index = (from.getRow() - i) * this->count_columns + from.getColumn() + i;
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getColor() != color){
                if (this->figures[index]->getType() == Type::QUEEN
                    or this->figures[index]->getType() == Type::BISHOP){
                    isCheck = true;
                }
                else {
                    break;
                }
            } else {
                break;
            }
        }

        i++;
    }
    return isCheck;
}

bool Board::controlPawn(Color color, Position from) {
    bool isCheck = false;
    if (color == Color::BLACK){
        if (from.getRow() == 7){
            return isCheck;
        }
        if (from.getColumn() - 1 < 0){
            int index = (from.getRow() + 1) * this->count_columns + from.getColumn() + 1;
            if (this->figures[index] != std::nullopt) {
                if (this->figures[index]->getType() == Type::PAWN and
                    this->figures[index]->getColor() == Color::WHITE) {
                    isCheck = true;
                }
            }
        }
        else if (from.getColumn() + 1 > 7){
            int index = (from.getRow() + 1) * this->count_columns + from.getColumn() - 1;
            if (this->figures[index] != std::nullopt) {
                if (this->figures[index]->getType() == Type::PAWN and
                    this->figures[index]->getColor() == Color::WHITE) {
                    isCheck = true;
                }
            }
        } else {
            int index = (from.getRow() + 1) * this->count_columns + from.getColumn() - 1;
            if (this->figures[index] != std::nullopt) {
                if (this->figures[index]->getType() == Type::PAWN and
                    this->figures[index]->getColor() == Color::WHITE) {
                    isCheck = true;
                }
            }
            index = (from.getRow() + 1) * this->count_columns + from.getColumn() + 1;
            if (this->figures[index] != std::nullopt) {
                if (this->figures[index]->getType() == Type::PAWN and
                    this->figures[index]->getColor() == Color::WHITE) {
                    isCheck = true;
                }
            }
        }
    } else {
        if (from.getRow() == 0){
            return isCheck;
        }
        if (from.getColumn() - 1 < 0){
            int index = (from.getRow() - 1) * this->count_columns + from.getColumn() + 1;
            if (this->figures[index] != std::nullopt) {
                if (this->figures[index]->getType() == Type::PAWN and
                    this->figures[index]->getColor() == Color::BLACK) {
                    isCheck = true;
                }
            }
        }
        else if (from.getColumn() + 1 > 7){
            int index = (from.getRow() - 1) * this->count_columns + from.getColumn() - 1;
            if (this->figures[index] != std::nullopt) {
                if (this->figures[index]->getType() == Type::PAWN and
                    this->figures[index]->getColor() == Color::BLACK) {
                    isCheck = true;
                }
            }
        }
        else {
            int index = (from.getRow() - 1) * this->count_columns + from.getColumn() - 1;
            if (this->figures[index] != std::nullopt) {
                if (this->figures[index]->getType() == Type::PAWN and
                    this->figures[index]->getColor() == Color::BLACK) {
                    isCheck = true;
                }
            }
            index = (from.getRow() - 1) * this->count_columns + from.getColumn() + 1;
            if (this->figures[index] != std::nullopt) {
                if (this->figures[index]->getType() == Type::PAWN and
                    this->figures[index]->getColor() == Color::BLACK) {
                    isCheck = true;
                }
            }
        }
    }
    return isCheck;
}

bool Board::controlKnightPosition(int row, int column, Color color) {
    int index = row * this->count_columns + column;
    if (row < 8 and column < 8 and row >= 0 and column >= 0){
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getType() == Type::KNIGHT and this->figures[index]->getColor() != color){
                return true;
            }
        }
    }
    return false;
}


bool Board::controlKnight(Color color, Position from) {
    if (this->controlKnightPosition(from.getRow() + 1, from.getColumn() + 2, color)
            or this->controlKnightPosition(from.getRow() + 2, from.getColumn() + 1, color)
            or this->controlKnightPosition(from.getRow() - 1, from.getColumn() + 2, color)
            or this->controlKnightPosition(from.getRow() + 1, from.getColumn() - 2, color)
            or this->controlKnightPosition(from.getRow() - 1, from.getColumn() - 2, color)
            or this->controlKnightPosition(from.getRow() - 2, from.getColumn() + 1, color)
            or this->controlKnightPosition(from.getRow() + 2, from.getColumn() - 1, color)
            or this->controlKnightPosition(from.getRow() - 2, from.getColumn() - 1, color)){
        return true;
    }
    return false;
}

bool Board::controlKingPosition(int row, int column, Color color) {
    int index = row * this->count_columns + column;
    if (row < 8 and column < 8 and row >= 0 and column >= 0){
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getType() == Type::KING and this->figures[index]->getColor() != color){
                return true;
            }
        }
    }
    return false;
}

bool Board::controlKing(Color color, Position from) {
    if (this->controlKingPosition(from.getRow() + 1, from.getColumn() + 1, color)
        or this->controlKingPosition(from.getRow() - 1, from.getColumn() - 1, color)
        or this->controlKingPosition(from.getRow() - 1, from.getColumn() + 1, color)
        or this->controlKingPosition(from.getRow() + 1, from.getColumn() - 1, color)
        or this->controlKingPosition(from.getRow() - 1, from.getColumn(), color)
        or this->controlKingPosition(from.getRow(), from.getColumn() - 1, color)
        or this->controlKingPosition(from.getRow() + 1, from.getColumn(), color)
        or this->controlKingPosition(from.getRow(), from.getColumn() + 1, color)){
        return true;
    }
    return false;
}

bool Board::controlStraight(Color color, Position from) {
    bool isCheck = false;
    int i = 1;
    while (true){//kontrola doprava
        if (from.getColumn() + i > 7){
             break;
        }
        int index = from.getRow() * this->count_columns + from.getColumn() + i;
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getColor() != color){
                if (this->figures[index]->getType() == Type::QUEEN
                        or this->figures[index]->getType() == Type::ROOK){
                    isCheck = true;
                }
                else {
                    break;
                }
            } else {
                break;
            }
        }
        i++;
    }
    i = 1;
    while (true){//kontrola doleva
        if (from.getColumn() - i < 0){
            break;
        }
        int index = from.getRow() * this->count_columns + from.getColumn() - i;
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getColor() != color){
                if (this->figures[index]->getType() == Type::QUEEN
                    or this->figures[index]->getType() == Type::ROOK){
                    isCheck = true;
                }
                else {
                    break;
                }
            } else {
                break;
            }
        }
        i++;
    }
    i = 1;
    while (true){//kontrola nahoru
        if (from.getRow() - i < 0){
            break;
        }
        int index = (from.getRow() - i) * this->count_columns + from.getColumn();
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getColor() != color){
                if (this->figures[index]->getType() == Type::QUEEN
                    or this->figures[index]->getType() == Type::ROOK){
                    isCheck = true;
                }
                else {
                    break;
                }
            } else {
                break;
            }
        }
        i++;
    }
    i = 1;
    while (true){//kontrola dolu
        if (from.getRow() + i > 7){
            break;
        }
        int index = (from.getRow() + i) * this->count_columns + from.getColumn();
        if (this->figures[index] != std::nullopt){
            if (this->figures[index]->getColor() != color){
                if (this->figures[index]->getType() == Type::QUEEN
                    or this->figures[index]->getType() == Type::ROOK){
                    isCheck = true;
                }
                else {
                    break;
                }
            } else {
                break;
            }
        }
        i++;
    }
    return isCheck;
}

bool Board::isCheck(Color color, Position from) {
    if (this->controlDiagonal(color, from)){
        return true;
    }
    if (this->controlStraight(color, from)){
        return true;
    }
    if (this->controlKing(color, from)){
        return true;
    }
    if (this->controlKnight(color, from)){
        return true;
    }
    if (this->controlPawn(color, from)){
        return true;
    }

    return false;
}

bool Board::isCheck(Color color) {
    return this->isCheck(color, this->getPositionOfKing(color));
}

Position Board::getPositionOfKing(Color color) {
    int row = 0;
    int column = 0;
    for (int i = 0; i < this->count_rows; i++) {
        for (int j = 0; j < this->count_columns; j++) {
            if (this->figures[i * this->count_columns + j] == std::nullopt){
                continue;
            }
            if (this->figures[i * this->count_columns + j]->getType() == Type::KING
                and this->figures[i * this->count_columns + j]->getColor() == color){
                row = i;
                column = j;
            }
        }
    }
    return Position(row, column);
}

bool Board::isCheckMatePosition(Color color, int row, int column) {
    int index = row * this->count_columns + column;
    if (row < 8 and column < 8 and row >= 0 and column >= 0){
        if (this->figures[index] == std::nullopt or
                color == Color::WHITE and this->figures[index]->getColor() == Color::BLACK or
                color == Color::BLACK and this->figures[index]->getColor() == Color::WHITE){
            if (isCheck(color, Position{row, column})){
                return true;
            }
            return false;
        }
    }
    return true;
}

bool Board::isCheckMate(Color color) {
    Position position_of_king = this->getPositionOfKing(color);
    int row = position_of_king.getRow();
    int column = position_of_king.getColumn();
    if (this->isCheck(color, position_of_king)
            and this->isCheckMatePosition(color, row + 1, column)
            and this->isCheckMatePosition(color, row - 1, column)
            and this->isCheckMatePosition(color, row, column + 1)
            and this->isCheckMatePosition(color, row, column - 1)
            and this->isCheckMatePosition(color, row + 1, column + 1)
            and this->isCheckMatePosition(color, row + 1, column - 1)
            and this->isCheckMatePosition(color, row - 1, column + 1)
            and this->isCheckMatePosition(color, row - 1, column - 1)){
        return true;
    }
    return false;
}