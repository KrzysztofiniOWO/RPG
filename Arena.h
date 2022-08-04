#pragma once
#include "Character.h"
#include "Monsters.h"
#include <iostream>

class Arena
{

    Character& character;
    Monster& monster;

public:
    Arena(Character& character, Monster& monster);

    void fight();
    // Character and random monster fight
};