#include "program_state.h"
#include "instructions.h"
#include "interpreters.h"
#include "parse_and_load.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "Usage: %s <DS-size> e|c <source>\n";
        return -1;
    }

    int data_segment_size = atoi(argv[1]);

    char flag = argv[2][0];

    if (flag != 'e' and flag != 'c') return 1;

    std::vector<Instruction*> code;
    std::ifstream source_code(argv[3]);

    parse_and_load(code, source_code);

    Interpreter *interpreter = 0;
    switch (flag) {
        case 'e':
            interpreter = new Executor(data_segment_size);
            break;
        case 'c':
            interpreter = new Compiler(data_segment_size, std::cout);
            break;
        default:
            return 1;
    }

    interpreter->interpret(code);

    for (unsigned int i = 0; i < code.size(); ++i) {
        delete code[i];
    }

    delete interpreter;

    return 0;
}
