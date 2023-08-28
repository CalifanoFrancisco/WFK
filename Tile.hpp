#ifndef TILE_HPP
#define TILE_HPP

#include <initializer_list>
#include <stdexcept>
#include <ostream>
#include <vector>

#include "tile_t.hpp"
#include "Flags.hpp"
#include "seed.hpp"

namespace wfc 
{

template <typename T>
class Tile {
public:
    std::vector<tile_t<T>> states;
    Flag flag;
    
    Tile(
        const std::initializer_list<tile_t<T>>& elements
    ):
        states(elements), 
        flag(Flag::UNCOLLAPSED) 
    {
        extern unsigned int seed;
        srand(seed);
    }

    Tile(): 
        flag(Flag::INCOLLAPSABLE) 
    {}
    
    inline tile_t<T>& operator[](const int index) const {
        return states[index];
    }

    inline int entropy() const {
        return this->states.size();
    }

    void collapse() {

        if (states.size() == 0) {
            flag = Flag::INCOLLAPSABLE;
            throw std::invalid_argument("Casilla incolapsable, chau programa");
            return;
        }
        //int n = rand() % states.size();
        tile_t<T> stateChosen = states[chooseState()];
        states.clear();
        states.push_back(stateChosen);
        flag = Flag::COLLAPSED;
    }

private:
    inline int chooseState() {
        return rand() % states.size();
    }
};

};  // namespace wfc

#endif