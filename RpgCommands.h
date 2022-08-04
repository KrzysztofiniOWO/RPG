#pragma once
#include "Character.h"
#include "Monsters.h"
#include <memory>
#include <string>
#include <vector>

struct Coordinates
{
    int move_x;
    int move_y;

    Coordinates(int x = 0, int y = 0)
            : move_x(x)
            , move_y(y)
    {
    }

    Coordinates& operator+=(Coordinates& c)
    {
        move_x += c.move_x;
        move_y += c.move_y;
        return *this;
    }

    Coordinates& operator-=(Coordinates& c)
    {
        move_x -= c.move_x;
        move_y -= c.move_y;
        return *this;
    }
};


struct Field
{
    bool hasTree = false;
    bool hasHero = false;
    bool hasPrincess = false;
    bool hasGold = false;
    bool monsterCheck = false;
    bool hasSpider = false;
    bool hasSkeleton = false;
    bool hasZombie = false;
};

class RpgCommands
{

private:
    Field field;
    Coordinates coordinates;
    Coordinates new_coordinates;
    Coordinates saved_coordinates;
    Field& getField(const Coordinates&);
    const Field& getField(const Coordinates&) const;


protected:
    std::vector<std::vector<Field>> board;
    int width;
    int height;
    int gold = 0;
    int princess = 0;
    std::string monstype;
    Character& character;

public:
    RpgCommands(int width, int height, Character& character);

    void createBoard(int width, int height);
    // Create board for our rpg game

    int getWidth() const;
    // Width of board

    int getHeight() const;
    // Height of board

    char getFieldInfo(const Coordinates& coord) const;
    // Return state of one field from our board

    void genTrees();
    // Places trees at random positions on board (Just block some fields and make
    // oxygen)

    void placeHero();
    // Place our character on board

    void placeMonsters();
    // Place some monsters on our board
    //(Definitely not based on minecraft monsters duh)

    void placePrincess();
    // Place beautiful princess on our board. She got captured again and you need
    // to rescue her. (Btw our character ain't italian plumber. Princesses are
    // being captured in different universes too :I)

    void placeGoldPiles();
    // Place gold piles so you could earn some money

    void placeAll();
    // Use all functions placing stuff on board

    void moveCharacter();
    // Moves our character on board

    void getGold();
    // Collect pile of gold

    void getPrincess();
    // Collect our beautiful princess

    int returnGold() const;
    // Return state of gold

    int returnPrincess() const;
    // Return state of princess

    int returnCharacterHp() const;
    // Return character hp

    void randomiseMonster();
    // Select monster our character will fight with

    std::string selectDirection();
    // Select direction to move out character

    int moveVertical(std::string side, int direction);
    // Calculate vertical position of move

    int moveHorizontal(std::string side, int direction);
    // Calculate horizontal position of move

    int justRandomise(int b);
    // Return random number from range

    void fightMonster(int a);
    // Hero fight the monster

    void moveMonsters();
    // move monsters on board

    void addGold(int a);
    // Add gold to our pocket

    void addPrincess(int a);
    // Add princess to our pocket

    void setTree(const Coordinates& coord);
    // Place tree on board

    void setSkeleton(const Coordinates& coord);
    // Place skeleton on board

    void setZombie(const Coordinates& coord);
    // Place zombie on board

    void setGold(const Coordinates& coord);
    // Place gold on board

    void setHero(const Coordinates& coord);
    // Place hero on board

    void setPrincess(const Coordinates& coord);
    // Place tree on board

    void setSpider(const Coordinates& coord);
    // Place spider on board

    void setMonsterCheck(const Coordinates& coord);
    // set monster check on field

    void saveGame();
    // Save current state of game

    bool isMonsterWalkingIntoTree(const Coordinates& coord);
    // Check is monster walking into a tree

    bool isMonsterWalkingOutOfMap(const Coordinates& coord);
    // Check if monster is leaving area

    bool isMonsterWalkingIntoMonster(const Coordinates& coord);
    // Check if monster is walking into another monster

    bool isMonsterWalkingIntoHero(const Coordinates& coord);
    // Chech if monster is walking into a hero

    void selectMonsterToFight(const Coordinates& coord);
    // Checks which monster you are fighting with

    bool isMonsterBlocked(const Coordinates& coord);
    // Checks if monster can move or not

    int whichMonster(const Coordinates& coord);
    // Checks which of our monsters (spider, zombie, skeleton is on our position)

    int monsterSteps(int how_many);
    // Checks our monster x and y move

    void changeMonsterCords(const Coordinates& coord);
    // Moves our monster from one field to another
};