#ifndef TILE_T_HPP
#define TILE_T_HPP

#include <stdexcept>
#include <iostream>
#include <vector>

namespace wfc 
{

using std::cout;

template <typename T>
struct tile_t {

    struct pm2i_t {
        int PLUS, MINUS;
        pm2i_t(int __plus, int __minus): PLUS(__plus), MINUS(__minus) { }
        pm2i_t():PLUS(0), MINUS(0) { }
        bool operator==(const pm2i_t& other) {
            return (
                PLUS  == other.PLUS &&
                MINUS == other.MINUS
            );
        }
    };

    T      element;
    pm2i_t X, Y, Z;

    tile_t():
        element(T()), 
        X(0, 0), 
        Y(0, 0), 
        Z(0, 0)
    { }

    tile_t(const T& __element):
        element(__element), 
        X(0, 0), 
        Y(0, 0), 
        Z(0, 0)
    { }

    /* modify to
    *
    * -x, +x, -y, +y, -z, +z
    * left, right, down, up, back, front
    */

    // Clockwise UP, DOWN, RIGHT LEFT
    tile_t(
        const T&       __element, 
        const std::vector<int>& rules
    ):
        element(__element)
    {
        switch (rules.size()) {
        case 2:
            Y = pm2i_t(-1      , -1      );
            X = pm2i_t(rules[0], rules[1]);
            Z = pm2i_t(-1      , -1      );
        case 4:
            Y = pm2i_t(rules[0], rules[1]);
            X = pm2i_t(rules[2], rules[3]);
            Z = pm2i_t(-1      , -1      );
            break;
        case 6:
            Y = pm2i_t(rules[0], rules[1]);
            X = pm2i_t(rules[2], rules[3]);
            Z = pm2i_t(rules[4], rules[5]);
            break;
        default: 
            throw "tile_t.h tile_t<T>::tile_t() -> Invalid amount of elements in constructor rules";
            break;
        }
    }

    bool operator==(const tile_t<T>& other) {
        return (
            this->element == other.element &&
            this->X == other.X &&
            this->Y == other.Y &&
            this->Z == other.Z
        );
    }
};

};  //namespace wfc

#endif