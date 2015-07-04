#include <iostream>
#include <iomanip>
#include "program_state.h"

std::ostream& operator<<(std::ostream& out, const DataSegment &data_segment) {
    if (data_segment.data_segment.size() == 0) {
        return out;
    }

    for (unsigned int i = 0; i < data_segment.data_segment.size() - 1; ++i) {
        out << std::setw(2) << std::setfill('0') <<
            (int)data_segment.data_segment[i] << " ";
    }

    out << std::setw(2) << std::setfill('0') <<
        (int)data_segment.data_segment[data_segment.data_segment.size()-1];

    return out;
}
