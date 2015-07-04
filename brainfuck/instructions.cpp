#include <iostream>
#include <iomanip>
#include "program_state.h"
#include "instructions.h"

// DataPointerMove
DataPointerMove::DataPointerMove(int move) : move(move) {}

void DataPointerMove::exec(ProgramState &state) {
    state.data_pointer += move;
}

void DataPointerMove::compile(std::ostream &out) {
    out << "dataptr += " << move << ";" << std::endl;
}


// DataChange
DataChange::DataChange(int change) : change(change) {}

void DataChange::exec(ProgramState &state) {
    state.data_segment[state.data_pointer] += change;
}

void DataChange::compile(std::ostream &out) {
    out << "data[AT(dataptr)] += " << change << ";" << std::endl;
}


//Write
void Write::exec(ProgramState &state) {
    signed char symbol = state.data_segment[state.data_pointer];
    state.standard_out << symbol;
}

void Write::compile(std::ostream &out) {
    out << "std::cout << data[AT(dataptr)];" << std::endl;
}


//Read
void Read::exec(ProgramState &state) {
    signed char symbol = 0;       // 0 by default

    if (not state.standard_in.eof()) {
        symbol = state.standard_in.get();
    }

    if (state.standard_in.eof()) {
        symbol = 0;
    }

    state.data_segment[state.data_pointer] = symbol;
}

void Read::compile(std::ostream &out) {
    out << "c = std::cin.get();" << std::endl;
    out << "data[AT(dataptr)] = std::cin.eof() ? 0 : c;" << std::endl;
}


//ConditionalJump
ConditionalJump::ConditionalJump(bool jumpifzero) : jumpifzero(jumpifzero),
    code_position(-1) {}

    void ConditionalJump::exec(ProgramState &state) {
        signed char symbol = state.data_segment[state.data_pointer];

        if (
                (jumpifzero and symbol == 0) or
                (not jumpifzero and symbol != 0)
           ) {
            state.code_position = this->code_position;
        }
    }

void ConditionalJump::jump_to(int code_position) {
    this->code_position = code_position;
}

void ConditionalJump::compile(std::ostream &out) {
    if (jumpifzero) {    // BF symbol: [
        out << "while(data[AT(dataptr)]) {" << std::endl;
    } else {               // BF symbol: ]
        out << "}" << std::endl;
    }
}


//End
void End::exec(ProgramState &state) {
    state.end = true;
}

void End::compile(std::ostream &out) {
    out << "return 0;" << std::endl;
}


//Abort
void Abort::dump(ProgramState &state) {
    state.standard_err << std::uppercase << std::hex;
    state.standard_err << "PI " << std::setw(8) << std::setfill('0') <<
        state.code_position << std::endl;
    state.standard_err << "PD " << std::setw(8) << std::setfill('0') <<
        state.data_pointer << std::endl;
    state.standard_err << "Data" << std::endl << state.data_segment <<
        std::endl;
}


void Abort::exec(ProgramState &state) {
    dump(state);
    End::exec(state);
}


