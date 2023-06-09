#include "../GameFactory.hpp"
#include "../../model/player/PlayerObserver.hpp"
#include "../../model/player/strategies/setup/SetupStrategy.hpp"
#include "../../model/player/strategies/shot/ShotStrategy.hpp"
#include "../../view/board_viewer/BoardViewer.hpp"

namespace Factories {
    class HumanVsAIFactory : public GameFactory {
    public:
        HumanVsAIFactory();
        ~HumanVsAIFactory(); // too lazy to implement rule of 3, do it yourself.
        virtual View::View *CreateView();
        virtual Controller::Controller *CreateController();
        virtual Model::BattleSalvoGame *CreateBattleSalvoGame();
    private:
        View::BoardViewer *boardViewer;
        View::View *view;
        Controller::Controller *controller;
        Model::PlayerObserver *playerObserver;
        Model::BattleSalvoGame *model;
        Model::Player *player1;
        Model::Player *player2;
        Model::SetupStrategy *setupStrat;
        Model::ShotStrategy *shotStrat;
    };
}