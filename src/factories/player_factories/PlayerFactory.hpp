#pragma once

#include "../../model/player/Player.hpp"

namespace Factory {
    class PlayerFactory {
    public:
        virtual ~PlayerFactory();
        virtual Model::Player *GetPlayer();
        virtual Model::Player *CreatePlayer();
    protected:
        virtual Model::Player *NewPlayer() = 0;
        virtual void DeletePlayer();
        Model::Player *player;
    };
}