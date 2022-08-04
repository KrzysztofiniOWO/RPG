#include "RpgCommands.h"
#include "Arena.h"
#include "Character.h"
#include "Monsters.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

RpgCommands::RpgCommands(int width,
                         int height,
                         Character& character)
        : width(width)
        , height(height)
        , character(character)


{
    createBoard(width, height);
    srand(time(NULL));
}

Coordinates operator+(const Coordinates& lhs, const Coordinates& rhs)
{
    return Coordinates{lhs.move_x + rhs.move_x, lhs.move_y + rhs.move_y};
}


std::unique_ptr<Monster> CreateMonster(int random)
{
    if (random == 0)
    {
        return std::make_unique<spider>();
    }
    else if (random == 1)
    {
        return std::make_unique<skeleton>();
    }
    else
    {
        return std::make_unique<zombie>();
    }
}

void RpgCommands::createBoard(int width, int height) // Create our main board
{
    for (int i = 0; i < width; i++)
    {
        std::vector<Field> vec;

        for (int j = 0; j < height; j++)
        {
            vec.push_back(field);
        }

        board.push_back(vec);
    }
}

int RpgCommands::getWidth() const // Return width of board
{
    return width;
}

Field& RpgCommands::getField(const Coordinates& coord)
{
    return board[coord.move_x][coord.move_y];
}

const Field& RpgCommands::getField(const Coordinates& coord) const
{
    return board[coord.move_x][coord.move_y];
}

int RpgCommands::getHeight() const // Return height of board
{
    return height;
}

char RpgCommands::getFieldInfo(const Coordinates& coord)
const // Return state of one field from our board
{
    if (getField(coord).hasTree == true)
    {
        return 'T';
    }
    else if (getField(coord).hasSpider == true)
    {
        return 'S';
    }
    else if (getField(coord).hasSkeleton == true)
    {
        return 'B';
    }
    else if (getField(coord).hasZombie == true)
    {
        return 'Z';
    }
    else if (getField(coord).hasHero == true)
    {
        return 'H';
    }
    else if (getField(coord).hasPrincess == true)
    {
        return 'P';
    }
    else if (getField(coord).hasGold == true)
    {
        return 'G';
    }
    else
    {
        return ' ';
    }
}

void RpgCommands::genTrees() // Generate trees on board
{
    int placed = 0;
    int trees = floor(width * height / 5);

    while (placed < trees)
    {
        int random = rand() % (width * height);
        int row = random / width;
        int col = random % height;
        Coordinates coordinate{row, col};
        if ((getField(coordinate).hasTree == true) || (row + 1 >= width) ||
            (col + 1 >= height) || (board[row + 1][col].hasTree == true) ||
            (getField(coordinate+Coordinates{0, 1}).hasTree == true))
            continue;
        getField(coordinate).hasTree = true;
        placed++;
    }
}

void RpgCommands::placeHero()
{
    int is_on = 0;

    while (is_on < 1)
    {
        int random = rand() % (width * height);
        int row = random / width;
        int col = random % height;
        Coordinates coordinate{row, col};

        if (getField(coordinate).hasTree == true)
            continue;
        getField(coordinate).hasHero = true;
        is_on++;
    }
}

void RpgCommands::placeMonsters()
{
    int monsters = floor(width * height / 5);
    int are_on = 0;

    while (are_on < monsters)
    {
        int random = rand() % (width * height);
        int row = random / width;
        int col = random % height;
        Coordinates coordinate{row, col};
        if ((getField(coordinate).hasTree == true) || (getField(coordinate).hasHero == true))
            continue;
        getField(coordinate).monsterCheck = true;

        int monster_number = justRandomise(3);

        if (monster_number == 0)
        {
            getField(coordinate).hasSpider = true;
        }
        else if (monster_number == 1)
        {
            getField(coordinate).hasSkeleton = true;
        }
        else
        {
            getField(coordinate).hasZombie = true;
        }

        are_on++;
    }
}

void RpgCommands::placePrincess()
{
    int is_on = 0;

    while (is_on < 1)
    {
        int random = rand() % (width * height);
        int row = random / width;
        int col = random % height;
        Coordinates coordinate{row, col};
        if ((getField(coordinate).hasTree == true) ||
            (getField(coordinate).hasHero == true) ||
            (getField(coordinate).monsterCheck == true))
            continue;
        getField(coordinate).hasPrincess = true;
        is_on++;
    }
}

