#ifndef OBJ_H
#define OBJ_H

#include <string>

#include "../WFC/tile_t.h"
#include "../WFC/Tile.h"

struct Obj
{
    std::string x;
    Obj(std::string b) : x(b) {}

    // OBLIGATORIOS
    Obj() : x("@") {}
    bool operator==(const Obj& obj){
        return (this->x == obj.x);
    }
    friend std::ostream &operator<<(std::ostream &os, const Obj &obj) {
        return os << obj.x;
    }
};

wfc::Tile<Obj> g_smartTile(
    {
        wfc::tile_t<Obj>(Obj("┏"), {1, 0, 1, 0}),
        wfc::tile_t<Obj>(Obj("┃"), {1, 1, 0, 0}),
        wfc::tile_t<Obj>(Obj("┓"), {1, 0, 0, 1}),
        wfc::tile_t<Obj>(Obj("━"), {0, 0, 1, 1}),
        wfc::tile_t<Obj>(Obj("┗"), {0, 1, 1, 0}),
        wfc::tile_t<Obj>(Obj("┛"), {0, 1, 0, 1}),
        wfc::tile_t<Obj>(Obj("┫"), {1, 1, 0, 1}),
        wfc::tile_t<Obj>(Obj("┣"), {1, 1, 1, 0}),
        wfc::tile_t<Obj>(Obj("┻"), {0, 1, 1, 1}),
        wfc::tile_t<Obj>(Obj("┳"), {1, 0, 1, 1}),
        wfc::tile_t<Obj>(Obj("╋"), {1, 1, 1, 1}),
        wfc::tile_t<Obj>(Obj(" "), {0, 0, 0, 0})
    }
);

#endif