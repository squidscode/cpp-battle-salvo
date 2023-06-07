#include "../ShotStrategy.hpp"

namespace Model {
    class RandomShot : public ShotStrategy {
    public:
        virtual Iterator<std::pair<int,int>> BuildShots(int, const Board&);
    };
}