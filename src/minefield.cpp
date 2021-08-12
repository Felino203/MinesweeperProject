#include "minefield.hpp"
#include <iostream>
#include <iomanip>
#include <memory>
#include <algorithm>
#include <random>
#include "tile.hpp"

Minefield::Minefield(int x, int y) : fieldX(x), fieldY(y)
{
    for (int i = 0; i < (x * y); i++)
    {
        field.push_back(make_shared<Tile>(i));
    }
}

void Minefield::generateMines(int numMines)
{
    auto fieldCopy = field;
    for (int i = 0; i < numMines; i++)
    {
        std::random_shuffle(fieldCopy.begin(), fieldCopy.end());
        auto it = fieldCopy.begin();
        auto iter = *it;
        if (iter->getTileValue() == -1)
            i--;
        else
            iter->setTileValue(-1);
    }
}

void Minefield::generateValues()
{
    for (auto tile : field)
    {
        int position = tile->getTilePosition();
        for (int direction : {1, -1, fieldX, -fieldX, -fieldX - 1, -fieldX + 1, fieldX + 1, fieldX - 1})
        {
            if (!(isLooping(position, position + direction)) && tile->getTileValue() != -1)
            {
                if (field[position + direction]->getTileValue() == -1)
                    tile->setTileValue(tile->getTileValue() + 1);
            }
        }
    }
}

void Minefield::printField()
{
    int j = 1;
    for (int i = 0; i < (fieldX * fieldY); i++)
    {
        cout << setw(2) << field[i]->getTileValue() << " ";
        if ((i + 1) / fieldX == j)
        {
            cout << "\n";
            j++;
        }
    }
}

bool Minefield::isLooping(int position, int nextPosition)
{
    return (abs((nextPosition % fieldX) - (position % fieldX)) > 1 || nextPosition < 0 || nextPosition >= (fieldX * fieldY));
}