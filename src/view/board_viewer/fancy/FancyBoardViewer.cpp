#include "FancyBoardViewer.hpp"
#include <string>

#define ifnh if(this->charMap[nxt.first][nxt.second] != "o") 

using namespace View;

std::string FancyBoardViewer::GetBoardString(const Model::Board& board, Iterator<Model::Ship>& ships) {
    const char LEFT_PADDING[] = "  ";
    std::string output = "";
    int width = board.GetWidth();
    int height = board.GetHeight();
    this->InitializeCharacterMap(board, ships);
    bool first = true;
    for(int x = -2; x < width; ++x) {
        if(!first) output += "\n";
        first = false;
        output += LEFT_PADDING;
        for(int y = -2; y < height; ++y) {
            if(x == -2) {
                output += y == -2 ? "  " :
                          y == -1 ? "| " :
                          std::to_string(y) + " ";
            } else if(x == -1) {
                output += y == -2 ? "- " :
                          y == -1 ? "+ " :
                                    "- ";
            } else {
                output += y == -2 ? std::to_string(x) + " " :
                          y == -1 ? "| " :
                                    this->charMap[x][y] + std::string(" ");
            }
        }
    }

    return output;
}

void FancyBoardViewer::InitializeCharacterMap(const Model::Board& board, Iterator<Model::Ship>& it) {
    int width = board.GetWidth();
    int height = board.GetHeight();
    this->charMap.resize(width, std::vector<std::string>());
    for(int x = 0; x < width; ++x) {
        this->charMap[x].resize(height, std::string());
        for(int y = 0; y < height; ++y) {
            Model::CellType c = board.GetCell(x, y);
            this->charMap[x][y] = c == Model::CellType::EMPTY ? " " :
                                  c == Model::CellType::HIT   ? "o" :
                                  c == Model::CellType::MISS  ? "x" :
                                                                "S";
        }
    }
    while(it.HasNext()) {
        const Model::Ship nxtShip = it.Next();
        Iterator<std::pair<int,int>> coords = nxtShip.GetPoints();
        std::pair<int,int> nxt = coords.Next();
        Model::Direction dir = nxtShip.GetDirection();
        ifnh this->charMap[nxt.first][nxt.second] = (dir == Model::Direction::HORIZONTAL ? "^" : "<");
        while(coords.HasNext()) {
            nxt = coords.Next();
            ifnh this->charMap[nxt.first][nxt.second] = (dir == Model::Direction::HORIZONTAL ? "H" : "I");
        }
        ifnh this->charMap[nxt.first][nxt.second] = (dir == Model::Direction::HORIZONTAL ? "v" : ">");
    }
}


/*
The concept:
    | 0 1 2 3
  - + - - - -
  0 | < I > ^
  1 |       H
  2 | x     o
  3 |       V

*/