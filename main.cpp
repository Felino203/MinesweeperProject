#include <iostream>
#include <vector>
#include <string>
#include "model/minefield.hpp"
#include "model/tile.hpp"

using namespace std;

void clearConsole()
{
    for (int i = 0; i < 20; i++)
    {
        cout << "\n";
    }
}

int main()
{
    clearConsole();

    Minefield minefield = Minefield(16, 30);
    minefield.generateMines(99);
    minefield.generateValues();
    minefield.printField();

    cout << "\n";
}