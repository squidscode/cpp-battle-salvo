#include "Ship.hpp"
#include <vector>

using namespace Model;

Ship::Ship(ShipType shipType, Direction direction, std::pair<int,int> topLeftCoord) {
    this->st = shipType;
    this->dir = direction;
    this->topLeftCoord = topLeftCoord;
}

ShipType Ship::GetShipType() const {
    return this->st;
}

Direction Ship::GetDirection() const {
    return this->dir;
}

bool Ship::Intersects(const Ship& other) const {
    std::pair<int,int> curCoord = topLeftCoord;
    std::pair<int,int> otherBotLeft = other.GetBotLeft();
    for(int i = 0; i < this->st; ++i) {
        if(curCoord.first >= other.topLeftCoord.first and curCoord.second >= other.topLeftCoord.second
            and curCoord.first <= otherBotLeft.first and curCoord.second >= otherBotLeft.second){
            // Intersecting!
            return true;
        }

        // Move to next coordinate:
        curCoord.first += (this->dir == HORIZONTAL ? 1 : 0);
        curCoord.second += (this->dir == VERTICAL ? 1 : 0);
    }
    return false;
}

Iterator<std::pair<int,int>> Ship::GetPoints() const {
    std::vector<std::pair<int,int>> pts;
    std::pair<int,int> curCoord = this->topLeftCoord;
    for(int i = 0; i < this->st; ++i) {
        pts.push_back(curCoord);

        // Move to next coordinate:
        curCoord.first += (this->dir == HORIZONTAL ? 1 : 0);
        curCoord.second += (this->dir == VERTICAL ? 1 : 0);
    }
    return Iterator<std::pair<int,int>>(pts);
}

std::pair<int,int> Ship::GetBotLeft() const {
    return std::pair<int,int>{this->topLeftCoord.first + (this->dir == HORIZONTAL ? this->st : 0),
        this->topLeftCoord.second + (this->dir == VERTICAL ? this->st : 0)};
}

std::pair<int,int> Ship::GetTopLeftCoord() const {
    return this->topLeftCoord;
}