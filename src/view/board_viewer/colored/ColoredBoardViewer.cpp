#include "ColoredBoardViewer.hpp"
#include <unordered_set>

using namespace View;
const std::string GREEN = "\x1b[32;1m";
const std::string RED = "\x1b[31;1m";
const std::string BLUE = "\x1b[34;1m";
const std::string RESET = "\x1b[0m";

void ColoredBoardViewer::InitializeCharacterMap(const Model::Board& board, Iterator<Model::Ship>& ship) {
    FancyBoardViewer::InitializeCharacterMap(board, ship);
    std::unordered_set<std::string> green_strings{"<", ">", "^", "v", "H", "I"};
    std::unordered_set<std::string> red_strings{"o"};
    std::unordered_set<std::string> blue_strings{"~"};
    for(int x = 0; x < this->charMap.size(); ++x) {
        for(int y = 0; y < this->charMap[x].size(); ++y) {
            if(green_strings.count(this->charMap[x][y])) {
                this->charMap[x][y] = GREEN + this->charMap[x][y] + RESET;
            }else if(red_strings.count(this->charMap[x][y])) {
                this->charMap[x][y] = RED + this->charMap[x][y] + RESET;
            }else if(blue_strings.count(this->charMap[x][y])) {
                this->charMap[x][y] = BLUE + this->charMap[x][y] + RESET;
            }
        }
    }
}