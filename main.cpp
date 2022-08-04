#include "Character.h"
#include "Monsters.h"
#include "RpgCommands.h"
#include "RpgControl.h"
#include "RpgViewer.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

std::unique_ptr<Character> CreateCharacter(std::string chara)
{
    if (chara == "warrior")
    {
        return std::make_unique<warrior>();
    }
    else if (chara == "hunter")
    {
        return std::make_unique<hunter>();
    }
    else
    {
        return std::make_unique<mage>();
    }
}

int main()
{

    std::string loading;
    std::cout << "Do you want to load your last save? [yes, no]" << std::endl;
    std::cin >> loading;

    if (loading == "tak")
    {
        std::fstream plik;
        plik.open("dane.txt", std::ios::in);

        int w;
        plik >> w;

        int h;
        plik >> h;

        std::string chara;
        plik >> chara;

        std::unique_ptr<Character> character = CreateCharacter(chara);

        int gold;
        plik >> gold;

        int princess;
        plik >> princess;

        std::string word;
        std::string words;

        for (int a = 0; a < h * w; a++)
        {
            plik >> word;
            words = words + word;
        }

        plik.close();


        RpgCommands board(w, h, *character);
        RpgViewer viewer(board);
        RpgControl game(board, viewer, words, gold, princess);
        game.play();
    }
    else
    {
        std::string chara;
        std::cout << "select your class [warrior, hunter, mage]" << std::endl;
        std::cin >> chara;

        std::string words = "A";


        std::unique_ptr<Character> character = CreateCharacter(chara);
        RpgCommands board(11, 11, *character);
        RpgViewer viewer(board);
        RpgControl game(board, viewer, words, 0, 0);
        game.play();
    }

    return 0;
}