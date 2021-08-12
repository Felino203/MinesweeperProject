#pragma once
#include <string>
#include <vector>
#include <memory>
using namespace std;

class Tile;

class Minefield
{
public:
    Minefield(int x, int y);
    vector<shared_ptr<Tile>> getField() { return field; }
    void generateMines(int numMines);
    void generateValues();
    void printField();

private:
    bool isLooping(int position, int nextPosition);
    vector<shared_ptr<Tile>>
        field;
    int fieldX;
    int fieldY;
};
