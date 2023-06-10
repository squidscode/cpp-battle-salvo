#include "PlayerFactory.hpp"

using namespace Factory;

PlayerFactory::~PlayerFactory() {
    delete player;
}

Model::Player *PlayerFactory::GetPlayer() {
    return this->player;
}

Model::Player *PlayerFactory::CreatePlayer() {
    this->DeletePlayer();
    this->player = this->NewPlayer();
    return this->player;
}

void PlayerFactory::DeletePlayer() {
    delete player;
}