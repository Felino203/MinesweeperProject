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

    Minefield minefield = Minefield(10, 10);
    minefield.getField();

    cout << "console display: \n\n";
}