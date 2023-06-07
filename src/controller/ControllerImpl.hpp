#pragma once

#include "Controller.hpp"
#include "../view/View.hpp"
#include "../model/BattleSalvoGame.hpp"

namespace Controller {
    class ControllerImpl : public Controller {
    public:
        ControllerImpl(View::View*, Model::BattleSalvoGame*);
        virtual void Run(); 
    private:
        View::View *view;
        Model::BattleSalvoGame *game;
    };
}