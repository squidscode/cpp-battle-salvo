#include "HeatMap.hpp"
#include "../random/RandomShot.hpp"
#include <vector>
#include <math.h>
#include <map>
#include <iostream>
#include <algorithm>
#include <random>
#include <iomanip>

typedef std::vector<std::vector<std::vector<std::vector<bool>>>> quad_bvec;
typedef std::vector<std::vector<int>> bi_ivec;
typedef std::vector<std::pair<int, std::pair<int,int>>> pp_vec;

using namespace Model;

void construct_tlheatmap(quad_bvec&, const Board&);
void construct_heatmap(quad_bvec&, bi_ivec&, const Board&, int);
void print_tlheatmap(quad_bvec&);
void print_heatmap(bi_ivec&);
void construct_heatmap_positions(bi_ivec&, std::vector<std::pair<int,std::pair<int,int>>>&);
Iterator<std::pair<int,int>> handleRandomFreq(int, pp_vec&, const Board&);

HeatMapStrategy::HeatMapStrategy(ShotStrategy *shot, bool enableDelegate, int minTotalShots, bool randomFreq,
    int compound) {
    this->enableDelegate = enableDelegate;
    this->minShotRatio = minTotalShots;
    this->delegate = shot;
    this->randomFreqSelection = randomFreq;
    this->compound = compound;
}

HeatMapStrategy::HeatMapStrategy() : HeatMapStrategy(new RandomShot(), true, 50, false, 0) {}

Iterator<std::pair<int,int>> HeatMapStrategy::BuildShots(int num_shots, const Board& board) {
    if(this->enableDelegate && this->ResortToDelegate(board)) return delegate->BuildShots(num_shots, board);
    int width = board.GetWidth();
    int height = board.GetHeight();
    quad_bvec tlpos_heatmap; // int[right / left][ 3, 4, 5, 6 ]
    tlpos_heatmap.resize(width);
    for(int i = 0; i < width; ++i) {
        for(int j = 0; j < height; ++j) {
            tlpos_heatmap[i].push_back({{0,0,0,0},{0,0,0,0}});
        }
    }
    construct_tlheatmap(tlpos_heatmap, board);
    // print_tlheatmap(tlpos_heatmap);

    bi_ivec heatmap;
    heatmap.resize(width);
    for(int i = 0; i < width; ++i) heatmap[i].resize(height);
    construct_heatmap(tlpos_heatmap, heatmap, board, this->compound);
    print_heatmap(heatmap);

    // Sort heatmap
    pp_vec heatmap_positions;
    construct_heatmap_positions(heatmap, heatmap_positions);
    std::sort(heatmap_positions.begin(), heatmap_positions.end());

    if(this->randomFreqSelection) {
        return handleRandomFreq(num_shots, heatmap_positions, board);
    }

    std::vector<std::pair<int,int>> shots;
    for(auto val = heatmap_positions.rbegin(); val != heatmap_positions.rend(); ++val) {
        auto pos = val->second;
        if(board.GetCell(pos.first, pos.second) == CellType::EMPTY)
            shots.push_back(pos);
        if(shots.size() == num_shots) break;
    }
    return Iterator<std::pair<int,int>>(shots);
}

Iterator<std::pair<int,int>> handleRandomFreq(int num_shots, pp_vec& positions, const Board& board) {
    std::map<int, std::vector<std::pair<int,int>>> freqMap;
    for(auto posp : positions) {
        if(board.GetCell(posp.second.first, posp.second.second) != CellType::EMPTY) continue;
        if(freqMap.count(posp.first)) freqMap[posp.first].push_back(posp.second);
        else                             freqMap[posp.first] = std::vector<std::pair<int,int>>{posp.second};
    }
    std::default_random_engine generator(time(NULL) + rand());
    std::vector<std::pair<int,int>> shots;
    for(auto freq_vec = freqMap.rbegin(); freq_vec != freqMap.rend(); ++freq_vec) {
        while(freq_vec->second.size() && shots.size() < num_shots) {
            std::uniform_int_distribution<int> picker(0, freq_vec->second.size() - 1);
            int nxt_val = picker(generator);
            shots.push_back(freq_vec->second[nxt_val]);
            freq_vec->second.erase(freq_vec->second.begin() + nxt_val);
        }
    }
    return shots;
}

