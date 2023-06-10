#include "BattleSalvoRound.hpp"
#include <random>

#define min(x,y)    (x < y ? x : y)

using namespace Model;

BattleSalvoRound::BattleSalvoRound(Factory::PlayerFactory *pf1, Factory::PlayerFactory *pf2) {
    this->pf1 = pf1;
    this->pf2 = pf2;
}

bool validFreq(int freq[4], int min_val) {
    int tot = 0;
    for(int i = 0; i < 4; ++i){
        if(freq[i] <= 0) return false;
        tot += freq[i];
    }
    return tot <= min_val;
}

void BattleSalvoRound::Run(int min_size, int max_size, int rounds) {
    std::default_random_engine generator(time(NULL) + rand());
    std::uniform_int_distribution<int> width_height(min_size, max_size);
    auto new_wh = std::bind(width_height, generator);
    while(rounds--) {
        // Make players
        Model::Player *p1 = this->pf1->CreatePlayer();
        Model::Player *p2 = this->pf2->CreatePlayer();

        // Generate configs
        int width = new_wh(); int height = new_wh();
        std::uniform_int_distribution<int> ship_freq(1, min(width, height) - 3);
        int freq[4] = {-1,-1,-1,-1};
        while(!validFreq(freq, min(width, height))) {
            for(int i = 0; i < 4; ++i) freq[i] = ship_freq(generator);
        }
        Map<Model::ShipType, int> map;
        map.Insert(Model::ShipType::CARRIER, freq[0]);
        map.Insert(Model::ShipType::BATTLESHIP, freq[1]);
        map.Insert(Model::ShipType::DESTROYER, freq[2]);
        map.Insert(Model::ShipType::SUBMARINE, freq[3]);

        // Send setup
        Model::BattleSalvoGame bsg(p1, p2);
        bsg.Setup(width, height, &map);
        while(!bsg.GameOver()) {
            bsg.GameStep();
        }
        totalPlayerWins[0] += (bsg.GameResult(PLAYER_1) == WIN ? 1 : 0);
        totalPlayerWins[1] += (bsg.GameResult(PLAYER_2) == WIN ? 1 : 0);
        totalGamesPlayed += 1;
    }
}

int BattleSalvoRound::GetPlayerWins(GamePlayer gp) {
    return totalPlayerWins[(gp == PLAYER_1 ? 0 : 1)];
}

int BattleSalvoRound::GetGamesPlayed() {
    return totalGamesPlayed;
}