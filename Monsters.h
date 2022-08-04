#pragma once
#include <iostream>
#include <string>

class Monster
{
public:
    std::string name;
    int hp;
    int dmg;

    // virtual int getSpeed() = 0;
    // Our monsters move differently (spider 3, skeleton 2, zombie 1 move per
    // turn)
};

class spider : public Monster
{
public:
    spider()
    {
        hp = 50;
        dmg = 30;
        name = "spider";
    }

    // int getSpeed() override;
};

class skeleton : public Monster
{
public:
    skeleton()
    {
        hp = 120;
        dmg = 20;
        name = "skeleton";
    }

    // int getSpeed() override;
};

class zombie : public Monster
{
public:
    zombie()
    {
        hp = 200;
        dmg = 10;
        name = "zombie";
    }

    // int getSpeed() override;
};