#pragma once
#include "RpgCommands.h"
#include <vector>

class RpgViewer
{

    RpgCommands& game;

public:
    RpgViewer(RpgCommands& game);

    void display() const;
    // Display our main board
};