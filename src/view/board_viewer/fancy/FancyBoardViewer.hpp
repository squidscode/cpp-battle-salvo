#pragma once

#include "../BoardViewer.hpp"
#include <vector>

namespace View {
    class FancyBoardViewer : public BoardViewer {
    public:
        virtual std::string GetBoardString(const Model::Board&, Iterator<Model::Ship>&);
    protected:
        std::vector<std::vector<std::string>> charMap;
        virtual void InitializeCharacterMap(const Model::Board&, Iterator<Model::Ship>&);
    };
}


/*

The concept:

    | 0 1 2 3
  - + - - - -
  0 | < I > ^
  1 |       H
  2 | x     o
  3 |       V

*/