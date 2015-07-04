#ifndef PARSE_AND_LOAD_H_
#define PARSE_AND_LOAD_H_

#include <vector>
#include <iostream>

class Instruction;

void parse_and_load(std::vector<Instruction*> &code, std::istream &in);

#endif
