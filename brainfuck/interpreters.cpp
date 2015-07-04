#include "instructions.h"
#include "interpreters.h"
#include "program_state.h"

#include <vector>

//Executor
void Executor::before_execute_instruction(ProgramState &state) {}
void Executor::after_execute_instruction(ProgramState &state) {}

Executor::Executor(int data_segment_size) :
    data_segment_size(data_segment_size) {}

    void Executor::interpret(std::vector<Instruction*> &code) {
        ProgramState state(this->data_segment_size);

        while (not state.end) {
            Instruction *instruction = code[state.code_position];

            before_execute_instruction(state);
            instruction->exec(state);
            after_execute_instruction(state);

            state.code_position += 1;
        }
    }

//Compiler
Compiler::Compiler(int data_segment_size, std::ostream &out) :
    data_segment_size(data_segment_size),
    out(out) {}

    void Compiler::interpret(std::vector<Instruction*> &code) {
        out << "#include <iostream>" << std::endl;
        out << "#include <vector>" << std::endl;
        out << std::endl;

        out << "#define N " << data_segment_size << std::endl;
        out << "#define AT(x) ((x) % " << data_segment_size << ")" << std::endl;
        out << std::endl;

        out << "int main(int argc, char *argv[]) {" << std::endl;
        out << "int dataptr = 0;" << std::endl;
        out << "signed char c = 0;" << std::endl;
        out << "std::vector<signed char> data(N, 0);" << std::endl;

        for (std::vector<Instruction*>::iterator it = code.begin();
                it != code.end();
                ++it) {
            (*it)->compile(out); // TODO define out (open and close here)
        }

        out << "}" << std::endl;
    }

//Debugger
void Debugger::before_execute_instruction(ProgramState &state) {}
void Debugger::after_execute_instruction(ProgramState &state) {}


