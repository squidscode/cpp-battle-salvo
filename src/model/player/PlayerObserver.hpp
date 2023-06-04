#pragma once

#include "PlayerSnapshot.hpp"

namespace Model {
    class PlayerObserver {
    public:
        virtual void PreSetup(PlayerSnapshot*) = 0;
        virtual void PostSetup(PlayerSnapshot*) = 0;
        virtual void PreTakeShots(PlayerSnapshot*) = 0;
        virtual void PostTakeShots(PlayerSnapshot*) = 0;
        virtual void PreReportDamage(PlayerSnapshot*) = 0;
        virtual void PostReportDamage(PlayerSnapshot*) = 0;
        virtual void PreSuccessfulHits(PlayerSnapshot*) = 0;
        virtual void PostSuccessfulHits(PlayerSnapshot*) = 0;
        virtual void PreEndGame(PlayerSnapshot*) = 0;
        virtual void PostEndGame(PlayerSnapshot*) = 0;
    };
}