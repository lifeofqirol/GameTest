#ifndef Hero_hpp
#define Hero_hpp

using namespace std;

class Hero
{
private:
    double balance;
public:
    Hero(int);                    //CONSTRUCTOR
    string className;
    int hp;
    int mp;
    int att;
    int def;
    int spd;
    
    double getBalance();          //ACCESSOR
    void editBalance(double);      //MUTATOR
    //void promoteClass
    //void skillpoints
};

#endif /* Hero_hpp */
