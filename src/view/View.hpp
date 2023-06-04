#pragma once

#include "../model/Board.hpp"
#include <cstdlib>

namespace View {
    class View {
    public:
        virtual void DisplayWelcomeMessage() = 0;
        virtual void DisplayMessage(char *str) = 0;
        virtual void ReadWidthAndHeight(int *buf[2]) = 0;
        virtual void ReadShipTypeFrequency(int *buf, size_t size) = 0;
        virtual void DisplayBoard(char *str, Model::Board board) = 0;
        virtual void DisplayBoard(Model::Board board) = 0;
        virtual void ReadIntLine(int *buf, size_t size) = 0;
    };
}