#pragma once

#include <string>


namespace Model {
    enum PlayerStatus {RUNNING, WON, LOST, TIED};
    
    inline std::string convertPlayerStatus(PlayerStatus ps) {
        switch(ps) {
        case RUNNING:
            return std::string("RUNNING");
        case WON:
            return std::string("WON");
        case LOST:
            return std::string("LOST");
        case TIED:
            return std::string("TIED");
        }
        return std::string("INVALID");
    }
}