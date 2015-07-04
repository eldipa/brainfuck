#include "parse_and_load.h"

#include <vector>
#include <stack>
#include <iostream>
#include <cassert>
#include <string>
#include "instructions.h"

void parse_and_load(std::vector<Instruction*> &code, std::istream &in) {
    int current_code_position = 0;

    std::stack<int> parentesis_starts;

    bool ignore = false;
    char symbol = 0;
    in >> symbol;

    while (not in.eof()) {
        Instruction *instruction = 0;

        if (ignore) {  // 'ignore' mode
            std::string _;
            getline(in, _);    //TODO (improve this) ignore until a \n is found
            ignore = false;
        } else {         // 'decode' mode
            size_t start_position = 0;
            size_t end_position   = 0;

            ConditionalJump *start = 0;
            ConditionalJump *end   = 0;

            switch (symbol) {  // decode
                case '>':
                    instruction = new DataPointerMove(+1);
                    break;
                case '<':
                    instruction = new DataPointerMove(-1);
                    break;

                case '+':
                    instruction = new DataChange(+1);
                    break;
                case '-':
                    instruction = new DataChange(-1);
                    break;

                case '.':
                    instruction = new Write();
                    break;
                case ',':
                    instruction = new Read();
                    break;

                case '[':
                    instruction = new ConditionalJump(true); // jumpifzero=True
                    parentesis_starts.push(current_code_position);
                    break;

                case ']':
                    start_position = parentesis_starts.top();
                    end_position   = current_code_position;

                    start = dynamic_cast<ConditionalJump*>(code[start_position]);
                    end = new ConditionalJump(false); // jumpifzero=False

                    start->jump_to(end_position); //the instruction of
                    end->jump_to(start_position); //the instruction of

                    parentesis_starts.pop();

                    instruction = end;
                    break;

                case '$':
                    instruction = new End();
                    break;
                case '@':
                    instruction = new Abort();
                    break;

                case '#':
                    ignore = true;
                    instruction = 0; // for clarity (explicit intention)
                    break;

                default:
                    assert(false);
                    break;
            }

            if (instruction) {
                code.push_back(instruction);
                current_code_position += 1;
            }
        }

        in >> symbol;
    }

    code.push_back(new End()); // execute an end if the instruction pointer
    // reach the end of the code
}
