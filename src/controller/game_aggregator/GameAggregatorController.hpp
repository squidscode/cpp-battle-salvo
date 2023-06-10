#pragma once

#include "../Controller.hpp"
#include "../../factories/player_factories/PlayerFactory.hpp"
#include "../../view/View.hpp"
#include "../../model/BattleSalvoGame.hpp"

namespace Controller {
    class GameAggregatorController : public Controller {
    public:
        GameAggregatorController(View::View*, int, Factory::PlayerFactory*, Factory::PlayerFactory*); // the number of tests that we want
        virtual void Run();
    private:
        View::View *view;
        int numTimes;
        Factory::PlayerFactory *pf1;
        Factory::PlayerFactory *pf2;
    };
}