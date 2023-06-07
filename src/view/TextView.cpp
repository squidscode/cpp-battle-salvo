#include "TextView.hpp"
#include <string>
#include <sstream>

using namespace View;

TextView::TextView(BoardViewer *bv, std::istream *in, std::ostream *out) {
    this->bv = bv;
    this->in = in;
    this->out = out;
}

void TextView::DisplayWelcomeMessage() {
    *this->out << "Welcome to the BattleSalvo Command Line Interface [CLI]!\n";
}

void TextView::DisplayMessage(const char *str) {
    *this->out << str << "\n";
}

void TextView::ReadWidthAndHeight(int buf[2]) {
    char msg[] = "Enter the width and the height of the board separated by a space in a single line:";
    this->DisplayMessage(msg);
    this->ReadIntLine(buf, 2);
}

void TextView::ReadShipTypeFrequency(int *buf, size_t size) {
    std::string msg = "Enter the ship frequency as a line of " + std::to_string(size) + " numbers:";
    this->DisplayMessage(msg.c_str());
    this->ReadIntLine(buf, size);
}

void TextView::ShotReader(int buf[2], bool askAgain) {
    if(!askAgain) this->DisplayMessage(std::string("Enter the shot as a line (ie. \"x y\")").c_str());
    else          this->DisplayMessage(std::string("Invalid shot. Enter the shot as a line (ie. \"x y\")").c_str());
    this->ReadIntLine(buf, 2);
}

void TextView::DisplayBoard(char *str, const Model::Board& board, Iterator<Model::Ship> ships) {
    this->DisplayMessage(str);
    *this->out << this->bv->GetBoardString(board, ships) << "\n";
}

void TextView::DisplayBoard(const Model::Board& board, Iterator<Model::Ship> ships) {
    char msg[] = "Board:";
    this->DisplayBoard(msg, board, ships);
}

void TextView::ReadIntLine(int *buf, size_t size) {
    char strBuf[10];
    this->in->getline(strBuf, sizeof(strBuf));
    std::istringstream iss(strBuf);
    for(size_t i = 0; i < size; ++i) {
        if(iss.fail()) {
            buf[i] = -1;
            return;
        }
        iss >> buf[i];
    }
}
