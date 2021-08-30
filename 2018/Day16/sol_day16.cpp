#include <algorithm>
#include <array>
#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using std::cout;
using std::endl;

typedef std::array<uint32_t, 4> t_reg;
typedef std::array<std::pair<std::function<void(t_reg &, const t_reg &)>, int32_t>, 16> t_fnarray;

void PrintArray(const t_reg &arr);

class InputClass {
public:
    t_reg m_before, m_after;
    t_reg m_command;

    InputClass(std::string line1, std::string line2, std::string line3) {
        std::regex rgx(R"([a-zA-Z:,\[\]])");

        std::istringstream iss_before(std::regex_replace(line1, rgx, ""));
        iss_before >> m_before[0] >> m_before[1] >> m_before[2] >> m_before[3];

        std::istringstream iss_comm(line2);
        iss_comm >> m_command[0] >> m_command[1] >> m_command[2] >> m_command[3];

        std::istringstream iss_after(std::regex_replace(line3, rgx, ""));
        iss_after >> m_after[0] >> m_after[1] >> m_after[2] >> m_after[3];
    }
    
    friend std::ostream& operator<< (std::ostream &out, const InputClass &inc);
};

std::ostream& operator<< (std::ostream &out, const InputClass &inc)
{
    PrintArray(inc.m_before);
    PrintArray(inc.m_command);
    PrintArray(inc.m_after);
    cout << endl;

    return out;
}

// instructions
void addr(t_reg &regs, const t_reg &comm);
void addi(t_reg &regs, const t_reg &comm);

void mulr(t_reg &regs, const t_reg &comm);
void muli(t_reg &regs, const t_reg &comm);

void banr(t_reg &regs, const t_reg &comm);
void bani(t_reg &regs, const t_reg &comm);
void borr(t_reg &regs, const t_reg &comm);
void bori(t_reg &regs, const t_reg &comm);

void setr(t_reg &regs, const t_reg &comm);
void seti(t_reg &regs, const t_reg &comm);

void gtir(t_reg &regs, const t_reg &comm);
void gtri(t_reg &regs, const t_reg &comm);
void gtrr(t_reg &regs, const t_reg &comm);

void eqir(t_reg &regs, const t_reg &comm);
void eqri(t_reg &regs, const t_reg &comm);
void eqrr(t_reg &regs, const t_reg &comm);

uint32_t Part1(const std::vector<InputClass> &inputs, t_fnarray &fn);  
uint32_t Part2(const std::vector<InputClass> &inputs, const std::vector<t_reg> &program, t_fnarray &fn);

int main() {
    std::ifstream fin("input_day16.dat");
    std::vector<InputClass> inputs;
    std::vector<t_reg> program;

    t_fnarray fn = { std::make_pair(addr, -1), 
        std::make_pair(addi, -1), std::make_pair(mulr, -1), std::make_pair(muli, -1), std::make_pair(banr, -1), 
        std::make_pair(bani, -1), std::make_pair(borr, -1), std::make_pair(bori, -1), std::make_pair(setr, -1), 
        std::make_pair(seti, -1), std::make_pair(gtir, -1), std::make_pair(gtri, -1), std::make_pair(gtrr, -1), 
        std::make_pair(eqir, -1), std::make_pair(eqri, -1), std::make_pair(eqrr, -1) };

    std::string line;
    while(std::getline(fin, line)) {
        if(line == "====")
            break;
        if(line.empty())
            continue;
        
        if(line.substr(0, 6) == "Before") {
            std::string line_mid, line_end;
            std::getline(fin, line_mid);
            std::getline(fin, line_end);

            inputs.push_back(InputClass(line, line_mid, line_end));
        }
    }

    while(std::getline(fin, line)) {
        t_reg tmpProgLine;

        std::istringstream iss_progline(line);
        iss_progline >> tmpProgLine[0] >> tmpProgLine[1] >> tmpProgLine[2] >> tmpProgLine[3];
        program.push_back(tmpProgLine);
    }

    cout << "Day 16, part 1: " << Part1(inputs, fn) << endl;
    cout << "Day 16, part 2: " << Part2(inputs, program, fn) << endl;

    return 0;
}

