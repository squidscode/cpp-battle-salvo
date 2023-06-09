#pragma once

namespace Controller {
    class Controller {
    public:
        virtual ~Controller() {};
        virtual void Run() = 0;
    };
}