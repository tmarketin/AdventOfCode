#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

using std::cout;
using std::endl;

typedef std::array<int32_t, 60> timeplan;

// should all be refactored
class Item{
private:
    int32_t guard_id;
    int32_t year, month, day;
    std::array<int32_t, 60> timeplan;

public:
    Item(std::string &timestamp, int32_t gid, std::array<int32_t, 60> &plan) {
        std::istringstream iss(timestamp);
        iss >> year >> month >> day;
        guard_id = gid;
        timeplan = plan;
    }

    void Print() {
        cout << guard_id << "  ";
        for(auto k: timeplan)
            cout << (k == 0 ? '.' : '#');
        cout << endl;

        return;
    }

    int32_t Count() {
        return std::count(timeplan.begin(), timeplan.end(), 1);
    }

    int32_t GetGid(){
        return guard_id;
    }

    int32_t GetVal(int32_t min) {
        return timeplan[min];
    }

    std::array<int32_t, 60> GetArray() {
        return timeplan;
    }
};

void ParseInput(std::vector<std::string> &data, std::vector<Item> &table);
void MakeDict(std::vector<Item> &table, std::map<int32_t, timeplan> &dict);
int32_t SumArray(std::array<int32_t, 60> &arr);

int Part1(std::map<int32_t, std::array<int32_t, 60>> &dict);
int Part2(std::map<int32_t, std::array<int32_t, 60>> &dict);

int main() {
    std::string line;
    std::vector<std::string> data;
    std::vector<Item> table;
    std::map<int32_t, std::array<int32_t, 60>> dict;

    std::ifstream fin("input_day4_sorted.dat");

    while(std::getline(fin, line))
        data.push_back(line);

    ParseInput(data, table);
    MakeDict(table, dict);

    cout << "Day 4, part 1: " << Part1(dict) << endl;
    cout << "Day 4, part 2: " << Part2(dict) << endl;

    return 0;
}

int Part1(std::map<int32_t, std::array<int32_t, 60>> &dict) {
    int32_t gid_max = 0;
    int32_t cnt_max = 0;
    for(auto &k: dict) {
        int32_t s = 0;
        for(auto &l: k.second)
            s = s + l;
        if(s > cnt_max) {
            gid_max = k.first;
            cnt_max = s;
        }
    }

    auto search = dict.find(gid_max);
    std::array<int32_t, 60>::iterator pos;
    pos = std::max_element(search->second.begin(), search->second.end());

    return gid_max*std::distance(search->second.begin(), pos);
}

int Part2(std::map<int32_t, std::array<int32_t, 60>> &dict) {
    int32_t mnt_max = 0;
    int32_t gid_max;
    int32_t mnt_max_cnt = 0;
    for(int32_t mnt = 0; mnt < 60; ++mnt) {
        for(auto &k: dict) {
            if(k.second[mnt] > mnt_max_cnt) {
                mnt_max_cnt = k.second[mnt];
                mnt_max = mnt;
                gid_max = k.first;
            }
        }
    }

    return gid_max*mnt_max;
}

void MakeDict(std::vector<Item> &table, std::map<int32_t, timeplan> &dict) {
    for(auto &k: table) {
        int32_t gid = k.GetGid();

        auto search = dict.find(gid);
        if(search ==  dict.end()) {
            dict.emplace(gid, k.GetArray());
        }
        else {
            for(int32_t idx = 0; idx < 60; ++idx)
                search->second[idx] += k.GetVal(idx);
        }
    }
    return;
}

void ParseInput(std::vector<std::string> &data, std::vector<Item> &table) {
    bool check_first = true;
    int32_t gid;
    int32_t y,mth,d,h,min;
    std::array<int32_t, 60> day;

    std::string timestamp;

    std::regex rgx_time(R"([-:])");
    std::regex rgx_guard(R"(Guard)");
    std::regex rgx_sleep(R"(asleep)");
    std::regex rgx_awake(R"(wakes)");

    for(auto &line: data) {
        timestamp = std::regex_replace(line.substr(1, 16), rgx_time, " ");
        std::istringstream tmplan(timestamp);
        tmplan >> y >> mth>> d >> h >> min;

        if(std::regex_search(line, rgx_guard)) {
            if(! check_first)
                table.push_back(Item(timestamp, gid, day));
            check_first = false;

            day.fill(0);
            std::istringstream iss(line.substr(line.find("#") + 1));
            iss >> gid;
        }

        if(std::regex_search(line, rgx_sleep)) {
            for(int32_t idx = min; idx <= 59; ++idx)
                day[idx] = 1;
        }

        if(std::regex_search(line, rgx_awake)) {
            for(int32_t idx = min; idx <= 59; ++idx)
                day[idx] = 0;
        }
    }
    table.push_back(Item(timestamp, gid, day));

    return;
}

int32_t SumArray(std::array<int32_t, 60> &arr) {
    int32_t res = 0;
    for(auto &k: arr)
        res = res + k;

    return res;
}