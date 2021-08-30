#ifndef AOCLIB_H
#define AOCLIB_H

#include <string>
#include <vector>

namespace aoc {

typedef std::vector<std::string> StrVecT;
typedef std::vector<StrVecT> StrVecVecT;

StrVecVecT getSpaceDelimitedInputFromFile(std::string fname);

} // namespace aoc

#endif