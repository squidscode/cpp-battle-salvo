#include "AIPlayerFactory.hpp"
#include "../../../model/player/ai_player/AIPlayer.hpp"

using namespace Factory;

AIPlayerFactory::AIPlayerFactory(char *name, Model::SetupStrategy* setup, Model::ShotStrategy* shot) {
    this->name = name;
    this->setup = setup;
    this->shot = shot;
}

void AIPlayerFactory::AttachPlayerObserver(Model::PlayerObserver *po) {
    this->playerObservers.insert(po);
}

void AIPlayerFactory::DetachPlayerObserver(Model::PlayerObserver *po) {
    this->playerObservers.erase(po);
}

Model::Player *AIPlayerFactory::NewPlayer() {
    Model::ObservablePlayer *op = new Model::AIPlayer(this->name, this->setup, this->shot);
    for(auto po : playerObservers) {
        op->Attach(po);
    }
    this->player = op;
    return this->player;
}