#include "../GameFactory.hpp"
#include "../../controller/proxy_controller/ProxyController.hpp"

namespace Factory {
    class ServerFactory : public GameFactory {
    public:
        ~ServerFactory();
        // username, host, port, player factory.
        ServerFactory(const char*, Controller::GameType, const char*, int, PlayerFactory*);
        virtual View::View *CreateView();
        virtual Controller::Controller *CreateController();
        virtual Model::BattleSalvoGame *CreateBattleSalvoGame();
    private:
        Controller::Controller *controller;
        Model::Player *player;
        int client_fd;
    };
}