#pragma once

#include "../../model/board/Board.hpp"
#include "../../model/board/Ship.hpp"
#include <string>

namespace View {
    class BoardViewer {
    public:
        virtual ~BoardViewer() {};
        virtual std::string GetBoardString(const Model::Board&, Iterator<Model::Ship>&) = 0;
    };
}