#include "../ShotStrategy.hpp"

namespace Model {
    class HeatMapStrategy : public ShotStrategy {
    public:
        HeatMapStrategy();
        HeatMapStrategy(ShotStrategy*, bool, int, bool, int);
        virtual Iterator<std::pair<int,int>> BuildShots(int, const Board&);
    private:
        bool ResortToDelegate(const Board&);
        ShotStrategy *delegate;
        bool enableDelegate;
        int minShotRatio;
        bool randomFreqSelection;
        int compound;
    };
}