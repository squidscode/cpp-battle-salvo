#pragma once

#include "../PlayerFactory.hpp"
#include "../../../model/player/strategies/setup/SetupStrategy.hpp"
#include "../../../view/ShotReadable.hpp"
#include "../../../model/player/PlayerObserver.hpp"
#include <unordered_set>

namespace Factory {
    class ManualPlayerFactory : public PlayerFactory {
    public:
        ManualPlayerFactory(char*, Model::SetupStrategy*, View::ShotReadable*); // NOTE: This factory does not own the setup strategy.
        void AttachPlayerObserver(Model::PlayerObserver*);
        void DetachPlayerObserver(Model::PlayerObserver*);
    protected:
        virtual Model::Player *NewPlayer();
    private:
        char *name;
        Model::SetupStrategy *setup;
        View::ShotReadable *shotReadable;
        std::unordered_set<Model::PlayerObserver*> playerObservers;
    };
}