#include "Arena.h"
#include "Character.h"
#include "Monsters.h"
#include <iostream>

Arena::Arena(Character& character, Monster& monster)
        : character(character)
        , monster(monster)
{
}

void Arena::fight()
{
    std::cout << character.name << " encounters " << std::endl
              << monster.name << std::endl;

    while ((character.hp > 0) && (monster.hp > 0))
    {
        std::cout << monster.name << " takes " << character.dmg << " damage."
                  << std::endl;
        monster.hp -= character.dmg;
        if (monster.hp > 0)
        {
            std::cout << character.name << " takes " << monster.dmg << " damage."
                      << std::endl;
            character.hp -= monster.dmg;
        }
    }

    if (monster.hp < 0)
    {
        std::cout << monster.name << " has been defeated by " << character.name
                  << std::endl;
        character.regenHp();
    }
    else if (character.hp < 0)
    {
        std::cout << character.name << " has been defeated by " << monster.name
                  << std::endl;
        std::cout << character.name
                  << " you failed to complete your quest. Maybe next hero will "
                     "have enough luck to do so."
                  << std::endl;
    }
}