#pragma once

#include "../Controller.hpp"
#include "../../view/View.hpp"
#include "../../model/BattleSalvoGame.hpp"

namespace Controller {
    class GameController : public Controller {
    public:
        GameController(View::View*, Model::BattleSalvoGame*);
        virtual void Run(); 
    private:
        View::View *view;
        Model::BattleSalvoGame *game;
    };
}