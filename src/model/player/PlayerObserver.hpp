#pragma once

#include "PlayerSnapshot.hpp"

namespace Model {
    class PlayerObserver {
    public:
        // Default implementation give for each of the methods:
        virtual void PreSetup(PlayerSnapshot*) {};
        virtual void PostSetup(PlayerSnapshot*) {};
        virtual void PreTakeShots(PlayerSnapshot*) {};
        virtual void PostTakeShots(PlayerSnapshot*) {};
        virtual void PreReportDamage(PlayerSnapshot*) {};
        virtual void PostReportDamage(PlayerSnapshot*) {};
        virtual void PreSuccessfulHits(PlayerSnapshot*) {};
        virtual void PostSuccessfulHits(PlayerSnapshot*) {};
        virtual void PreEndGame(PlayerSnapshot*) {};
        virtual void PostEndGame(PlayerSnapshot*) {};
    };
}