#include "ManualPlayerFactory.hpp"
#include "../../../model/player/manual_player/ManualPlayer.hpp"

using namespace Factory;

ManualPlayerFactory::ManualPlayerFactory(char *name, Model::SetupStrategy* setup, View::ShotReadable *shotReadable) {
    this->name = name;
    this->setup = setup;
    this->shotReadable = shotReadable;
}

void ManualPlayerFactory::AttachPlayerObserver(Model::PlayerObserver *po) {
    this->playerObservers.insert(po);
}

void ManualPlayerFactory::DetachPlayerObserver(Model::PlayerObserver *po) {
    this->playerObservers.erase(po);
}

Model::Player *ManualPlayerFactory::NewPlayer() {
    Model::ObservablePlayer *op = new Model::ManualPlayer(this->name, this->setup, this->shotReadable);
    for(auto po : playerObservers) {
        op->Attach(po);
    }
    this->player = op;
    return this->player;
}