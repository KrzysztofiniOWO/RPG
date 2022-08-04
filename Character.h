#pragma once
#include <cmath>
#include <iostream>
#include <string>

class Character
{
public:
    std::string name;
    int hp;
    int dmg;

    virtual std::string returnName() { return name; };
    virtual void regenHp() = 0;
};

class warrior : public Character
{
public:
    warrior()
    {
        hp = 300;
        dmg = 30;
        name = "warrior";
    }

    void regenHp() override { hp += floor((hp / 5)); }
};

class hunter : public Character
{
public:
    hunter()
    {
        hp = 200;
        dmg = 50;
        name = "hunter";
    }

    void regenHp() override { hp += floor((hp / 3)); }
};

class mage : public Character
{
public:
    mage()
    {
        hp = 100;
        dmg = 100;
        name = "mage";
    }

    void regenHp() override { hp += floor((hp / 2)); }
};