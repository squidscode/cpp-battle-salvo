#pragma once

#include "CellType.hpp"

namespace Model {
    class Board {
    public:
        virtual bool ValidPosition(int x, int y) = 0;
        virtual CellType GetCell(int x, int y) = 0;
    };
}