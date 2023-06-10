#include "../GameFactory.hpp"
#include "../../model/player/PlayerObserver.hpp"
#include "../../model/player/strategies/setup/SetupStrategy.hpp"
#include "../../model/player/strategies/shot/ShotStrategy.hpp"
#include "../../view/board_viewer/BoardViewer.hpp"
#include "../player_factories/ai_player_factory/AIPlayerFactory.hpp"
#include "../player_factories/manual_player_factory/ManualPlayerFactory.hpp"

namespace Factory {
    class AggregatorFactory : public GameFactory {
    public:
        AggregatorFactory(int, Model::SetupStrategy*, Model::SetupStrategy*, Model::ShotStrategy*, Model::ShotStrategy*);
        ~AggregatorFactory(); // too lazy to implement rule of 3, do it yourself.
        virtual View::View *CreateView();
        virtual Controller::Controller *CreateController();
        virtual Model::BattleSalvoGame *CreateBattleSalvoGame();
    private:
        View::BoardViewer *boardViewer;
        View::View *view;
        Controller::Controller *controller;
        Factory::AIPlayerFactory *aiFactory1;
        Factory::AIPlayerFactory *aiFactory2;
    };
}