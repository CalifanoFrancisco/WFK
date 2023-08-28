#ifndef WFC_HPP
#define WFC_HPP

#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <time.h>

#include "tile_t.hpp"
#include "Flags.hpp"
#include "seed.hpp"
#include "Map.hpp"

namespace wfc 
{

// windows compatibility
#if __linux__
    #define BOOT() 
#elif _WIN32 || _WIN64 || __CYGWIN__
    #define BOOT() system("chcp 65001")
#endif

using std::cout;
using std::endl;


template <typename T> 
class WFC 
{

public:
    // ctors
    WFC(const Map<T>& map) {
        BOOT();
        if (map.x <= 0 || map.y <= 0 || map.z <= 0)
            throw std::invalid_argument(" WFC.h WFC<T>::WFC() -> Cannot use values lower or equal to 0");
        this->m_map = map;
        this->MAX_TILE_SIZE = this->m_map.tiles[0].entropy();
        srand(seed);
    }
   
    WFC(const Tile<T>& smart_tile, const int x = 1, const int y = 1, const int z = 1):
        WFC(Map<T>(smart_tile, x, y, z))
    {}

    WFC(const std::initializer_list<tile_t<T>>& primitive_tiles, const int x = 1, const int y = 1, const int z = 1):
        WFC(Tile<T>(primitive_tiles), x, y, z)
    {}

    Map<T> run(const bool render = true) {
        m_map[0].collapse();                            // tile 0 collapses incorrectly always :(

        //m_map[findUncollapsed()].collapse();          // collapse random tile to init chain propagation
        
        for (int i = 0; !hasEntirelyCollapsed(); i++) { // loop while map hasnt collapsed entirely

            if (render) m_map.draw();

            propagate();                                // propagate data
            m_map[findLowestEntropy()].collapse();      // collapse random tile
            
            //std::cout << i << '/' << m_map.tiles.size() << " | " << std::endl;
        }

        return this->m_map;                             // returns collapsed map
    }

    void forceCollapse(const int index) {
        m_map[index].collapse();
        propagate();
    }
    
private:
    int MAX_TILE_SIZE = 0;
     Map<T> m_map;

    // set lib doesnt work with generic types (templated)
    inline void setCroto(std::vector<tile_t<T>>& list, const tile_t<T>& element) {
        for (auto i:list) 
            if (i == element) return;   // unica razon por la que T necesita operator==()
        list.push_back(element);
    }

    // Returns true if the tile chosen is collapsed
    inline bool observe(const int index) {
        return (m_map[index].flag == Flag::COLLAPSED);
    }
    
    // Returns 1 if the whole map has collapsed/reached quantum impossibility
    bool hasEntirelyCollapsed() {
        for (int i = 0; i < m_map.size(); i++)          // Iterate through all tiles
            if (!observe(i)) return false;              // if tile is uncollapsed return false
        return true;                                    // else true
    }

    // undefined behaviour, needs further testing
    bool hasEntirelyCollapsedOptimized() {
        static int n;
        n += 1;
        if (n >= m_map.size()) return true;
        return false;
    }
    
    // Makes calculations to spread info in 1 dimension
    void calculate(const int index, const int displacement, const int side) {
        
        // check its inbounds
        if (displacement > m_map.size() - 1 || displacement < 0) return;

        // optimization
        if (m_map[displacement].flag == Flag::COLLAPSED) return;

        const Tile<T> tile_b = m_map[displacement];
        const Tile<T> tile_a = m_map[index];

        std::vector<tile_t<T>> b_elements;          // auxiliar array of elements

        for (tile_t<T> a:tile_a.states) {           // iterate through all states of main tile (a)
        for (tile_t<T> b:tile_b.states) {           // iterate through all states of secondary tile (b)
            switch (side) {
                case 0: // LEFT
                    if (a.X.MINUS == b.X.PLUS) setCroto(b_elements, b);
                    break;
                case 1: // RIGHT
                    if (a.X.PLUS == b.X.MINUS) setCroto(b_elements, b);
                    break;
                case 2: // UP
                    if (a.Y.MINUS == b.Y.PLUS) setCroto(b_elements, b);
                    break;
                case 3: // DOWN
                    if (a.Y.PLUS == b.Y.MINUS) setCroto(b_elements, b);
                    break;
                case 4: // FRONT
                    if (a.Z.PLUS == b.Z.MINUS) setCroto(b_elements, b);
                    break;
                case 5: // BACK
                    if (a.Z.MINUS == b.Z.PLUS) setCroto(b_elements, b);
                    break;
                default:
                    throw std::invalid_argument("WFC.h WFC<T>::calculate() -> Invalid 'side' value");
                    break;
            }   
            
        }
        }
        m_map[displacement].states = b_elements;    // update possible states
    }
    
    // Propagates info through m_map
    void propagate() {

        for (int i = 0; i < m_map.size(); i++) {
            
            if (m_map[i].entropy() == MAX_TILE_SIZE) continue;

            if (m_map.x > 1) {
                calculate(i, i - 1, 0); // left
                calculate(i, i + 1, 1); // right
            }
            if (m_map.y > 1) {  
                calculate(i, i - m_map.x, 2); // up
                calculate(i, i + m_map.x, 3); // down
            }
            if (m_map.z > 1) {
                /* 
                *  untested
                *  no tengo como depurarlo, quiza usar el TileMap de SFML viejo
                */
                calculate(i, i - m_map.x * m_map.y, 5); // back
                calculate(i, i + m_map.x * m_map.y, 4); // front
            }
        }
    }

    // Returns m_map position which entropy is lowest
    int  findLowestEntropy() {
        int pos            = -1;                        // Impossible position
        int lowest_entropy = 1024;               
        for (int i = 0; i < m_map.size(); i++) {        // Iterate through all tiles
            if (
                m_map[i].entropy() < lowest_entropy     // Entropy is lower than lowest
                &&                                      // and
                !observe(i)                             // is not collapsed
            ) {
                pos = i;                                // update lowest entropy tile position
                lowest_entropy = m_map[i].entropy();    // update lowest entropy
            }
        }
        if (pos == -1) return findUncollapsed();        // Extreme cases function
        return pos;
    }
    
    // Returns random m_map position which is not collapsed
    int  findUncollapsed() {
        // [DEPRECATE] in future
        // Innecesary iterations
        int maxIterations = 3000;
        for (int i = 0; i < maxIterations; i++) {       // Iterate through all tiles
            int n = rand() % m_map.size();              // Generate random position
            if (!observe(n)) return n;                  // Check if its uncollapsed
        }
        return -1;
    }
};

};  // namespace wfc

#endif