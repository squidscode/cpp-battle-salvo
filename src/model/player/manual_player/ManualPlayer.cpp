#include "ManualPlayer.hpp"
#include "../PlayerObserver.hpp"
#include <utility>
#include <vector>
#include <set>

#define ifst1 this->opponentBoard->GetCell(shots[curShot][0], shots[curShot][1])
#define ifst hasNegOne(shots[curShot], 2) || shots[curShot][0] < 0 || shots[curShot][1] < 0 \
    || shots[curShot][0] >= this->myBoard->GetWidth() || shots[curShot][1] >= this->myBoard->GetHeight() \
    || seen.count({shots[curShot][0], shots[curShot][1]}) > 0

using namespace Model;

ManualPlayer::ManualPlayer(char *name, SetupStrategy *ss, View::ShotReadable *sr) : GenericPlayer{name} {
    this->setupStrategy = ss;
    this->shotReadable = sr;
}

Iterator<Ship> ManualPlayer::Setup(int width, int height, Map<ShipType, int> *specifications) {
    this->NotifyObservers(&PlayerObserver::PreSetup);
    Iterator<Ship> ret = this->setupStrategy->BuildSetup(width, height, specifications);
    this->myBoard = new Board(width, height);
    this->opponentBoard = new Board(width, height);
    this->SetShips(ret);
    this->NotifyObservers(&PlayerObserver::PostSetup);
    return ret;
}


bool ManualPlayer::hasNegOne(int *arr, size_t sz) {
    for(size_t i = 0; i < sz; ++i) {
        if(arr[i] < 0) return true;
    }
    return false;
}

Iterator<std::pair<int,int>> ManualPlayer::TakeShots() {
    this->NotifyObservers(&PlayerObserver::PreTakeShots);
    int shipsAlive = this->ShipsAlive();
    int **shots = new int*[shipsAlive];
    for(int i = 0; i < shipsAlive; ++i) shots[i] = new int[2];
    for(int i = 0; i < shipsAlive; ++i) {
        shots[i][0] = -1;
        shots[i][1] = -1;
    }

    int curShot = 0; bool failed = false; bool first = true;
    std::set<std::pair<int,int>> seen;

    while(curShot < shipsAlive && (ifst || ifst1 == Model::HIT || ifst1 == Model::MISS)) {
        this->shotReadable->ShotReader(shots[curShot], failed, first); first = false;
        if(ifst || ifst1 == Model::HIT || ifst1 == Model::MISS) (failed = true);
        else                                                    (failed = false, seen.insert({shots[curShot][0], shots[curShot][1]}), curShot++);
    }

    std::vector<std::pair<int,int>> vshots;
    for(int i = 0; i < shipsAlive; ++i) vshots.push_back({shots[i][0], shots[i][1]});
    for(int i = 0; i < shipsAlive; ++i) delete[] shots[i];
    delete[] shots;

    auto it = Iterator<std::pair<int,int>>(vshots);
    this->UpdateShots(it);
    this->NotifyObservers(&PlayerObserver::PostTakeShots);
    return it;
}
