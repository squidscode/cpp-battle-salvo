#pragma once

namespace Model {
    enum CellType : int {
        SHIP, EMPTY, HIT, MISS
    };

    class Board {
    public:
        Board(int width, int height);

        // Rule of 3:
        ~Board();
        Board(const Board&);
        Board& operator=(const Board&);

        int GetWidth() const;
        int GetHeight() const;
        bool ValidPosition(int x, int y) const;
        CellType GetCell(int x, int y) const;
        void SetCell(int x, int y, CellType);
    private:
        int height;
        int width;
        CellType **cells;
        void FreeCells();
        void CopyCells(CellType **other);
    };
}