#ifndef MAP_HPP
#define MAP_HPP

#include <stdexcept>
#include <vector>

#include "Tile.hpp"

namespace wfc {

template <typename T>
class Map {

public:
    int x, y, z;    
    std::vector<Tile<T>> tiles;
    Map(): x(1), y(1), z(1) {
        //tiles(Tile<T>());
    }
    Map(const Tile<T>& smartTile, 
        const int __x = 1, 
        const int __y = 1, 
        const int __z = 1
    )
        : x(__x), y(__y), z(__z), tiles(x * y * z, smartTile)
    {}

    inline Tile<T>& operator[](const int index) {
        return tiles[index];
    }
    
    inline int size() {
        return this->tiles.size();
    }
    
};

};  // namespace wfc

#endif