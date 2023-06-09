#pragma once

#include "../model/board/Board.hpp"
#include "../model/board/Ship.hpp"
#include "ShotReadable.hpp"
#include <cstdlib>

namespace View {
    class View : public ShotReadable {
    public:
        virtual ~View() {};
        virtual void DisplayWelcomeMessage() = 0;
        virtual void DisplayMessage(const char *str) = 0;
        virtual void ReadWidthAndHeight(int buf[2]) = 0;
        virtual void ReadShipTypeFrequency(int *buf, size_t size) = 0;
        virtual void ShotReader(int buf[2], bool askAgain=false, bool help_msg=false) = 0;
        virtual void DisplayBoard(char *str, const Model::Board& board, Iterator<Model::Ship> ships) = 0;
        virtual void DisplayBoard(const Model::Board& board, Iterator<Model::Ship> ships) = 0;
        virtual void ReadIntLine(int *buf, size_t size) = 0;
    };
}