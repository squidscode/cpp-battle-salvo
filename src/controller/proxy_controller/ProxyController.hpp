#pragma once

#include "../../../build/_deps/json-src/single_include/nlohmann/json.hpp"
#include "../Controller.hpp"
#include "GameType.hpp"
#include "../../factories/player_factories/PlayerFactory.hpp"

using json = nlohmann::json;

namespace Controller {
    class ProxyController : public Controller {
    public:
        ProxyController(const char* username, GameType gt, int socket_fd, Model::Player*); // the fds for the in and out
        virtual void Run();
    private:
        const char *username;
        GameType gameType;
        int socket_fd;
        Model::Player *player;
        void HandleReceivedMsg(const json&);
        void HandleJoin(const json&);
        void HandleSetup(const json&);
        void HandleTakeShots(const json&);
        void HandleReportDamage(const json&);
        void HandleSuccessfulHits(const json&);
        void HandleEndGame(const json&);
        json JsonTemplate(const char* method_name);
        void SendMsg(const json&);
    };
}

/*
  - parse string
  - handle join
  - handle setup
  - handle take-shots
  - handle report-damage
  - handle successful-hits
  - handle end-game
*/