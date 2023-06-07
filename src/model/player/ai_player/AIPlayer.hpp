#pragma once

#include "../generic_player/GenericPlayer.hpp"
#include "../strategies/shot/ShotStrategy.hpp"
#include "../strategies/setup/SetupStrategy.hpp"

namespace Model {
    class AIPlayer : public GenericPlayer {
    public:
        AIPlayer(char*, SetupStrategy*, ShotStrategy*);   // AI name, SetupStrategy, and ShotStrategy.

        // Player Interface overriding:
        virtual Iterator<Ship> Setup(int width, int height, Map<ShipType, int> *specifications);
        virtual Iterator<std::pair<int,int>> TakeShots();
    private:
        char name[20];
        SetupStrategy *setupStrategy;
        ShotStrategy *shotStrategy;
    };
}