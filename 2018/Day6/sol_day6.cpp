#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

typedef std::pair<int32_t, int32_t> t_coords;

int32_t ManhattanDistance(const t_coords &a, const t_coords &b);
int32_t MinDistance(const t_coords &a, const std::vector<t_coords> &points);
int32_t TotalDistance(const t_coords &a, const std::vector<t_coords> &points);
std::vector<int32_t> DistVector(const t_coords &a, const std::vector<t_coords> &points);

int32_t Part1(const std::vector<t_coords> &input, t_coords &pmin, t_coords &pmax);
int32_t Part2(const std::vector<t_coords> &input, t_coords &pmin, t_coords &pmax);

// needs cleaning up and simplifying

int main() {
    t_coords pos_min = {0, 0};
    t_coords pos_max = {0, 0};
    std::vector<t_coords> points;
    std::ifstream fin("input_day6.dat");

    int32_t posx, posy;
    while(fin >> posx >> posy) {
        if(pos_min.first == 0 || pos_min.first > posx)
            pos_min.first = posx;
        if(pos_min.second == 0 || pos_min.second > posy)
            pos_min.second = posy;
        if(pos_max.first == 0 || pos_max.first < posx)
            pos_max.first = posx;
        if(pos_max.second == 0 || pos_max.second < posy)
            pos_max.second = posy;
        points.push_back(std::make_pair(posx, posy));
    }

    int32_t width = pos_max.first - pos_min.first;
    int32_t height = pos_max.second - pos_min.second;
    pos_min.first -= width;
    pos_max.first += width;
    pos_min.second -= height;
    pos_max.second += height;

    cout << "Day 6, part 1: " << Part1(points, pos_min, pos_max) << endl;
    cout << "Day 6, part 2: " << Part2(points, pos_min, pos_max) << endl;

    return 0;
}

int32_t Part1(const std::vector<t_coords> &input, t_coords &pmin, t_coords &pmax) {
    t_coords pos = pmin;
    int32_t tmp;
    std::vector<int32_t> res;
    std::vector<int32_t> res1;
    res.resize(input.size());
    res1.resize(input.size());

    while(pos != pmax) {
        tmp = MinDistance(pos, input);
        if(tmp != -1)
            res[tmp]++;
        
        pos.first = pos.first + 1;
        if(pos.first > pmax.first) {
            pos.first = pmin.first;
            pos.second++;
        }
    }

    pmin.first -= 1;
    pmin.second -= 1;
    pmax.first += 1;
    pmax.second += 1;
    pos = pmin;
    while(pos != pmax) {
        tmp = MinDistance(pos, input);
        if(tmp != -1)
            res1[tmp]++;
        
        pos.first = pos.first + 1;
        if(pos.first > pmax.first) {
            pos.first = pmin.first;
            pos.second++;
        }
    }

    tmp = 0;
    for(int32_t idx = 0; idx < res.size(); ++idx)
        if(res[idx] == res1[idx] && res[idx] > tmp)
            tmp = res[idx];
    
    return tmp;
}

int32_t Part2(const std::vector<t_coords> &input, t_coords &pmin, t_coords &pmax) {
    t_coords pos = pmin;
    int32_t counter = 0;
    int32_t tmp;

    while(pos != pmax) {
        tmp = TotalDistance(pos, input);
        if(tmp < 10000)
            counter++;
        
        pos.first = pos.first + 1;
        if(pos.first > pmax.first) {
            pos.first = pmin.first;
            pos.second++;
        }
    }

    return counter;
}

int32_t MinDistance(const t_coords &a, const std::vector<t_coords> &points) {
    std::vector<int32_t> dist;
    int32_t tmpdist;

    dist = DistVector(a, points);
    int32_t mindist = dist[0];
    int32_t mdistcount = 1;
    int32_t mdistpos = 0;
    for(int32_t idx = 0; idx < points.size(); ++idx) {
        if(dist[idx] == mindist)
            mdistcount++;

        if(dist[idx] < mindist) {
            mindist = dist[idx];
            mdistcount = 1;
            mdistpos = idx;
        }
    }

    return mdistcount == 1 ? mdistpos : -1;
}

int32_t TotalDistance(const t_coords &a, const std::vector<t_coords> &points) {
    std::vector<int32_t> dist;
    dist = DistVector(a, points);

    int32_t tot = 0;
    for(int32_t idx = 0; idx < points.size(); ++idx)
        tot += dist[idx];
    
    return tot;
}

std::vector<int32_t> DistVector(const t_coords &a, const std::vector<t_coords> &points) {
    std::vector<int32_t> dist;
    dist.reserve(points.size());

    for(int32_t idx = 0; idx < points.size(); ++idx)
        dist[idx] = ManhattanDistance(points[idx], a);
    
    return dist;
}

int32_t ManhattanDistance(const t_coords &a, const t_coords &b) {
    return abs(a.first - b.first) + abs(a.second - b.second);
}