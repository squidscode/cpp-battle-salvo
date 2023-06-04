#include "ObservablePlayer.hpp"

using namespace Model;

void ObservablePlayer::Attach(PlayerObserver* po) {
    observers.insert(po);
}

void ObservablePlayer::Detach(PlayerObserver* po) {
    if(observers.count(po)) observers.erase(po);
}

void ObservablePlayer::NotifyObservers(void (PlayerObserver::*notificationFunction)(PlayerSnapshot*)) {
    PlayerSnapshot ps = this->CreatePlayerSnapshot();
    for(auto observer : observers) {
        (observer->*notificationFunction)(&ps);
    }
}