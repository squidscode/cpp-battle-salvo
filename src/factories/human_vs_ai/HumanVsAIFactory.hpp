#include "../GameFactory.hpp"
#include "../../model/player/PlayerObserver.hpp"
#include "../../model/player/strategies/setup/SetupStrategy.hpp"
#include "../../model/player/strategies/shot/ShotStrategy.hpp"
#include "../../view/board_viewer/BoardViewer.hpp"
#include "../player_factories/ai_player_factory/AIPlayerFactory.hpp"
#include "../player_factories/manual_player_factory/ManualPlayerFactory.hpp"

namespace Factory {
    class HumanVsAIFactory : public GameFactory {
    public:
        HumanVsAIFactory();
        HumanVsAIFactory(Model::SetupStrategy*);
        HumanVsAIFactory(Model::ShotStrategy*);
        HumanVsAIFactory(Model::SetupStrategy*, Model::ShotStrategy*);
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
        Factory::ManualPlayerFactory *manualFactory;
        Factory::AIPlayerFactory *aiFactory;
        Model::SetupStrategy *setupStrat;
        Model::ShotStrategy *shotStrat;
    };
}