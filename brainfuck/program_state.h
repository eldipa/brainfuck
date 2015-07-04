#ifndef PROGRAM_STATE_H_
#define PROGRAM_STATE_H_

#include <vector>
#include <iostream>

class DataSegment {
    private:
        std::vector<signed char> data_segment;

    public:
        explicit DataSegment(int data_segment_size) :
            data_segment(data_segment_size, 0) {}

        signed char& operator[](int at) {
            return data_segment[at % data_segment.size()];
        }

        friend std::ostream& operator<<(std::ostream& out,
                const DataSegment &data_segment);
};

struct ProgramState {
    int data_pointer;
    int code_position;

    bool end;
    DataSegment data_segment;

    std::ostream &standard_out;
    std::istream &standard_in;
    std::ostream &standard_err;

    explicit ProgramState(int data_segment_size) : data_pointer(0),
    code_position(0),
    end(false),
    data_segment(data_segment_size),
    standard_out(std::cout),
    standard_in(std::cin),
    standard_err(std::cerr) {
    }
};

std::ostream& operator<<(std::ostream& out, const DataSegment &data_segment);

#endif
