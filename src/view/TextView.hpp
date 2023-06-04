#pragma once

#include "View.hpp"
#include "cstdlib"
#include "../model/board/Board.hpp"

namespace View {
    class TextView : public View {
        virtual void DisplayWelcomeMessage();
        virtual void DisplayMessage(char *str);
        virtual void ReadWidthAndHeight(int *buf[2]);
        virtual void ReadShipTypeFrequency(int *buf, size_t size);
        virtual void DisplayBoard(char *str, Model::Board board);
        virtual void DisplayBoard(Model::Board board);
        virtual void ReadIntLine(int *buf, size_t size);
    };
}