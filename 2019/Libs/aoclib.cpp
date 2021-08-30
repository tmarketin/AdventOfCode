#include <fstream>
#include <iostream>
#include <sstream>

#include "aoclib.h"

namespace aoc {

StrVecVecT getSpaceDelimitedInputFromFile(std::string fname) {
    StrVecVecT result;
    std::ifstream infile(fname);

    std::string line;
    while(std::getline(infile, line)) {
        StrVecT singleRes;
        std::istringstream iss(line);
        for(std::string shortline; getline(iss, shortline, ' ');) {
            singleRes.push_back(shortline);
        }
        result.push_back(singleRes);
    }

    return result;
}

} // namespace aoc