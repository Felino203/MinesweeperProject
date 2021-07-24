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

private:
    vector<shared_ptr<Tile>> field;
};
