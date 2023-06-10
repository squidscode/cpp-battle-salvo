#pragma once

#include "BattleSalvoGame.hpp"
#include "../factories/player_factories/PlayerFactory.hpp"

namespace Model {
    class BattleSalvoRound {
    public:
        BattleSalvoRound(Factory::PlayerFactory*, Factory::PlayerFactory*);
        void Run(int width, int height, int rounds);
        int GetPlayerWins(GamePlayer gp);
        int GetGamesPlayed();
    private:
        Factory::PlayerFactory *pf1;
        Factory::PlayerFactory *pf2;
        int totalPlayerWins[2]{0, 0};
        int totalGamesPlayed{0};
    };
}