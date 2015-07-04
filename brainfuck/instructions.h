#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include <iostream>

class ProgramState;

class Instruction {
    public:
        virtual void exec(ProgramState &state) = 0;
        virtual void compile(std::ostream &out) = 0;
        virtual ~Instruction() {}
};


class DataPointerMove: public Instruction {
    private:
        const int move;

    public:
        explicit DataPointerMove(int move);

        virtual void exec(ProgramState &state);
        virtual void compile(std::ostream &out);
};

class DataChange: public Instruction {
    private:
        const int change;

    public:
        explicit DataChange(int change);

        virtual void exec(ProgramState &state);
        virtual void compile(std::ostream &out);
};


class Write: public Instruction {
    public:
        virtual void exec(ProgramState &state);
        virtual void compile(std::ostream &out);
};

class Read: public Instruction {
    public:
        virtual void exec(ProgramState &state);
        virtual void compile(std::ostream &out);
};

class ConditionalJump: public Instruction {
    private:
        const bool jumpifzero;
        int code_position;

    public:
        explicit ConditionalJump(bool jumpifzero);

        virtual void exec(ProgramState &state);
        virtual void compile(std::ostream &out);

        void jump_to(int code_position);
};

class End: public Instruction {
    public:
        virtual void exec(ProgramState &state);
        virtual void compile(std::ostream &out);
};

class Abort: public End {
    private:
        void dump(ProgramState &state);

    public:
        virtual void exec(ProgramState &state);
};

#endif
