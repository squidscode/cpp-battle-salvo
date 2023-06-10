#include "GameAggregatorController.hpp"
#include "../../model/BattleSalvoRound.hpp"
#include <random>
#include <string>

using namespace Controller;

GameAggregatorController::GameAggregatorController(View::View* view, 
    int numTimes, Factory::PlayerFactory *pf1, Factory::PlayerFactory *pf2) {
    this->view = view;
    this->numTimes = numTimes;
    this->pf1 = pf1;
    this->pf2 = pf2;
}

void GameAggregatorController::Run() {
    Model::BattleSalvoRound bsr(pf1, pf2);
    bsr.Run(6, 14, this->numTimes);
    int total_player_wins[2] = {bsr.GetPlayerWins(PLAYER_1), bsr.GetPlayerWins(PLAYER_2)};
    int total_games_played = bsr.GetGamesPlayed();
    this->view->DisplayMessage("GAME STATISTICS");
    this->view->DisplayMessage("---------------");
    std::string stats1 = "Player 1 wins: " + std::to_string(total_player_wins[0]);
    std::string stats2 = "Player 2 wins: " + std::to_string(total_player_wins[1]);
    std::string stats3 = "Games played: " + std::to_string(total_games_played);
    std::string win_ratio1 = "Player 1 win ratio: " + std::to_string((double) total_player_wins[0] / total_games_played);
    std::string win_ratio2 = "Player 2 win ratio: " + std::to_string((double) total_player_wins[1] / total_games_played);
    std::string tie_ratio = "Tie ratio: " + std::to_string((double) (total_games_played - total_player_wins[0] - total_player_wins[1]) / total_games_played);
    this->view->DisplayMessage(stats3.c_str());
    this->view->DisplayMessage(stats1.c_str());
    this->view->DisplayMessage(stats2.c_str());
    this->view->DisplayMessage(win_ratio1.c_str());
    this->view->DisplayMessage(win_ratio2.c_str());
    this->view->DisplayMessage(tie_ratio.c_str());
}