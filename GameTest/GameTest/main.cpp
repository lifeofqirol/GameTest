#include <iostream>
#include <string>
#include "Hero.hpp"
#include "Gamble.hpp"

using namespace std;
int start ();
int menu (int);
double menuSelection (int, Hero);
void displayStats (Hero);

int main()
{
    int choice = 0;
    double transaction = 0;
    choice = start();                       //character creation
    Hero player(choice);                    //construct class object
    cout<<endl;
    displayStats(player);
    
    do
    {
        choice = menu(choice);                                      //display menu
        transaction = menuSelection(choice,player);                 //end of all options are loot/loss, or 0                **improve this!
        player.editBalance(transaction);                            //change money (SO IT'S LOCAL TO MAIN, NOT A FUNCTION)
    } while (choice != 7);
    
    cin.get();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int menu (int choice)
{
    cout<<endl<<"=================================\h\"<<endl;
    cout<<"What would you like to do next?  ||"<<endl;
    cout<<"1. Fight                         ||"<<endl;
    cout<<"2. Hunt                          ||"<<endl;
    cout<<"3. Shop                          ||"<<endl;
    cout<<"4. Gamble                        ||"<<endl;
    cout<<"5. Check Balance                 ||"<<endl;
    cout<<"6. Check Stats                   ||"<<endl;
    cout<<"7. Quit Game                     ||"<<endl;
    cout<<"I shall (#): ";
    
    cin>>choice;                                                //MENU CHOICE
    cin.ignore();
    
    while (choice > 7 || choice < 1)                            //INVALID SELECTION
    {
        cout<<endl<<"Invalid option! Select again: ";
        cin>>choice;
        cin.ignore();
    }
    cout<<"=================================/"<<endl<<endl;
    return choice;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double menuSelection (int choice, Hero player)
{
    double reward = 0;
    switch (choice)
    {
        case 1:                                                                     //FIGHT
        {
            break;
        }
        case 2:                                                                     //HUNT
        {
            
            break;
        }
        case 3:                                                                     //SHOP
        {
            
            break;
        }
        case 4:                                                                     //GAMBLE
        {
            if (player.getBalance() == 0)
            {
                cout<<"You can't play with no money!"<<endl;
                break;
            }
            reward = gambleMenu(player);
            break;
        }
        case 5:                                                                     //BALANCE
        {
            cout<<"\tBALANCE: "<<player.getBalance()<<"ø"<<endl;
            break;
        }
        case 6:                                                                     //STATS
        {
            displayStats(player);
            break;
        }
        case 7:                                                                     //QUIT
        {
            cout<<endl<<"Thanks for playing!";
            break;
        }
    }
    return reward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void displayStats (Hero player)
{
    cout<<player.className<<endl;
    cout<<"HP:    "<<player.hp<<endl;
    cout<<"MP:    "<<player.mp<<endl;
    cout<<"ATT:   "<<player.att<<endl;
    cout<<"DEF:   "<<player.def<<endl;
    cout<<"SPD:   "<<player.spd<<endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int start()
{
    cout<<"     Welcome worthy hero!"<<endl;                    //MENU
    cout<<"|==============================|"<<endl;
    cout<<"1. Warrior   (HIGH HP, LOW SPD)"<<endl;              //--> juggernaut, Berserker
    cout<<"2. Mage      (HIGH MP, LOW ATT)"<<endl;              //--> sorcerer, Sage
    cout<<"3. Rogue     (HIGH SPD, LOW MP)"<<endl;              //--> druid, Performer
    cout<<"4. Knight    (HIGH DEF, LOW HP)"<<endl;              //--> paladin, Inquisitor
    cout<<"5. Ronin     (HIGH ATT, LOW DEF)"<<endl;             //--> daimyo, Shogun
    cout<<"choose your class (#): ";
    
    int choice = 0;
    cin>>choice;                                                //MENU CHOICE
    cin.ignore();
    
    while (choice > 5 || choice < 1)                            //INVALID SELECTION
    {
        cout<<"Invalid choice! Choose a class by selecing the class number 1-5: ";
        cin>>choice;
        cin.ignore();
    }
    return choice;
}
