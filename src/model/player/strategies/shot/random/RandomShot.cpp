#include "RandomShot.hpp"
#include <set>
#include <random>

using namespace Model;

Iterator<std::pair<int,int>> RandomShot::BuildShots(int numShots, const Board& opponentBoard) {
    int width = opponentBoard.GetWidth();
    int height = opponentBoard.GetHeight();
    std::vector<std::pair<int,int>> empty;
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            if(opponentBoard.GetCell(x,y) == CellType::EMPTY){
                empty.push_back({x,y});
            }
        }
    }
    std::default_random_engine generator(time(NULL) + rand());
    std::set<std::pair<int,int>> coords;
    for(int i = 0; i < numShots; ++i) {
        if(empty.size() == 0) break;
        std::uniform_int_distribution<int> picker(0, empty.size() - 1);
        int ind = picker(generator);
        std::pair<int,int> pt = empty[ind];
        empty.erase(empty.begin() + ind);
        coords.insert(pt);
    }
    return Iterator<std::pair<int,int>>(coords);
}