#include "Board.hpp"
#include <assert.h>

using namespace Model;

Board::Board(int width, int height) {
    this->width = width;
    this->height = height;
    this->cells = new CellType*[width];
    for(int i = 0; i < width; ++i) {
        this->cells[i] = new CellType[height];
    }
    for(int i = 0; i < width; ++i){
        for(int j = 0; j < height; ++j) {
            this->cells[i][j] = CellType::EMPTY;
        }
    }
}

Board::~Board() {
    this->FreeCells();
}

Board::Board(const Board& other) : Board(other.width, other.height) {
    this->CopyCells(other.cells);
}

Board& Board::operator=(const Board& other) {
    this->FreeCells();
    this->width = other.width;
    this->height = other.height;
    this->cells = new CellType*[width];
    for(int i = 0; i < width; ++i) {
        this->cells[i] = new CellType[height];
    }
    this->CopyCells(other.cells);
    return *this;
}

void Board::FreeCells() {
    for(int i = 0; i < width; ++i) {
        delete[] this->cells[i];
    }
    delete[] this->cells;
}

void Board::CopyCells(CellType **other) {
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            this->cells[i][j] = other[i][j];
        }
    }
}

int Board::GetWidth() const {
    return this->width;
}

int Board::GetHeight() const {
    return this->height;
}

bool Board::ValidPosition(int x, int y) const {
    return 0 <= x && x < this->width and 0 <= y && y < this->height;
}

CellType Board::GetCell(int x, int y) const {
    assert(this->ValidPosition(x, y));
    return this->cells[x][y];
}

void Board::SetCell(int x, int y, CellType ct) {
    assert(this->ValidPosition(x, y));
    this->cells[x][y] = ct;
}
