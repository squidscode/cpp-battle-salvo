#include "factories/GameFactory.hpp"
#include "factories/pa03/HumanVsAIFactory.hpp"

int main(int argc, char* argv[]) {
    Factories::GameFactory *gf = new Factories::HumanVsAIFactory();
    gf->CreateController()->Run();
}