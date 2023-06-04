#pragma once

namespace Model {
    enum CellType {
        SHIP, EMPTY, HIT, MISS
    };

    class Board {
    public:
        bool ValidPosition(int x, int y);
        CellType GetCell(int x, int y);
        void SetCell(int x, int y, CellType);
    };
}