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
    *this->out << "Welcome to the BattleSalvo Command Line Interface [BSCLI]!\n\n";
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
    std::string msg = "\nEnter the ship frequency as a line of " + std::to_string(size) + " numbers:";
    this->DisplayMessage(msg.c_str());
    this->ReadIntLine(buf, size);
}

void TextView::ShotReader(int buf[2], bool askAgain, bool help) {
    if(help)     this->DisplayMessage(std::string("Enter the shot as a line (ie. \"x y\")").c_str()); 
    if(askAgain) this->DisplayMessage(std::string("Invalid shot. Enter the shot as a line (ie. \"x y\")").c_str());
    this->ReadIntLine(buf, 2);
}

void TextView::DisplayBoard(char *str, const Model::Board& board, Iterator<Model::Ship> ships) {
    this->DisplayMessage(str);
    this->DisplayBoard(board, ships);
}

void TextView::DisplayBoard(const Model::Board& board, Iterator<Model::Ship> ships) {
    *this->out << this->bv->GetBoardString(board, ships) << "\n";
}

void TextView::ReadIntLine(int *buf, size_t size) {
    std::string str; // to avoid buffer-overflow, use std::string
    *this->out << "> "; this->out->flush();
    std::getline(*this->in, str);
    std::istringstream iss(str);
    for(size_t i = 0; i < size; ++i) {
        if(iss.fail()) {
            buf[i] = -1;
            return;
        }
        iss >> buf[i];
    }
}
