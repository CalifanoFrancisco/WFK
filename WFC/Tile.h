#ifndef TILE_H
#define TILE_H

#include <initializer_list>
#include <stdexcept>
#include <ostream>
#include <vector>

#include "debugMacros.h"
#include "tile_t.h"
#include "Flags.h"
#include "seed.h"

#include "../Debug/Timer.h"


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
        /*
        if (index < 0 || index > states.size()) 
            throw std::invalid_argument("Tile.h Tile<T>::operator[](): -> Out of bounds index");
        */
        return states[index];
    }

    inline int entropy() const {
        return this->states.size();
    }

    void collapse() {
        //Timer timer("Tile.h collapse()");

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

    friend std::ostream& operator<<(std::ostream&os, const Tile<T>& tile) {
        os << "State: " << tile.flag;
        if (FULL_TILE_T_LOG) os << '\n';

        for (tile_t<T> tile: tile.states) {
            if (FULL_TILE_T_LOG) os << "   " << tile;
            else os << " " << tile;
        }
        return os;
    }
private:
    inline int chooseState() {
        return rand() % states.size();
    }
};

};  // namespace wfc

#endif