#ifndef INTERPRETERS_H_
#define INTERPRETERS_H_

#include <vector>

class Instruction;
class ProgramState;

class Interpreter {
    public:
        virtual void interpret(std::vector<Instruction*> &code) = 0;
        virtual ~Interpreter() {}
};

class Executor: public Interpreter {
    private:
        int data_segment_size;
    protected:
        virtual void before_execute_instruction(ProgramState &state);
        virtual void after_execute_instruction(ProgramState &state);
    public:
        explicit Executor(int data_segment_size);
        virtual void interpret(std::vector<Instruction*> &code);
};

class Compiler: public Interpreter {
    private:
        int data_segment_size;
        std::ostream &out;

    public:
        Compiler(int data_segment_size, std::ostream &out);
        virtual void interpret(std::vector<Instruction*> &code);
};

class Debugger: public Executor {
    protected:
        virtual void before_execute_instruction(ProgramState &state);
        virtual void after_execute_instruction(ProgramState &state);
};

#endif