uint32_t Part1(const std::vector<InputClass> &inputs, t_fnarray &fn) {
    uint32_t input_count = 0;
    uint32_t cnt = 0;
    uint32_t fnidx;

    for(auto &k: inputs) {
        cnt = 0;
        for(uint32_t idx = 0; idx < 16; ++idx) {
            InputClass tmpReg = k;
            fn[idx].first(tmpReg.m_before, tmpReg.m_command);
            if(tmpReg.m_before[tmpReg.m_command[3]] == tmpReg.m_after[tmpReg.m_command[3]]) {
                fnidx = idx;
                cnt++;
            }
        }
        if(cnt >= 3)
            input_count++;

        if(cnt == 1)
            fn[fnidx].second = k.m_command[0];
    }

    return input_count;
}

uint32_t Part2(const std::vector<InputClass> &inputs, const std::vector<t_reg> &program, t_fnarray &fn) {
    uint32_t known_opcodes = 0;
    std::array<int32_t, 16> lookup = {0};

    for(auto &k: fn)
        if(k.second != -1) {
            lookup[k.second] = 1;
            known_opcodes++;
        }

    // find out opcodes
    uint32_t input_idx = -1;
    while(known_opcodes < 16) {
        input_idx = (input_idx + 1) % inputs.size();
        InputClass tmpInput = inputs[input_idx];

        if(lookup[tmpInput.m_command[0]] != 0)
            continue;

        uint32_t unknown_opcodes = 0;
        uint32_t unknown_possible = -1;
        for(uint32_t opidx = 0; opidx < 16; ++opidx) {
            tmpInput = inputs[input_idx];
            fn[opidx].first(tmpInput.m_before, tmpInput.m_command);
            if(tmpInput.m_before[tmpInput.m_command[3]] == tmpInput.m_after[tmpInput.m_command[3]] && fn[opidx].second == -1) {
                unknown_possible = opidx;
                unknown_opcodes++;
            }
        }

        if(unknown_opcodes == 1) {
            fn[unknown_possible].second = tmpInput.m_command[0];
            lookup[tmpInput.m_command[0]] = 1;
            known_opcodes++;
        }

    }

    std::sort(fn.begin(), fn.end(), [](const std::pair<std::function<void(t_reg &, const t_reg &)>, int32_t> &lhs, const std::pair<std::function<void(t_reg &, const t_reg &)>, int32_t> &rhs)
        {return lhs.second < rhs.second;});

    t_reg resRegs = {0, 0, 0, 0};

    for(auto &cmd: program)
        fn[cmd[0]].first(resRegs, cmd);

    return resRegs[0];
}

void PrintArray(const t_reg &arr) {
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int32_t>(std::cout, " "));
    cout << endl;

    return;
}

void addr(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = regs[comm[1]] + regs[comm[2]];

    return;
}

void addi(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = regs[comm[1]] + comm[2];

    return;
}

void mulr(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = regs[comm[1]]*regs[comm[2]];

    return;
}

void muli(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = regs[comm[1]]*comm[2];

    return;
}

void banr(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = regs[comm[1]] & regs[comm[2]];

    return;
}

void bani(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = regs[comm[1]] & comm[2];

    return;
}

void borr(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = regs[comm[1]] | regs[comm[2]];

    return;
}

void bori(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = regs[comm[1]] | comm[2];

    return;
}

void setr(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = regs[comm[1]];

    return;
}

void seti(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = comm[1];

    return;
}

void gtir(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = (comm[1] > regs[comm[2]] ? 1 : 0);

    return;
}

void gtri(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = (regs[comm[1]] > comm[2] ? 1: 0);

    return;
}

void gtrr(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = (regs[comm[1]] > regs[comm[2]] ? 1 : 0);

    return;
}

void eqir(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = (comm[1] == regs[comm[2]] ? 1 : 0);

    return;
}

void eqri(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = (regs[comm[1]] == comm[2] ? 1 : 0);

    return;
}

void eqrr(t_reg &regs, const t_reg &comm) {
    regs[comm[3]] = (regs[comm[1]] == regs[comm[2]] ? 1 : 0);

    return;
}