// Simple resort to delegate method: resort to delegate when no hits found on board.
bool HeatMapStrategy::ResortToDelegate(const Board& board) {
    int width = board.GetWidth();
    int height = board.GetHeight();
    int total_hits = 0; int total_shots = 0;
    for(int x = 0; x < width; ++x) {
        for(int y = 0; y < height; ++y) {
            CellType ct = board.GetCell(x, y);
            if(ct == CellType::HIT) total_hits += 1;
            if(ct == CellType::HIT || ct == CellType::MISS) total_shots += 1;
        }
    }
    return total_hits == 0 || total_shots < width * height / this->minShotRatio;
}

void print_heatmap(bi_ivec& hmap) {
    std::cerr << "HEATMAP : \n";
    for(int y = 0; y < hmap[0].size(); ++y) {
        for(int x = 0; x < hmap.size(); ++x) {
            std::cerr << std::setw(4) << hmap[x][y] << "  ";
        }
        std::cerr << "\n";
    }
    std::cerr << "\n";
}

char convertTF(bool b) {
    return (b ? 't' : 'f');
}

void print_tlheatmap(quad_bvec& qbv) {
    std::cerr << "TL HEATMAP : \n";
    for(int y = 0; y < qbv[0].size(); ++y) {
        for(int x = 0; x < qbv.size(); ++x) {
            std::cerr << convertTF(qbv[x][y][0][0]) << convertTF(qbv[x][y][0][1])
                << convertTF(qbv[x][y][0][2]) << convertTF(qbv[x][y][0][3])
                << '-' << convertTF(qbv[x][y][1][0]) << convertTF(qbv[x][y][1][1])
                << convertTF(qbv[x][y][1][2]) << convertTF(qbv[x][y][1][3]) << " ";
        }
        std::cerr << "\n";
    }
    std::cerr << "\n";
}

void construct_tlheatmap(quad_bvec& heatmap, const Board& board) {
    for(int x = 0; x < heatmap.size(); ++x) {
        for(int y = 0; y < heatmap[0].size(); ++y) {
            for(int dx = 0; dx <= 6; ++dx) {
                if(!board.ValidPosition(x+dx, y) || board.GetCell(x + dx, y) == CellType::MISS) break;
                if(3 <= dx) heatmap[x][y][0][dx - 3] = true;
                // printf("(3 <= %d) ASSIGNING %d %d to true\n", dx, x, y);
            }
            for(int dy = 0; dy <= 6; ++dy) {
                if(!board.ValidPosition(x, y+dy) || board.GetCell(x, y + dy) == CellType::MISS)
                    break;
                if(3 <= dy) heatmap[x][y][1][dy - 3] = true;
                // printf("(3 <= %d) ASSIGNING %d %d to true\n", dy, x, y);
            }
        }
    }
}

void construct_heatmap(quad_bvec& tlmap, bi_ivec& hmap, const Board& board, int comp) {
    // 5 nested loops!!!!!!
    for(int x = 0; x < tlmap.size(); ++x) {
        for(int y = 0; y < tlmap[0].size(); ++y) {
            for(int rl = 0; rl < 2; ++rl) {
                for(int sh = 0; sh < 4; ++sh) {
                    if(tlmap[x][y][rl][sh] == false) break;
                    int inc = 1;
                    int total_hits = 0;
                    for(int i = 0; i < sh + 3; ++i) {
                        // go through the span of the possible ships, determine if a cell that has been hit is contained, if it exists
                        // increment the increment by `comp`.
                        if(board.GetCell(x + (rl ? 0 : i), y + (rl ? i : 0)) == CellType::HIT)
                            inc += comp;
                    }
                    for(int i = 0; i < sh + 3; ++i) {
                        hmap[x + (rl ? 0 : i)][y + (rl ? i : 0)] += inc;
                    }
                }
            }
        }
    }
}

void construct_heatmap_positions(bi_ivec& hmap, std::vector<std::pair<int,std::pair<int,int>>>& pos) {
    for(int x = 0; x < hmap.size(); ++x) {
        for(int y = 0; y < hmap[0].size(); ++y) {
            pos.push_back({hmap[x][y], {x,y}});
        }
    }
}