#pragma once

#include "../model/player/PlayerObserver.hpp"
#include "../view/TextView.hpp"

using namespace Model;

namespace Controller {
    class PlayerController : public PlayerObserver {
    public:
        virtual void PreSetup(PlayerSnapshot*);
        virtual void PostSetup(PlayerSnapshot*);
        virtual void PreTakeShots(PlayerSnapshot*);
        virtual void PostTakeShots(PlayerSnapshot*);
        virtual void PreReportDamage(PlayerSnapshot*);
        virtual void PostReportDamage(PlayerSnapshot*);
        virtual void PreSuccessfulHits(PlayerSnapshot*);
        virtual void PostSuccessfulHits(PlayerSnapshot*);
        virtual void PreEndGame(PlayerSnapshot*);
        virtual void PostEndGame(PlayerSnapshot*);
    };
}