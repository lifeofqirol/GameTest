/*#ifndef Monster_hpp
 #define Monster_hpp
 
 using namespace std;
 
 class Monster
 {
 int loot = NULL;
 int variance;
 public:
 Monster(int);            //CONSTRUCTOR
 ~Monster();              //DESTRUCTOR
 int hp;
 int mp;
 int att;
 int def;
 int spd;
 double getLoot();        //RETURN LOOT WHEN DEAD
 };
 
 class Goblin : public Monster
 {
 loot = 10;
 variance 10;
 public:
 hp = 30;
 mp = 0;
 att = 15;
 def = 5;
 spd = 20;
 };
 
 #endif*/ /* Monster_hpp */