void RpgCommands::placeGoldPiles()
{
    int piles = floor(width * height / 5);
    int are_on = 0;

    while (are_on < piles)
    {
        int random = rand() % (width * height);
        int row = random / width;
        int col = random % height;
        Coordinates coordinate{row, col};
        if ((getField(coordinate).hasTree == true) ||
            (getField(coordinate).hasHero == true) ||
            (getField(coordinate).hasPrincess == true) ||
            (getField(coordinate).monsterCheck == true))
            continue;
        getField(coordinate).hasGold = true;
        are_on++;
    }
}

void RpgCommands::setTree(const Coordinates& coord)
{
    getField(coord).hasTree = true;
}

void RpgCommands::setGold(const Coordinates& coord)
{
    getField(coord).hasGold = true;
}

void RpgCommands::setHero(const Coordinates& coord)
{
    getField(coord).hasHero = true;
}

void RpgCommands::setPrincess(const Coordinates& coord)
{
    getField(coord).hasPrincess = true;
}

void RpgCommands::setSpider(const Coordinates& coord)
{
    getField(coord).hasSpider = true;
}

void RpgCommands::setSkeleton(const Coordinates& coord)
{
    getField(coord).hasSkeleton = true;
}

void RpgCommands::setZombie(const Coordinates& coord)
{
    getField(coord).hasZombie = true;
}

void RpgCommands::setMonsterCheck(const Coordinates& coord)
{
    getField(coord).monsterCheck = true;
}

void RpgCommands::addGold(int a)
{
    gold += a;
}

void RpgCommands::addPrincess(int a)
{
    princess += a;
}

void RpgCommands::placeAll()
{
    genTrees();
    placeHero();
    placeMonsters();
    placePrincess();
    placeGoldPiles();
}

void RpgCommands::getGold()
{
    gold += 20;
    std::cout << "you have " << gold << " gold." << std::endl;
}

void RpgCommands::getPrincess()
{
    princess += 1;
    std::cout << "You just picked up a beautiful princess" << std::endl;
}

int RpgCommands::returnGold() const
{
    return gold;
}

int RpgCommands::returnPrincess() const
{
    return princess;
}

int RpgCommands::returnCharacterHp() const
{
    return character.hp;
}

int RpgCommands::justRandomise(int b)
{
    int random = rand() % (b);
    return random;
}

void RpgCommands::fightMonster(int a)
{
    std::unique_ptr<Monster> mon = CreateMonster(a);
    Arena arena(character, *mon);
    arena.fight();
}

std::string RpgCommands::selectDirection()
{
    std::string direction;
    std::cout << "In which direction you want to move your character [up, down, "
                 "left, right, save_game]"
              << std::endl;
    std::cin >> direction;
    return direction;
}

int RpgCommands::moveHorizontal(std::string side, int direction)
{
    if (side == "up")
    {
        direction = -1;
    }
    else if (side == "down")
    {
        direction = 1;
    }

    return direction;
}

int RpgCommands::moveVertical(std::string side, int direction)
{
    if (side == "right")
    {
        direction = 1;
    }
    else if (side == "left")
    {
        direction = -1;
    }

    return direction;
}

void RpgCommands::selectMonsterToFight(const Coordinates& coord)
{
    if (getField(coord).hasSpider == true)
    {
        fightMonster(0);
        getField(coord).monsterCheck = false;
        getField(coord).hasSpider = false;
    }
    else if (getField(coord).hasSkeleton == true)
    {
        fightMonster(1);
        getField(coord).monsterCheck = false;
        getField(coord).hasSkeleton = false;
    }
    else if (getField(coord).hasZombie == true)
    {
        fightMonster(2);
        getField(coord).monsterCheck = false;
        getField(coord).hasZombie = false;
    }

}

void RpgCommands::moveCharacter()
{

    for (int i = 0; i < width; i++) // find position of our character
    {
        for (int j = 0; j < height; j++)
        {
            if (board[i][j].hasHero == true)
            {
                coordinates.move_x = i;
                coordinates.move_y = j;
            }
        }
    }

    std::string direction = selectDirection();

    new_coordinates.move_x = 0;
    new_coordinates.move_y = 0;

    new_coordinates.move_x = moveHorizontal(direction, new_coordinates.move_x);
    new_coordinates.move_y = moveVertical(direction, new_coordinates.move_y);
    coordinates += new_coordinates;

    if (direction == "save_game")
    {
        saveGame();
    }
    else
    {

        if ((coordinates.move_y < 0) || (coordinates.move_x < 0) || (coordinates.move_y >= width) ||
            (coordinates.move_x >= height)) // Incorrect move
        {
            std::cout << "Invisible barrier stops you from leaving our game area. "
                         "Make move in correct direction"
                      << std::endl;
        }
        else // Correct move
        {
            if (board[coordinates.move_x][coordinates.move_y].hasTree == true)
            {
                std::cout << "You bumped into a tree silly. Now tree is sad. Make move "
                             "in correct direction"
                          << std::endl;
            }
            else
            {
                coordinates -= new_coordinates;
                board[coordinates.move_x][coordinates.move_y].hasHero = false;
                coordinates += new_coordinates;
                board[coordinates.move_x][coordinates.move_y].hasHero = true;

                if (board[coordinates.move_x][coordinates.move_y].hasGold == true)
                {
                    getGold();
                    board[coordinates.move_x][coordinates.move_y].hasGold = false;
                }
                else if (board[coordinates.move_x][coordinates.move_y].hasPrincess == true)
                {
                    getPrincess();
                    board[coordinates.move_x][coordinates.move_y].hasPrincess = false;
                }
                else if (board[coordinates.move_x][coordinates.move_y].monsterCheck == true)
                {
                    selectMonsterToFight(coordinates);
                }
                else
                {
                    std::cout << "You moved your character. Yikes!" << std::endl;
                }
            }
        }
    }
}

