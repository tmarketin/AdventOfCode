#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

typedef std::pair<int32_t, int32_t> t_coords;
typedef std::pair<int32_t, int32_t> t_spacing;

class Star {
public:
    t_coords m_pos;
    t_coords m_vel;

    Star(int32_t r, int32_t c, int32_t vr, int32_t vc) {
        m_pos = std::make_pair(r, c);
        m_vel = std::make_pair(vr, vc);
    }

    t_coords GetPos() {
        return m_pos;
    }

    void Move() {
        m_pos.first += m_vel.first;
        m_pos.second += m_vel.second;

        return;
    }

    void MoveBack() {
        m_pos.first -= m_vel.first;
        m_pos.second -= m_vel.second;

        return;
    }
};

t_spacing GetSpacing(std::vector<Star> &input);
void MoveForward(std::vector<Star> &input);
void MoveBack(std::vector<Star> &input);
void PrintOut(std::vector<Star> &input);

void Part1(std::vector<Star> &input);

int main() {
    std::ifstream fin("input_day10.dat");

    std::regex rgx(R"([a-z,=><])");

    std::vector<Star> stars;
    std::string line;
    int32_t px, py, vx, vy;
    while(std::getline(fin, line)) {
        line = std::regex_replace(line, rgx, "");
        std::istringstream iss(line);

        iss >> px >> py >> vx >> vy;

        stars.push_back(Star(px, py, vx, vy));
    }

    Part1(stars);

    return 0;
}

void Part1(std::vector<Star> &input) {
    t_spacing old = std::make_pair(0, 0);
    int32_t check = 0;
    for(int32_t it = 0; it < 20000; ++it) {
        MoveForward(input);
        
        t_spacing tmp = GetSpacing(input);
        if((it > 0 && tmp.second > old.second)) {
            cout << "Iteration: " << it << endl;
            MoveBack(input);
            PrintOut(input);
            MoveForward(input);

            break;
            check++;
        }
        old = tmp;
    }

    return;
}

void PrintOut(std::vector<Star> &input) {
    t_spacing spc = GetSpacing(input);
    int32_t offset = 6;

    spc.first += offset + 1;
    spc.second += offset + 1;

    std::vector<std::vector<char>> field;

    field.resize(spc.second);
    for(int32_t it = 0; it < spc.second; ++it) {
        field[it].resize(spc.first);
        std::fill(field[it].begin(), field[it].end(), 0);
    }

    int32_t rmin = input[0].GetPos().second;
    int32_t cmin = input[0].GetPos().first;
    for(auto &k: input) {
        if(k.GetPos().first < cmin)
            cmin = k.GetPos().first;
        if(k.GetPos().second < rmin)
            rmin = k.GetPos().second;
    }

    for(auto &k: input) {
        t_coords tmp = k.GetPos();
        field[tmp.second - rmin + offset/2][tmp.first - cmin + offset/2] = 1;
    }

    for(int32_t row = 0; row < spc.second; ++row) {
        for(int32_t col = 0; col < spc.first; ++col)
            cout << (field[row][col] == 0 ? ' ' : '#');
        cout << endl;
    }
    cout << endl;

    return;
}

void MoveForward(std::vector<Star> &input) {
    for(auto &k: input)
        k.Move();

    return;
}

void MoveBack(std::vector<Star> &input) {
    for(auto &k: input)
        k.MoveBack();

    return;
}

t_spacing GetSpacing(std::vector<Star> &input) {
    t_coords min = input[0].GetPos();
    t_coords max = input[0].GetPos();

    for(auto &k: input) {
        t_coords tmp = k.GetPos();

        if(tmp.first < min.first)
            min.first = tmp.first;
        if(tmp.first > max.first)
            max.first = tmp.first;

        if(tmp.second < min.second)
            min.second = tmp.second;
        if(tmp.second > max.second)
            max.second = tmp.second;
    }

    return std::make_pair(max.first - min.first + 1, max.second - min.second + 1);
}