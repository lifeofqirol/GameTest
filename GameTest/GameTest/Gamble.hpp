#ifndef Gamble_hpp
#define Gamble_hpp
#include "Hero.hpp"

double gambleMenu(Hero);
void howToPlay(int);

double diceGame(Hero);
bool diceRoll (int);

double numberGame(Hero);
double numGuess(int);
double onebyone(int[], int);
double xofnum(int[], int);

double getMinStake(double);
double getStake(double, double, double);

#endif /* Gamble_hpp */
