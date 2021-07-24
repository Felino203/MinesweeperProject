#include "minefield.hpp"
#include <memory>
#include "tile.hpp"

Minefield::Minefield(int x, int y)
{
    for (int i = 0; i < (x * y); i++)
    {
        field.push_back(make_shared<Tile>(i));
    }
}