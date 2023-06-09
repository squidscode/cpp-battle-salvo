#pragma once

#include "../BoardViewer.hpp"
#include "../fancy/FancyBoardViewer.hpp"
#include <vector>

namespace View {
    class ColoredBoardViewer : public FancyBoardViewer {
    protected:
        virtual void InitializeCharacterMap(const Model::Board&, Iterator<Model::Ship>&);
    };
}

