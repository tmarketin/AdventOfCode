#include <cstdint>
#include <iostream>
#include <map>
#include <utility>
#include <vector>

#include "../Libs/aoclib.h"

typedef std::pair<std::string, float> CompoundT;
typedef std::vector<CompoundT> CompoundVecT;
typedef std::map<CompoundT, CompoundVecT> FormulaTableT;

using std::cout;
using std::endl;

class Problem {
private:
    aoc::StrVecVecT input;
    FormulaTableT table;

    void parseInput() {
        table.clear();
        CompoundVecT inputs;
        CompoundT output;
        for(auto vec : input) {
            inputs.clear();
            int idx = 0;
            while(idx < vec.size()) {
                if(vec[idx] == "=>") {
                    output = std::make_pair(vec[idx + 2], std::stoi(vec[idx + 1]));
                    idx += 3;
                    break;
                }
                uint32_t quantity = std::stoi(vec[idx]);
                std::string comp = vec[idx + 1];
                if(comp[comp.size() - 1] == ',')
                    comp.pop_back();
                idx += 2;
                inputs.push_back(std::make_pair(comp, quantity));
            }
            table[output] = inputs;
        }

        return;
    }

    bool isOnlyOre(CompoundVecT & vec) const {
        for(auto iter = vec.begin(); iter != vec.end(); ++iter){
            if(iter->first != "ORE")
                return false;
        }
        return true;
    }

    CompoundT findMatchingComponent(std::string name) {
        for(auto iter = table.begin(); iter != table.end(); ++iter)
            if(iter->first.first == name)
                return iter->first;
    }

    void addMoreComponents(CompoundVecT & components, CompoundVecT & additions) {
        return;
    }

public:
    Problem(std::string fname) {
        input = aoc::getSpaceDelimitedInputFromFile(fname);
        parseInput();
    }

    void printTable() {
        cout << "Table size: " << table.size() << endl;
        for(auto iter = table.begin(); iter != table.end(); ++iter) {
            cout << "(" << iter->first.first << " " << iter->first.second << ")" << " : ";
            for(auto pair : iter->second)
                cout << "(" << pair.first << " " << pair.second << ") + ";
            cout << endl;
        }

        return;
    }

    void printCompoundVec(CompoundVecT & vec) {
        for(auto iter = vec.begin(); iter != vec.end(); ++iter) {
            cout << "(" << iter->first << " " << iter->second << ")";
            if((iter + 1) != vec.end())
                cout << " + ";
        }
        cout << endl;
    }

    void solvePart1() {
        CompoundVecT components = table[std::make_pair("FUEL", 1)];

        int count = 0;
        while(! isOnlyOre(components) && count < 1) {
            for(auto iter = components.begin(); iter != components.end(); ++iter) {
                if(iter->first != "ORE") {
                    CompoundT reactant = findMatchingComponent(iter->first);
                    addMoreComponents(components, table[reactant]);
                    printCompoundVec(table[reactant]);
                }
            }
            printCompoundVec(components);
            count++;
        }

        return;
    }

};

int main() {
    Problem problem("input_day14.dat");

    problem.solvePart1();

    return 0;
}
