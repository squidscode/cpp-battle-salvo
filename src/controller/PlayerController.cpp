#include "PlayerController.hpp"

using namespace Controller;

PlayerController::PlayerController(View::View *view) {
    this->view = view;
}

void PlayerController::PostSetup(PlayerSnapshot* ps) {
    this->view->DisplayMessage("\nNo volleys have been exchanged on your opponent's board:");
    this->view->DisplayBoard(ps->GetOpponentBoard(), Iterator<Model::Ship>());
    this->view->DisplayMessage("Your board has been created: ");
    this->view->DisplayBoard(ps->GetMyBoard(), ps->GetMyShips());
}

void PlayerController::PostSuccessfulHits(PlayerSnapshot* ps) {
    this->view->DisplayMessage("A volley has been exchanged!");
    this->view->DisplayMessage("Your opponent's board:");
    this->view->DisplayBoard(ps->GetOpponentBoard(), Iterator<Model::Ship>());
    this->view->DisplayMessage("Your board:");
    this->view->DisplayBoard(ps->GetMyBoard(), ps->GetMyShips());
}

void PlayerController::PostEndGame(PlayerSnapshot* ps) {
    this->view->DisplayMessage("Seems like the game has ended!");
    this->view->DisplayMessage("Your opponent's board:");
    this->view->DisplayBoard(ps->GetOpponentBoard(), Iterator<Model::Ship>());
    this->view->DisplayMessage("Your board:");
    this->view->DisplayBoard(ps->GetMyBoard(), ps->GetMyShips());
}