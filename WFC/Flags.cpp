#include "Flags.h"

std::ostream& operator<<(std::ostream& os, const wfc::Flag flag) {
    switch (flag) {
        case wfc::Flag::COLLAPSED:
            os << "COLLAPSED";
            break;
        case  wfc::Flag::UNCOLLAPSED:
           os <<  "UNCOLLAPSED";
            break;
        case wfc::Flag::INCOLLAPSABLE:
            os << "INCOLLAPSABLE";
            break;
    }
    return os;
}
