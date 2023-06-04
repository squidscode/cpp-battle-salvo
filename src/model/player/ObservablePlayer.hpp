#pragma once

#include "Player.hpp"
#include "PlayerObserver.hpp"
#include "PlayerSnapshot.hpp"
#include <unordered_set>

namespace Model {
    class ObservablePlayer : public Player {
    public:
        void Attach(PlayerObserver* po);
        void Detach(PlayerObserver* po);
        void NotifyObservers(void (PlayerObserver::*notificationFunction)(PlayerSnapshot*));
    protected:
        virtual PlayerSnapshot CreatePlayerSnapshot() = 0;
    private:
        std::unordered_set<PlayerObserver*> observers;
    };
}