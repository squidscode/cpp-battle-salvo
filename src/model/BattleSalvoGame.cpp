#include "BattleSalvoGame.hpp"

#define min(x,y)    (x > y ? y : x)

using namespace Model;

// NOTE: The caller owns both players.
BattleSalvoGame::BattleSalvoGame(Player *player1, Player *player2){
    this->player1 = player1;
    this->player2 = player2;
}

int BattleSalvoGame::Setup(int width, int height, Map<ShipType, int> *specifications) {
    assert(setupCalled == false);
    int numShipPoints = 0;
    int numShipsInGame = 0;
    Iterator<std::pair<ShipType,int>> it = specifications->Iterator();
    while(it.HasNext()) {
        std::pair<ShipType, int> pt = it.Next();
        numShipPoints += pt.first * pt.second;
        numShipsInGame += pt.second;
    }
    if(numShipsInGame > min(width, height)) {
        assert("INVALID GAME STATE!");
    }
    this->setupCalled = true;

    // Initialization
    this->numShipPoints[0] = numShipPoints;
    this->numShipPoints[1] = numShipPoints;
    this->player1->Setup(width, height, specifications);
    this->player2->Setup(width, height, specifications);
    return 0;
}

void print_iterator(Iterator<std::pair<int,int>> p) {
    printf("Points: ");
    while(p.HasNext()) {
        std::pair<int,int> pt = p.Next();
        printf("{%d,%d}", pt.first, pt.second);
    }
    printf("\n");
}

void BattleSalvoGame::GameStep(){
    assert(setupCalled == true);
    Iterator<std::pair<int,int>> shots1 = this->player1->TakeShots();
    Iterator<std::pair<int,int>> shots2 = this->player2->TakeShots();
    printf("shots1 "); print_iterator(shots1);
    printf("shots2 "); print_iterator(shots2);
    Iterator<std::pair<int,int>> suc1 = this->player1->ReportDamage(&shots2);
    Iterator<std::pair<int,int>> suc2 = this->player2->ReportDamage(&shots1);
    this->numShipPoints[0] -= suc1.Size();
    this->numShipPoints[1] -= suc2.Size();
    Iterator<std::pair<int,int>> cpy1 = suc1;
    Iterator<std::pair<int,int>> cpy2 = suc2;
    printf("suc1 "); print_iterator(cpy1);
    printf("suc2 "); print_iterator(cpy2);
    this->player1->SuccessfulHits(&suc2);
    this->player2->SuccessfulHits(&suc1);
    this->CheckGameOver();
}

void BattleSalvoGame::CheckGameOver() {
    assert(this->numShipPoints[0] >= 0 && this->numShipPoints[1] >= 0);
    if(this->numShipPoints[0] > 0 && this->numShipPoints[1] > 0) return;
    this->gameOver = true;
    if(this->numShipPoints[0] == 0 && this->numShipPoints[1] == 0) {
        char reason[] = "Both players eliminated their opponent in the same turn.";
        this->player1->EndGame(GameResult::TIE, reason);
        this->player2->EndGame(GameResult::TIE, reason);
    }else if(this->numShipPoints[0] == 0) {
        char reason1[] = "Your opponent eliminated you before you could eliminate them.";
        char reason2[] = "You eliminated your opponent before they could eliminate you.";
        this->player1->EndGame(GameResult::LOSE, reason1);
        this->player2->EndGame(GameResult::WIN, reason2);
    }else if(this->numShipPoints[1] == 0) {
        char reason1[] = "You eliminated your opponent before they could eliminate you.";
        char reason2[] = "Your opponent eliminated you before you could eliminate them.";
        this->player1->EndGame(GameResult::WIN, reason1);
        this->player2->EndGame(GameResult::LOSE, reason2);
    }
}

bool BattleSalvoGame::GameOver(){
    assert(setupCalled == true);
    return this->gameOver;
}