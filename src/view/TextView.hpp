#pragma once

#include "View.hpp"
#include "cstdlib"
#include "../model/board/Board.hpp"
#include "board_viewer/BoardViewer.hpp"
#include <iostream>
#include <istream>

namespace View {
    class TextView : public View {
    public:
        TextView(BoardViewer*, std::istream*, std::ostream*);

        virtual void DisplayWelcomeMessage();
        virtual void DisplayMessage(const char *str);
        virtual void ReadWidthAndHeight(int buf[2]);
        virtual void ReadShipTypeFrequency(int *buf, size_t size);
        virtual void ShotReader(int buf[2], bool askAgain=false, bool help_msg=false);
        virtual void DisplayBoard(char *str, const Model::Board& board, Iterator<Model::Ship> ships);
        virtual void DisplayBoard(const Model::Board& board, Iterator<Model::Ship> ships);
        virtual void ReadIntLine(int *buf, size_t size);
    private:
        BoardViewer *bv;
        std::istream *in;
        std::ostream *out;
    };
}