#pragma once

#include "Controller.hpp"

namespace Controller {
    class GameAggregatorController : Controller {
        GameAggregatorController(int); // the number of tests that we want
        virtual void Run();
    };
}