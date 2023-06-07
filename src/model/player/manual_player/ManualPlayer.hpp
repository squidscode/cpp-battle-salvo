#pragma once

#include "../generic_player/GenericPlayer.hpp"
#include "../strategies/setup/SetupStrategy.hpp"
#include "../../../view/ShotReadable.hpp"

namespace Model {
    class ManualPlayer : public GenericPlayer {
    public:
        ManualPlayer(char*, SetupStrategy*, View::ShotReadable*);  // name, setup strategy, ShotReadable to ask for shots

        // Player Interface overriding:
        virtual Iterator<Ship> Setup(int width, int height, Map<ShipType, int> *specifications);
        virtual Iterator<std::pair<int,int>> TakeShots();
    private:
        SetupStrategy *setupStrategy;
        View::ShotReadable *shotReadable;
        bool hasNegOne(int *arr, size_t sz);
    };
}