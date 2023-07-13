// This tells doctest to provide a main() function
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include "doctest.h"
#include "Board.h"


Board board{};

TEST_SUITE("Move pawn") {
    TEST_CASE("Move - 1 step") {
        REQUIRE(board.move(Position{1, 1}, Position{2, 1}) == 1);
        auto b = board.getFigures();
        REQUIRE(b[1 * board.getColumns() + 1] == std::nullopt);
        REQUIRE(b[2 * board.getColumns() + 1] != std::nullopt);

        REQUIRE(board.move(Position{6, 2}, Position{5, 2}) == 1);
        REQUIRE(board.move(Position{5, 2}, Position{4, 2}) == 1);
        REQUIRE(board.move(Position{4, 2}, Position{3, 2}) == 1);
        b = board.getFigures();
        REQUIRE(b[6 * board.getColumns() + 2] == std::nullopt);
        REQUIRE(b[5 * board.getColumns() + 2] == std::nullopt);
        REQUIRE(b[4 * board.getColumns() + 2] == std::nullopt);
        REQUIRE(b[3 * board.getColumns() + 2] != std::nullopt);

        REQUIRE(board.move(Position{3, 2}, Position{2, 1}) == 1);//vyhozeni
        b = board.getFigures();
        REQUIRE(b[3 * board.getColumns() + 2] == std::nullopt);
        REQUIRE(b[2 * board.getColumns() + 1] != std::nullopt);
    }
    TEST_CASE("Move - 2 steps") {
        REQUIRE(board.move(Position{1, 0}, Position{3, 0}) == 1);
        REQUIRE(board.move(Position{6, 5}, Position{4, 5}) == 1);
        REQUIRE(board.move(Position{6, 4}, Position{4, 4}) == 1);
        auto b = board.getFigures();
        REQUIRE(b[1 * board.getColumns() + 0] == std::nullopt);
        REQUIRE(b[3 * board.getColumns() + 0] != std::nullopt);
        REQUIRE(b[6 * board.getColumns() + 5] == std::nullopt);
        REQUIRE(b[4 * board.getColumns() + 5] != std::nullopt);
        REQUIRE(b[6 * board.getColumns() + 4] == std::nullopt);
        REQUIRE(b[4 * board.getColumns() + 4] != std::nullopt);
    }
}

TEST_SUITE("Move king"){
    TEST_CASE("Move"){
        REQUIRE(board.move(Position{7, 4}, Position{6, 4}) == 1);
        REQUIRE(board.move(Position{6, 4}, Position{5, 3}) == 1);
        auto b = board.getFigures();
        REQUIRE(b[7 * board.getColumns() + 4] == std::nullopt);
        REQUIRE(b[6 * board.getColumns() + 4] == std::nullopt);
        REQUIRE(b[5 * board.getColumns() + 3] != std::nullopt);
    }
    TEST_CASE("Don't move"){
        REQUIRE(board.move(Position{0, 4}, Position{1, 3}) == 0);
        REQUIRE(board.move(Position{5, 3}, Position{3, 3}) == 0);
        REQUIRE(board.move(Position{5, 3}, Position{4, 4}) == 0);
        auto b = board.getFigures();
        REQUIRE(b[7 * board.getColumns() + 4] == std::nullopt);
        REQUIRE(b[5 * board.getColumns() + 3] != std::nullopt);
        REQUIRE(b[3 * board.getColumns() + 3] == std::nullopt);
        REQUIRE(b[4 * board.getColumns() + 4] != std::nullopt);
    }
}

TEST_SUITE("Move rook"){
    TEST_CASE("Move"){
        REQUIRE(board.move(Position{0, 0}, Position{2, 0}) == 1);
        REQUIRE(board.move(Position{2, 0}, Position{2, 1}) == 1);
        REQUIRE(board.move(Position{2, 1}, Position{2, 0}) == 1);
        auto b = board.getFigures();
        REQUIRE(b[0 * board.getColumns() + 0] == std::nullopt);
        REQUIRE(b[2 * board.getColumns() + 0] != std::nullopt);
        REQUIRE(b[2 * board.getColumns() + 1] == std::nullopt);
    }
    TEST_CASE("Don't move"){
        REQUIRE(board.move(Position{7, 0}, Position{7, 2}) == 0);
        REQUIRE(board.move(Position{7, 0}, Position{7, 4}) == 0);
        REQUIRE(board.move(Position{7, 0}, Position{0, 0}) == 0);
        auto b = board.getFigures();
        REQUIRE(b[0 * board.getColumns() + 0] == std::nullopt);
        REQUIRE(b[7 * board.getColumns() + 0] != std::nullopt);
        REQUIRE(b[7 * board.getColumns() + 2] != std::nullopt);
    }
}

