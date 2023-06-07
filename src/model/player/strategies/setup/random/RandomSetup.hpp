#include "../SetupStrategy.hpp"
#include "../../../../board/Board.hpp"

namespace Model {
    class RandomSetup : public SetupStrategy {
    public:
        virtual Iterator<Ship> BuildSetup(int width, int height, Map<ShipType, int> *specifications);
    private:
        void ClearBoard(Board&);
        bool FitsOnBoard(Board&, int, int, Direction, int);
        void PlaceShip(Board&, Ship);
    };
}