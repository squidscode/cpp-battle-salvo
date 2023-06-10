#pragma once

#include "../PlayerFactory.hpp"
#include "../../../model/player/strategies/setup/SetupStrategy.hpp"
#include "../../../model/player/strategies/shot/ShotStrategy.hpp"
#include "../../../model/player/PlayerObserver.hpp"
#include <unordered_set>

namespace Factory {
    class AIPlayerFactory : public PlayerFactory {
    public:
        AIPlayerFactory(char*, Model::SetupStrategy*, Model::ShotStrategy*);    // NOTE: This factory does not own these strategies.
        void AttachPlayerObserver(Model::PlayerObserver*);
        void DetachPlayerObserver(Model::PlayerObserver*);
    protected:
        virtual Model::Player *NewPlayer();
    private:
        char *name;
        Model::SetupStrategy *setup;
        Model::ShotStrategy *shot;
        std::unordered_set<Model::PlayerObserver*> playerObservers;
   };
}