TEST_SUITE("Move knight"){
    TEST_CASE("Don't move"){
        REQUIRE(board.move(Position{0, 1}, Position{2, 1}) == 0);
        REQUIRE(board.move(Position{0, 1}, Position{1, 3}) == 0);
        auto b = board.getFigures();
        REQUIRE(b[0 * board.getColumns() + 1] != std::nullopt);
        REQUIRE(b[0 * board.getColumns() + 1] != std::nullopt);
        REQUIRE(b[0 * board.getColumns() + 1]->getColor() == b[1 * board.getColumns() + 3]->getColor());
        REQUIRE(b[2 * board.getColumns() + 1] == std::nullopt);
    }
    TEST_CASE("Move"){
        REQUIRE(board.move(Position{0, 1}, Position{2, 2}) == 1);
        REQUIRE(board.move(Position{0, 6}, Position{2, 5}) == 1);
        REQUIRE(board.move(Position{7, 1}, Position{5, 0}) == 1);
        REQUIRE(board.move(Position{7, 6}, Position{6, 4}) == 1);
        REQUIRE(board.move(Position{6, 4}, Position{4, 3}) == 1);
        REQUIRE(board.move(Position{4, 3}, Position{3, 5}) == 1);
        REQUIRE(board.move(Position{3, 5}, Position{1, 6}) == 1);
        auto b = board.getFigures();
        REQUIRE(b[0 * board.getColumns() + 1] == std::nullopt);
        REQUIRE(b[0 * board.getColumns() + 6] == std::nullopt);
        REQUIRE(b[7 * board.getColumns() + 1] == std::nullopt);
        REQUIRE(b[7 * board.getColumns() + 6] == std::nullopt);
        REQUIRE(b[6 * board.getColumns() + 4] == std::nullopt);
        REQUIRE(b[4 * board.getColumns() + 3] == std::nullopt);
        REQUIRE(b[3 * board.getColumns() + 5] == std::nullopt);
        REQUIRE(b[1 * board.getColumns() + 6] != std::nullopt);
    }
}

TEST_SUITE("Move bishop"){
    TEST_CASE("Don't move - first part"){
        REQUIRE(board.move(Position{7, 5}, Position{5, 3}) == 0);
        REQUIRE(board.move(Position{7, 5}, Position{3, 3}) == 0);
        REQUIRE(board.move(Position{7, 5}, Position{3, 1}) == 0);
        REQUIRE(board.move(Position{7, 5}, Position{5, 7}) == 0);
        REQUIRE(board.move(Position{7, 5}, Position{5, 5}) == 0);
        auto b = board.getFigures();
        REQUIRE(b[7 * board.getColumns() + 5] != std::nullopt);
    }
    TEST_CASE("Move - first part"){
        REQUIRE(board.move(Position{7, 5}, Position{6, 4}) == 1);
        REQUIRE(board.move(Position{6, 4}, Position{4, 6}) == 1);
        REQUIRE(board.move(Position{4, 6}, Position{1, 3}) == 1);
        REQUIRE(board.move(Position{1, 3}, Position{2, 4}) == 1);
        REQUIRE(board.move(Position{2, 4}, Position{4, 2}) == 1);
        REQUIRE(board.move(Position{4, 2}, Position{3, 1}) == 1);
        auto b = board.getFigures();
        REQUIRE(b[7 * board.getColumns() + 5] == std::nullopt);
        REQUIRE(b[6 * board.getColumns() + 4] == std::nullopt);
        REQUIRE(b[4 * board.getColumns() + 6] == std::nullopt);
        REQUIRE(b[1 * board.getColumns() + 3] == std::nullopt);
        REQUIRE(b[4 * board.getColumns() + 2] == std::nullopt);
        REQUIRE(b[2 * board.getColumns() + 4] == std::nullopt);
        REQUIRE(b[3 * board.getColumns() + 1] != std::nullopt);
    }
    TEST_CASE("Don't move - second part"){
        REQUIRE(board.move(Position{3, 1}, Position{1, 3}) == 0);
        REQUIRE(board.move(Position{3, 1}, Position{3, 0}) == 0);
        auto b = board.getFigures();
        REQUIRE(b[3 * board.getColumns() + 1] != std::nullopt);
    }
}

TEST_SUITE("Move queen"){
    TEST_CASE("Move"){
        REQUIRE(board.move(Position{7, 3}, Position{3, 7}) == 1);
        REQUIRE(board.move(Position{3, 7}, Position{1, 7}) == 1);
        REQUIRE(board.move(Position{1, 7}, Position{3, 5}) == 1);
        REQUIRE(board.move(Position{3, 5}, Position{3, 2}) == 1);
        REQUIRE(board.move(Position{3, 2}, Position{6, 2}) == 1);
        REQUIRE(board.move(Position{6, 2}, Position{4, 0}) == 1);
        REQUIRE(board.move(Position{4, 0}, Position{3, 0}) == 1);
        REQUIRE(board.move(Position{3, 0}, Position{1, 2}) == 1);
        REQUIRE(board.move(Position{1, 2}, Position{1, 4}) == 1);
        auto b = board.getFigures();
        REQUIRE(b[7 * board.getColumns() + 3] == std::nullopt);
        REQUIRE(b[3 * board.getColumns() + 7] == std::nullopt);
        REQUIRE(b[1 * board.getColumns() + 7] == std::nullopt);
        REQUIRE(b[3 * board.getColumns() + 5] == std::nullopt);
        REQUIRE(b[3 * board.getColumns() + 2] == std::nullopt);
        REQUIRE(b[6 * board.getColumns() + 2] == std::nullopt);
        REQUIRE(b[4 * board.getColumns() + 0] == std::nullopt);
        REQUIRE(b[3 * board.getColumns() + 0] == std::nullopt);
        REQUIRE(b[1 * board.getColumns() + 2] == std::nullopt);
        REQUIRE(b[1 * board.getColumns() + 4] != std::nullopt);
    }
}
