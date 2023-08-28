#ifndef MAP_H
#define MAP_H

#include <stdexcept>
#include <vector>

#include "Tile.h"

#include "debugMacros.h"


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
        #if INDEX_SAFEGUARD
        if (index < 0 || index > tiles.size()) 
            throw std::invalid_argument("Map.h T& Map::operator[]() -> Index out of bounds "); 
        #endif
        
        return tiles[index];
    }
    
    inline int size() {
        return this->tiles.size();
    }
    
    void draw() {
        for (int z = 0; z < this->z; z++) {
        for (int y = 0; y < this->y; y++) {
        for (int x = 0; x < this->x; x++) 
        {
            int index = x + y * this->x + z * this->y;

            switch (tiles[index].flag) 
            {
                case Flag::COLLAPSED:
                    std::cout << tiles[index].states[0].element;
                    break;

                case Flag::UNCOLLAPSED:
                    std::cout << "-";
                    break;

                case Flag::INCOLLAPSABLE: 
                    std::cout << "X";
                    break;
            }
        }
        std::cout << std::endl;
        }
        std::cout << std::endl;
        }
    }

    friend std::ostream&operator<<(std::ostream&os, const Map<T>&map) {

        os << "Dimensions(X: " << map.x << ", Y:" << map.y << ", Z:" << map.z << ")" << '\n';

        for (int i = 0; i < map.tiles.size(); i++) {
            if (FULL_TILE_LOG) {
                os << i << " | " << map.tiles[i] << '\n';
            } else {
                os << i << " | " << map.tiles[i].flag << '\n';
            }
        }

        return os;
    }
};

};  // namespace wfc

#endif