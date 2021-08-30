#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

class Cook {
public:
    int32_t m_score;
    int32_t m_pos;

    Cook(int32_t _score, int32_t _pos) : m_score(_score), m_pos(_pos) {
    }

    void Move(const std::string &scores) {
        m_pos = (m_pos + 1 + m_score) % scores.size();
        m_score = scores[m_pos] - '0';

        return;
    }
};

std::string Part1(std::string &scores, const int32_t num, std::vector<Cook> &elfs);
int32_t Part2(std::string &scores, const int32_t num, std::vector<Cook> &elfs);

int main() {
    std::ifstream fin("input_day14.dat");

    int32_t critNum;
    fin >> critNum;

    std::string scores = "37";
    scores.reserve(critNum + 10);

    std::vector<Cook> elfs;
    elfs.push_back(Cook(3, 0));
    elfs.push_back(Cook(7, 1));

    cout << "Day 14, part 1: " << Part1(scores, critNum, elfs) << endl;
    cout << "Day 14, part 2: " << Part2(scores, critNum, elfs) << endl;

    return 0;
}

std::string Part1(std::string &scores, const int32_t num, std::vector<Cook> &elfs) {
    int32_t tmpscore;
    while(scores.size() < num + 10) {
        tmpscore = 0;
        for(const auto &k: elfs)
            tmpscore += k.m_score;

        if(tmpscore >= 10) {
            scores.push_back((tmpscore/10) + '0');
            scores.push_back((tmpscore % 10) + '0');
        }
        else {
            scores.push_back(tmpscore + '0');
        }

        for(auto &k: elfs)
            k.Move(scores);
    }

    return scores.substr(num, 10);
}

int32_t Part2(std::string &scores, const int32_t num, std::vector<Cook> &elfs) {
    std::string sstr = std::to_string(num);
    int32_t sstrsize = sstr.size();

    if(scores.find(sstr) == -1) {
        int32_t tmpscore;
        while(1) {
            tmpscore = 0;
            for(const auto &k: elfs)
                tmpscore += k.m_score;

            if(tmpscore >= 10) {
                scores.push_back((tmpscore/10) + '0');
                scores.push_back((tmpscore % 10) + '0');
            }
            else {
                scores.push_back(tmpscore + '0');
            }

            if(sstr == scores.substr(scores.size() - sstrsize, sstrsize) || sstr == scores.substr(scores.size() - sstrsize - 1, sstrsize))
                break;

            for(auto &k: elfs)
                k.Move(scores);
        }
    }

    return scores.find(std::to_string(num));
}