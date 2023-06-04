#pragma once

#include "../../model/BattleSalvoGame.hpp"

namespace Controller {
    class BattleSalvoGameCommand {
    public:
        virtual void act(Model::BattleSalvoGame*) = 0;
    };
}