#pragma once

#include "../../../../util/Iterator.hpp"
#include "../../../board/Board.hpp"

namespace Model {
    class ShotStrategy {
    public:
        virtual ~ShotStrategy() {};
        virtual Iterator<std::pair<int,int>> BuildShots(int, const Board&) = 0;
    };
}