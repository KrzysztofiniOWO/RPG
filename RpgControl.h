#pragma once
#include "RpgCommands.h"
#include "RpgViewer.h"
#include <vector>

class RpgControl
{

    RpgCommands& game;
    RpgViewer& viewer;
    std::string words;
    int gold;
    int princess;

public:
    RpgControl(RpgCommands& game,
               RpgViewer& viewer,
               std::string words,
               int gold,
               int princess);

    void play(); // Control behaviour of our game
};