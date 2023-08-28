#ifndef FLAGS_H
#define FLAGS_H

#include <ostream>

namespace wfc 
{

enum class Flag {
    COLLAPSED,
    UNCOLLAPSED,
    INCOLLAPSABLE
};

};  // namespace wfc

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

#endif