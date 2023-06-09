#include "RandomSetup.hpp"
#include <random>

#define MAX_LOOPS 100
#define GEN_DIR   (newDir() == 1 ? Direction::HORIZONTAL : Direction::VERTICAL)

using namespace Model;

void RandomSetup::ClearBoard(Board& board) {
    int width = board.GetWidth();
    int height = board.GetHeight();
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            board.SetCell(x, y, CellType::EMPTY);
        }
    }
}

bool RandomSetup::FitsOnBoard(Board& board, int x, int y, Direction dir, int size) {
    int width = board.GetWidth();
    int height = board.GetHeight();
    for(int i = 0; i < size; ++i) {
        if(x >= width || y >= height)             return false;
        if(board.GetCell(x, y) == CellType::SHIP) return false;
        x += (dir == Direction::HORIZONTAL ? 1 : 0);
        y += (dir == Direction::VERTICAL   ? 1 : 0);
    }
    return true;
}

void RandomSetup::PlaceShip(Board& board, Ship ship) {
    Iterator<std::pair<int,int>> it = ship.GetPoints();
    while(it.HasNext()) {
        auto pt = it.Next();
        board.SetCell(pt.first, pt.second, CellType::SHIP);
    }
}

Iterator<Ship> RandomSetup::BuildSetup(int width, int height, Map<ShipType, int> *specifications) {
    std::default_random_engine generator(time(NULL) + rand());
    std::default_random_engine generator1(time(NULL) + 1 + rand());
    std::default_random_engine generator2(time(NULL) + 2 + rand());
    std::uniform_int_distribution<int> direction(0, 1);
    std::uniform_int_distribution<int> xRand(0, width - 1);
    std::uniform_int_distribution<int> yRand(0, height - 1);
    auto newDir = std::bind(direction, generator);
    auto newX = std::bind(xRand, generator1);
    auto newY = std::bind(yRand, generator2);
    Iterator<std::pair<ShipType,int>> it = specifications->Iterator();
    Board brd = Board(width, height);
    std::list<Ship> ships;
    LOOP:while(it.HasNext()) {
        std::pair<ShipType,int> nxt = it.Next();
        int x = newX(); int y = newY(); Direction dir = GEN_DIR;
        int loop_counter = 0;
        while(nxt.second--) {
            while(!FitsOnBoard(brd, x, y, dir, nxt.first)) {
                x = newX(); y = newY(); dir = GEN_DIR;
                if(loop_counter++ >= MAX_LOOPS) {
                    ClearBoard(brd);
                    ships.clear();
                    it = specifications->Iterator();
                    goto LOOP;
                }
            }
            Ship newShip = Ship(nxt.first, dir, {x,y});
            ships.push_back(newShip);
            PlaceShip(brd, newShip);
        }
    }
    return Iterator<Ship>(ships);
}