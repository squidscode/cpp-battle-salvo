#pragma once

#include "../../../board/Ship.hpp"
#include "../../../../util/Map.hpp"

namespace Model {
    class SetupStrategy {
    public:
        virtual ~SetupStrategy() {};
        virtual Iterator<Ship> BuildSetup(int width, int height, Map<ShipType, int> *specifications) = 0;
    };
}