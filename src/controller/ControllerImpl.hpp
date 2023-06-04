#pragma once

#include "Controller.hpp"

namespace Controller {
    class ControllerImpl : public Controller {
    public:
        virtual void Run();
    };
}