void RpgCommands::saveGame()
{
    std::fstream plik;
    plik.open("dane.txt", std::ios::out);

    plik << width << std::endl;
    plik << height << std::endl;
    plik << character.returnName() << std::endl;
    plik << gold << std::endl;
    plik << princess << std::endl;

    std::string word;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (getFieldInfo({i, j}) == ' ')
            {
                plik << '.';
            }
            else
            {
                plik << getFieldInfo({i, j});
            }
        }
        // plik << word << std::endl;
        plik << std::endl;
    }

    plik.close();
}

bool RpgCommands::isMonsterWalkingOutOfMap(const Coordinates& coord)
{
    return(coord.move_x < 0) || (coord.move_y < 0) || (coord.move_x>= width) || (coord.move_y >= height);
}

bool RpgCommands::isMonsterWalkingIntoTree(const Coordinates& coord)
{
    return(getField(coord).hasTree);
}

bool RpgCommands::isMonsterWalkingIntoMonster(const Coordinates& coord)
{
    return(getField(coord).monsterCheck);
}

bool RpgCommands::isMonsterWalkingIntoHero(const Coordinates& coord)
{
    return(getField(coord).hasHero);
}

bool RpgCommands::isMonsterBlocked(const Coordinates& coord)
{
    if(isMonsterWalkingOutOfMap(coord))
    {
        return true;
    }

    if(isMonsterWalkingIntoMonster(coord) || isMonsterWalkingIntoMonster(coord) || isMonsterWalkingIntoHero(coord))
    {
        return true;
    }

    return false;
}

int RpgCommands::whichMonster(const Coordinates& coord)
{
    if (getField(coord).hasSpider == true)
    {
        return 0;
    }
    else if (getField(coord).hasSkeleton == true)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

int RpgCommands::monsterSteps(int how_many)
{
    int x=0, side;

    for(int i = 0; i<how_many; i++)
    {
        side = justRandomise(2);
        if (side == 0)
        {
            x++;
        }else
        {
            x--;
        }
    }
    return x;
}

void RpgCommands::changeMonsterCords(const Coordinates& coord)
{
    if (getField(coord).monsterCheck == true)
    {
        coordinates.move_x = coord.move_x;
        coordinates.move_y = coord.move_y;

        saved_coordinates.move_x = coord.move_x;
        saved_coordinates.move_y = coord.move_y;

        int which = whichMonster(coord);

        int how_much = justRandomise(2);

        new_coordinates.move_x = monsterSteps(how_much);
        new_coordinates.move_y = monsterSteps((1 - how_much));

        coordinates += new_coordinates;

        if (isMonsterBlocked(coordinates) == false)
        {
            coordinates -= new_coordinates;
            board[coordinates.move_x][coordinates.move_y].monsterCheck = false;
            coordinates += new_coordinates;
            board[coordinates.move_x][coordinates.move_y].monsterCheck =
                    true;
            if (which == 0)
            {
                board[coordinates.move_x][coordinates.move_y].hasSpider = true;
                coordinates -= new_coordinates;
                board[coordinates.move_x][coordinates.move_y].hasSpider = false;
            }
            else if (which == 1)
            {
                board[coordinates.move_x][coordinates.move_y].hasSkeleton = true;
                coordinates -= new_coordinates;
                board[coordinates.move_x][coordinates.move_y].hasSkeleton = false;
            }
            else
            {
                board[coordinates.move_x][coordinates.move_y].hasZombie = true;
                coordinates -= new_coordinates;
                board[coordinates.move_x][coordinates.move_y].hasZombie = false;
            }

        }

    }

}