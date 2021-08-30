#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <utility>
#include <vector>

#define MAX_WORKERS 5
#define TIME_OFFSET 61

using std::cout;
using std::endl;

typedef std::pair<int32_t, int32_t> condition;
typedef std::set<int32_t> t_setsteps;

void PrintVec(std::vector<t_setsteps> &v);
void PrintSet(t_setsteps &s);

std::string Part1(std::vector<t_setsteps> &pred, std::vector<t_setsteps> &succ);
int32_t Part2(std::vector<t_setsteps> &pred, std::vector<t_setsteps> &succ);

int main() {
    std::vector<condition> data;
    std::string line;

    char largest = 0;
    std::ifstream fin("input_day7.dat");
    while(std::getline(fin, line)) {
        data.push_back(std::make_pair(line[5] - 'A', line[36] - 'A'));
        if(line[5] > largest)
            largest = line[5];
        if(line[36] > largest)
            largest = line[36];
    }
    
    largest = largest - 'A';
    std::vector<t_setsteps> pred, succ;
    pred.resize(largest + 1);
    succ.resize(largest + 1);

    for(auto &k: data) {
        succ[k.first].emplace(k.second);
        pred[k.second].emplace(k.first);
    }

    cout << "Day 7, part 1: " << Part1(pred, succ) << endl;
    cout << "Day 7, part 2: " << Part2(pred, succ) << endl;

    return 0;
}

std::string Part1(std::vector<t_setsteps> &pred, std::vector<t_setsteps> &succ) {
    std::string res = "";
    t_setsteps options;

// Find first step(s)
    for(int32_t idx = 0; idx < pred.size(); ++idx)
        if(pred[idx].size() == 0)
            options.insert(idx);
    
    while(res.size() < pred.size()) {
        auto current = options.begin();

        for(auto step = options.begin(); step != options.end(); ++step) {
            bool good = true;
            for(auto p = pred[*step].begin(); p != pred[*step].end(); ++p) {
                if(res.find(static_cast<char>(*p + 'A')) == std::string::npos) {
                    good = false;
                    break;
                }
            }

            if(good) {
                current = step;
                break;
            }
        }

        res.push_back(static_cast<char>(*current + 'A'));
        options.erase(current);
        for(auto &k: succ[*current])
            options.insert(k);
        for(auto c: res)
            options.erase(c - 'A');
    }

    return res;
}

int32_t Part2(std::vector<t_setsteps> &pred, std::vector<t_setsteps> &succ) {
    std::string output;
    t_setsteps option_steps;
    t_setsteps finished_steps;
    t_setsteps deletion_steps;

    std::array<std::pair<int32_t, int32_t>, MAX_WORKERS> workers;
    int32_t free_workers = MAX_WORKERS;
    int32_t occ_workers = 0;

    for(int32_t idx = 0; idx < MAX_WORKERS; ++idx) {
        workers[idx] = std::make_pair(0, -1);
    }

// Find first step(s)
    for(int32_t idx = 0; idx < pred.size(); ++idx)
        if(pred[idx].size() == 0)
            option_steps.insert(idx);

    int32_t seconds = 0;
    while(output.size() < pred.size()) {
        finished_steps.clear();
        if(occ_workers > 0) {
            for(int32_t idx = 0; idx < workers.size(); ++idx) {
                if(workers[idx].second > 0) {
                    workers[idx].second--;
                    if(workers[idx].second == 0) {
                        workers[idx].second = -1;
                        finished_steps.insert(workers[idx].first);
                        occ_workers--;
                        free_workers++;
                    }
                }
            }
        }
        
        // add finished steps to result and add new options
        for(auto &s: finished_steps) {
            output.push_back(static_cast<char>(s + 'A'));
            for(auto &k: succ[s])
                option_steps.insert(k);
            for(auto c: output)
                option_steps.erase(c - 'A');
        }

        // add new jobs for workers
        deletion_steps.clear();
        for(auto step = option_steps.begin(); step != option_steps.end() && free_workers > 0; ++step) {
            bool good = true;
            for(auto p = pred[*step].begin(); p != pred[*step].end(); ++p) {
                if(output.find(static_cast<char>(*p + 'A')) == std::string::npos)
                    good = false;
                for(auto al: workers) {
                    if(al.first == *p && al.second > 0)
                        good = false;
                }
                if(! good)
                    break;
            }

            if(good) {
                for(int32_t idx = 0; idx < MAX_WORKERS; ++idx) {
                    if(workers[idx].second == -1) {
                        workers[idx].first = *step;
                        workers[idx].second = TIME_OFFSET + *step;
                        free_workers--;
                        occ_workers++;
                        deletion_steps.insert(*step);
                        break;
                    }
                }
            }
        }

        // fix options
        for(auto it = deletion_steps.begin(); it != deletion_steps.end(); ++it)
            option_steps.erase(*it);

        seconds++;
    }

    return seconds - 1;
}

void PrintSet(t_setsteps &s) {
    for(auto k: s)
        cout << static_cast<char>(k + 'A') << " ";
    cout << endl;

    return;
}

void PrintVec(std::vector<t_setsteps> &v) {
    for(int32_t item = 0; item < v.size(); ++item) {
        cout << static_cast<char>(item + 'A') << ": ";
            if(v[item].size() > 0)
                PrintSet(v[item]);
    }
    cout << endl;

    return;
}
