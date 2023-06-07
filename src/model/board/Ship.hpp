#pragma once

#include <utility>
#include "../../util/Iterator.hpp"
#include "ShipType.hpp"

namespace Model {
    enum Direction {HORIZONTAL, VERTICAL};

    class Ship {
    public:
        Ship(ShipType, Direction, std::pair<int,int>);
        ShipType GetShipType() const;
        Direction GetDirection() const;
        bool Intersects(const Ship&);
        Iterator<std::pair<int,int>> GetPoints() const;
    private:
        ShipType st;
        Direction dir;
        std::pair<int,int> topLeftCoord;
        std::pair<int,int> GetBotLeft() const;
    };
}

