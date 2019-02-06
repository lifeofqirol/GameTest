#include <iostream>
#include "Hero.hpp"

using namespace std;

Hero::Hero(int choice)
{
    balance = 10000;
    
    switch (choice)
    {
        case 1:
        {
            className = "Warrior";
            hp = 55;
            mp = 15;
            att = 25;
            def = 20;
            spd = 10;
            break;
        }
        case 2:
        {
            className = "Mage";
            hp = 40;
            mp = 45;
            att = 15;
            def = 15;
            spd = 20;
            break;
        }
        case 3:
        {
            className = "Rogue";
            hp = 35;
            mp = 15;
            att = 30;
            def = 20;
            spd = 40;
            break;
        }
        case 4:
        {
            className = "Knight";
            hp = 25;
            mp = 15;
            att = 20;
            def = 40;
            spd = 10;
            break;
        }
        case 5:
        {
            className = "Ronin";
            hp = 35;
            mp = 10;
            att = 45;
            def = 15;
            spd = 20;
            break;
        }
    }
}

double Hero::getBalance()
{
    return balance;
}

void Hero::editBalance(double transaction)
{
    balance += transaction;
}
