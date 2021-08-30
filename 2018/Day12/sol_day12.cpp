#include <bitset>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

#define NUMBER_OF_GENERATIONS 20
#define INITIAL_STRING_SIZE 99
#define BITSET_WIDTH 2048 
#define INIT_OFFSET ((BITSET_WIDTH - INITIAL_STRING_SIZE - 1)/2)
#define SUM_OFFSET (INITIAL_STRING_SIZE + INIT_OFFSET - 1)

typedef std::pair<std::string, char> t_rule;
typedef std::bitset<BITSET_WIDTH> t_bitstring;

int64_t SumPots(t_bitstring field, int64_t offset);
t_bitstring RuleRes(const t_bitstring &init, const t_rule &rule);
t_bitstring Iterate(const t_bitstring &init, const std::vector<t_rule> &rules);

int64_t Part1(t_bitstring init, const std::vector<t_rule> &rules);
int64_t Part2(t_bitstring init, const std::vector<t_rule> &rules);

int main() {
    std::ifstream fin("input_day12.dat");

    std::string line;
    std::string init_string;
    
    fin >> line >> line >> init_string;

    t_bitstring init_setting(init_string, 0, init_string.size(), '.', '#');
    init_setting <<= INIT_OFFSET;

    std::vector<std::pair<std::string, char>> rules;
    std::string str_a, str_b;
    char str_c;
    std::getline(fin, line);
    while(fin >> str_a >> str_b >> str_c)
        rules.push_back(std::make_pair(str_a, str_c));

    cout << "Day 12, part 1: " << Part1(init_setting, rules) << endl;
    cout << "Day 12, part 2: " << Part2(init_setting, rules) << endl;

    return 0;
}

int64_t Part1(t_bitstring init, const std::vector<t_rule> &rules) {
    for(int64_t gen = 0; gen < NUMBER_OF_GENERATIONS; ++gen)
        init = Iterate(init, rules);

    return SumPots(init, SUM_OFFSET);
}

int64_t Part2(t_bitstring init, const std::vector<t_rule> &rules) {
    const int64_t ngen = 50000000000;
    std::vector<t_bitstring> history;
    history.push_back(init);

    int64_t gen = 0;
    int64_t rep_gen = 0;
    bool check = false;
    while(gen < ngen) {
        gen++;

        init = Iterate(init, rules);

        check = false;
        for(int64_t idx = 0; idx < history.size(); ++idx) {
            if(history[idx] == (init << 1)) {
                rep_gen = idx;
                check = true;
                break;
            }
        }

        if(check)
            break;
        
        history.push_back(init);
    }

    int64_t delta = SumPots(init, SUM_OFFSET) - SumPots(history[rep_gen], SUM_OFFSET);
    int64_t res = SumPots(init, SUM_OFFSET) + (ngen - gen)*delta;

    return res;
}

int64_t SumPots(t_bitstring field, int64_t offset) {
    int64_t s = 0;

    for(int64_t idx = 0; idx < field.size(); ++idx) {
        if(field.test(idx))
            s = s + offset;
        offset--;
    }

    return s;
}

t_bitstring Iterate(const t_bitstring &init, const std::vector<t_rule> &rules) {
    t_bitstring rule_result;

    for(auto &k: rules)
        if(k.second == '#')
            rule_result |= RuleRes(init, k);
        else
            rule_result &= ~RuleRes(init, k);

    return rule_result;
}

t_bitstring RuleRes(const t_bitstring &init, const t_rule &rule) {
    t_bitstring tmp;
    tmp.flip();

    tmp &= rule.first[0] == '#' ? init >> 2 : ~(init >> 2);
    tmp &= rule.first[1] == '#' ? init >> 1 : ~(init >> 1);
    tmp &= rule.first[2] == '#' ? init : ~init;
    tmp &= rule.first[3] == '#' ? init << 1 : ~(init << 1);
    tmp &= rule.first[4] == '#' ? init << 2 : ~(init << 2);

    return tmp;
}