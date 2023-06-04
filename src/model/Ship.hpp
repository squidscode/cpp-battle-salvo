#pragma once

namespace Model {
    enum ShipType {};

    class Ship {
    public:
        virtual ShipType GetShipType() = 0;
    };
}