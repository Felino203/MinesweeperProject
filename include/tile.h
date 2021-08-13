#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    Tile(int num);
    void setTileValue(int newValue) { value = newValue; }
    int getTileValue() { return value; }
    int getTilePosition() { return position; }

private:
    int position;
    int value;
};

#endif