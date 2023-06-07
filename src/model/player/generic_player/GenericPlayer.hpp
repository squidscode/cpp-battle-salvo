#pragma once

#include "../ObservablePlayer.hpp"
#include <vector>

namespace Model {
    class GenericPlayer : public ObservablePlayer {
    public:
        GenericPlayer(char*);  // name, setup strategy, ShotReadable to ask for shots

        // Rule of 3:
        ~GenericPlayer();
        GenericPlayer(const GenericPlayer&);
        GenericPlayer& operator=(const GenericPlayer&);

        // Player Interface:
        virtual Iterator<Ship> Setup(int width, int height, Map<ShipType, int> *specifications) = 0;
        virtual Iterator<std::pair<int,int>> TakeShots() = 0;

        // Implements the following:
        virtual const char* Name();
        virtual Iterator<std::pair<int, int>> ReportDamage(Iterator<std::pair<int, int>> *opponentShots);
        virtual void SuccessfulHits(Iterator<std::pair<int,int>> *successfulShots);
        virtual void EndGame(GameResult result, char *reason);
    protected:
        void SetShips(Iterator<Ship>);
        void UpdateShots(Iterator<std::pair<int,int>>);
        virtual PlayerSnapshot *CreatePlayerSnapshot();
        int ShipsAlive();
 
        char name[20];
        Board *myBoard;
        Board *opponentBoard;
        std::vector<Ship> ships;
    };
}