#include "Maze.h"
#include <iostream>
#include <string>

bool Pos::operator==(const Pos &right) const {
    return (i == right.i && j == right.j);
}

Pos::Pos() : Pos(0, 0) {}

Pos::Pos(int i, int j) {
    this->i = i;
    this->j = j;
}

std::string Pos::to_String() {
    return (std::to_string(i) + "," + std::to_string(j));
}

Maze::Maze() = default;

Maze::Maze(int r, int c, char map[MAXLEN][MAXLEN]) {
    this->r = r;
    this->c = c;
    // 将map拷贝到this->map
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            this->map[i][j] = map[i][j];
        }
    }
}

int Maze::getRow() {
    return r;
}

void Maze::setRow(int row) {
    this->r = row;
}

int Maze::getCol() {
    return c;
}

void Maze::setCol(int col) {
    this->c = col;
}

void Maze::setMapValue(Pos pos, char value) {
    this->map[pos.i][pos.j] = value;
}

char Maze::getMapValue(Pos pos) {
    return map[pos.i][pos.j];
}

bool Maze::canPass(Pos pos) {
    return getMapValue(pos) == '.';
}


Block::Block() = default;

Block::Block(int ord, Pos seat, int di) {
    setBlock(ord, seat, di);
}

void Block::setBlock(int ord, Pos seat, int di) {
    this->ord = ord;
    this->seat = seat;
    this->di = di;
}

std::string Block::to_String() {
    return "(" + seat.to_String() + "," + std::to_string(di) + ")";
}

std::ostream &operator<<(std::ostream &output, Block block) {
    output << block.to_String();
    return output;
}