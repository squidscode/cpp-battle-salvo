#include "PlayerController.hpp"

using namespace Controller;

PlayerController::PlayerController(View::View *view) {
    this->view = view;
}

void PlayerController::PostSetup(PlayerSnapshot* ps) {
    this->view->DisplayMessage("\n\nNo volleys have been exchanged.\nYour opponent's board:");
    this->view->DisplayBoard(ps->GetOpponentBoard(), Iterator<Model::Ship>());
    this->view->DisplayMessage("\nYour board has been created: ");
    this->view->DisplayBoard(ps->GetMyBoard(), ps->GetMyShips());
}

void PlayerController::PostSuccessfulHits(PlayerSnapshot* ps) {
    this->view->DisplayMessage("\n\nA volley has been exchanged!\nYour opponent's board:");
    this->view->DisplayBoard(ps->GetOpponentBoard(), Iterator<Model::Ship>());
    this->view->DisplayMessage("\nYour board:");
    this->view->DisplayBoard(ps->GetMyBoard(), ps->GetMyShips());
}

void PlayerController::PostEndGame(PlayerSnapshot* ps) {
    this->view->DisplayMessage(("\n\nThe game has ended with status ["
        + convertPlayerStatus(ps->GetPlayerStatus()) + "]\nYour opponent's board:").c_str());
    this->view->DisplayBoard(ps->GetOpponentBoard(), Iterator<Model::Ship>());
    this->view->DisplayMessage("\nYour board:");
    this->view->DisplayBoard(ps->GetMyBoard(), ps->GetMyShips());
}