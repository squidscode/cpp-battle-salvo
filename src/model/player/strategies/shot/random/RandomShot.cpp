#include "RandomShot.hpp"
#include <random>

using namespace Model;

Iterator<std::pair<int,int>> RandomShot::BuildShots(int numShots, const Board& opponentBoard) {
    int width = opponentBoard.GetWidth();
    int height = opponentBoard.GetHeight();
    std::default_random_engine generator(time(NULL));
    std::default_random_engine generator1(time(NULL)+1);
    std::uniform_int_distribution<int> xRand(0, width - 1);
    std::uniform_int_distribution<int> yRand(0, height - 1);
    auto newX = std::bind(xRand, generator);
    auto newY = std::bind(yRand, generator1);
    std::list<std::pair<int,int>> coords;
    while(coords.size() < numShots) {
        std::pair<int,int> nxt = {newX(), newY()};
        if(opponentBoard.GetCell(nxt.first, nxt.second) == CellType::EMPTY){
            coords.push_front(nxt);
        }
    }
    return Iterator<std::pair<int,int>>(coords);
}