#pragma once

#include <utility>

namespace Model {
    enum ShipType : int {
        CARRIER=6, BATTLESHIP=5, DESTROYER=4, SUBMARINE=3
    };
}

namespace std {
    template <> struct std::hash<Model::ShipType> {
        size_t operator()(const Model::ShipType & x) const {
            return x;
        }
    };
}