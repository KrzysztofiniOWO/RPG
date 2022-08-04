#include "RpgControl.h"
#include "RpgCommands.h"
#include "RpgViewer.h"
#include <cstdlib>
#include <iostream>

RpgControl::RpgControl(RpgCommands& game,
                       RpgViewer& viewer,
                       std::string words,
                       int gold,
                       int princess)
        : game(game)
        , viewer(viewer)
        , words(words)
        , gold(gold)
        , princess(princess)
{
}

void RpgControl::play()
{

    if (words == "A")
    {
        game.placeAll();
    }
    else
    {
        game.addGold(gold);
        game.addPrincess(princess);
        for (int i = 0; i < (game.getWidth() * game.getHeight()); i++)
        {
            div_t wynik1 = div(i, game.getWidth());
            Coordinates coordinates{wynik1.quot, (i % game.getWidth())};
            if (words[i] == 'G')
            {
                game.setGold(coordinates);
            }
            else if (words[i] == 'P')
            {
                game.setPrincess(coordinates);
            }
            else if (words[i] == 'H')
            {
                game.setHero(coordinates);
            }
            else if (words[i] == 'T')
            {
                game.setTree(coordinates);
            }
            else if (words[i] == 'S')
            {
                game.setSpider(coordinates);
                game.setMonsterCheck(coordinates);
            }
            else if (words[i] == 'B')
            {
                game.setSkeleton(coordinates);
                game.setMonsterCheck(coordinates);
            }
            else if (words[i] == 'Z')
            {
                game.setZombie(coordinates);
                game.setMonsterCheck(coordinates);
            }
        }
    }

    while (((game.returnGold() < 100) || (game.returnPrincess() < 1)) &&
           (game.returnCharacterHp() > 0))
    {

        viewer.display();
        game.moveCharacter();
        for(int i = 0; i < game.getWidth(); i++)
        {
            for(int j = 0; j < game.getHeight(); j++)
            {
                Coordinates coordinates{i, j};
                game.changeMonsterCords(coordinates);
            }

        }
    }

    if ((game.returnGold() >= 100) && (game.returnPrincess() >= 1))
    {
        std::cout << "Wow you won. Congrats." << std::endl;
    }
    else
    {
        std::cout << "You failed to complete your quest. Maybe next hero will have "
                     "enough luck to do so."
                  << std::endl;
    }
}