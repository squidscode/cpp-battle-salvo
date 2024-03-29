#pragma once

#include "../view/View.hpp"
#include "../controller/Controller.hpp"
#include "../model/BattleSalvoGame.hpp"

namespace Factory {
    class GameFactory {
    public:
        virtual ~GameFactory() {};
        virtual View::View *CreateView() = 0;
        virtual Controller::Controller *CreateController() = 0;
        virtual Model::BattleSalvoGame *CreateBattleSalvoGame() = 0;
    };
}