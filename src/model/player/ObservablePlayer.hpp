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
        /**
         * @brief Create a Player Snapshot object
         * @attention The caller is responsible for calling free on the pointer.
         * 
         * @return PlayerSnapshot* a pointer to the created PlayerSnapshot.
         */
        virtual PlayerSnapshot *CreatePlayerSnapshot() = 0;
        PlayerStatus status{RUNNING};
    private:
        std::unordered_set<PlayerObserver*> observers;
    };
}