#include "FancyBoardViewer.hpp"
#include <string>

#define ifnh   if(this->charMap[nxt.first][nxt.second] != "o") 
#define pad(x) force_fit(x, target_size)

using namespace View;

std::string force_fit(std::string target, int sz) {
    if(target.size() < sz) {
        std::string padding(" ");
        while(target.size() + padding.size() < sz) padding += " ";
        return target + padding;
    }else if(target.size() == sz) {
        return target;
    }else{
        return target.substr(0, sz);
    }
}

std::string FancyBoardViewer::GetBoardString(const Model::Board& board, Iterator<Model::Ship>& ships) {
    const char LEFT_PADDING[] = "  ";
    std::string output = "";
    int width = board.GetWidth();
    int height = board.GetHeight();
    int target_size = 2;
    if(width > 10 || height > 10) target_size = 3;
    this->InitializeCharacterMap(board, ships);
    bool first = true;
    for(int y = -2; y < height; ++y) {
        if(!first) output += "\n";
        first = false;
        output += LEFT_PADDING;
        for(int x = -2; x < width; ++x) {
            if(x == -2) {
                output += y == -2 ? pad("  ") :
                          y == -1 ? pad("- ") :
                          pad(std::to_string(y) + " ");
            } else if(x == -1) {
                output += y == -1 ? pad("+ ") :
                                    pad("| ");
            } else {
                output += y == -2 ? pad(std::to_string(x) + " ") :
                          y == -1 ? pad("- ") :
                                    this->charMap[x][y] + force_fit(std::string(" "), target_size - 1);
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
                                  c == Model::CellType::MISS  ? "~" :
                                                                "S";
        }
    }
    while(it.HasNext()) {
        const Model::Ship nxtShip = it.Next();
        Iterator<std::pair<int,int>> coords = nxtShip.GetPoints();
        std::pair<int,int> nxt = coords.Next();
        Model::Direction dir = nxtShip.GetDirection();
        ifnh this->charMap[nxt.first][nxt.second] = (dir == Model::Direction::HORIZONTAL ? "<" : "^");
        while(coords.HasNext()) {
            nxt = coords.Next();
            ifnh this->charMap[nxt.first][nxt.second] = (dir == Model::Direction::HORIZONTAL ? "I" : "H");
        }
        ifnh this->charMap[nxt.first][nxt.second] = (dir == Model::Direction::HORIZONTAL ? ">" : "v");
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