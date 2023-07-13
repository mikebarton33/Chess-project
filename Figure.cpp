//
// Created by Michal Bartoň on 01.05.2022.
//

#include "Figure.h"

Figure::Figure(Type type, Color color)
        : type(type), color(color) {}

Figure::~Figure() {}

Type Figure::getType() {
    return this->type;
}

Color Figure::getColor() {
    return this->color;
}
