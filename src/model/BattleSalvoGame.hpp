#pragma once

#include "player/Player.hpp"
#include "GamePlayer.hpp"

namespace Model {
    class BattleSalvoGame {
    public:
        BattleSalvoGame(Player *player1, Player *player2);

        // -1 on failure, 0 on success.
        int Setup(int width, int height, Map<ShipType, int> *specifications);
        void GameStep();
        bool GameOver();
        GameResult GameResult(GamePlayer);
    private:
        Player *player1;
        Player *player2;
        bool setupCalled{false};
        bool gameOver{false};
        int numShipPoints[2]; // numShips[0] = # of player 1 ships, numShips[1] = # of player 2 ships
        void CheckGameOver();
    };
}