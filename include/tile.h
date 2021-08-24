#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    Tile(int num);
    void setTileValue(int newValue) { value = newValue; }
    int getTileValue() { return value; }
    int getTilePosition() { return position; }

    void flag(bool flag) { flagged = flag; }
    void uncover() { covered = false; }

    bool isFlagged() { return flagged; }
    bool isCovered() { return covered; }

private:
    bool flagged = false;
    bool covered = true;
    int position;
    int value;
};

#endif