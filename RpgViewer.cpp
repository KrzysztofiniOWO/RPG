#include "RpgViewer.h"
#include "RpgCommands.h"
#include <iostream>

RpgViewer::RpgViewer(RpgCommands& game)
        : game(game)
{
}

void RpgViewer::display() const
{
    for (int i = 0; i < game.getWidth(); i++)
    {
        for (int j = 0; j < game.getHeight(); j++)
        {
            std::cout << "[";
            std::cout << game.getFieldInfo({i, j});
            std::cout << "]";
        }
        std::cout << std::endl;
    }
}