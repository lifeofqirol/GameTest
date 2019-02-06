#include "iostream"
#include "Gamble.hpp"

using namespace std;

double gambleMenu (Hero player)
{
    double reward = 0;
    int choice = 0;
    char htp;
    cout<<"1. Roll dice"<<endl;
    cout<<"2. Guess numbers"<<endl;
    cout<<"(enter any other number to leave)"<<endl;
    cout<<"I want to (#): ";
    
    cin>>choice;
    cin.ignore();
    cout<<endl;
    
    if (choice >= 1 && choice <= 2)
    {
        cout<<"See the game's \"How to Play\" (Y)? ";
        cin>>htp;
        if (toupper(htp) == 'Y')
            howToPlay(choice);
        else
            cout<<endl;
    }
    
    switch (choice)
    {
        case 1:
        {
            reward = diceGame(player);
            break;
        }
        case 2:
        {
            reward = numberGame(player);
            break;
        }
        default:
        {
            cout<<"Returning to Menu";
            break;
        }
    }
    
    if (reward > 0)
        cout<<endl<<"You won "<<reward<<"ø";
    else if (reward < 0)
        cout<<endl<<"You lost "<<(reward*-1)<<"ø"<<endl;
    
    return reward;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double diceGame (Hero player)
{
    int dice = 0;                                                               //minStake (auto) - depends on Balance
    double stake = 0, minStake = 1, maxStake = 0;
    double balance = player.getBalance();
    minStake = getMinStake(balance);
    
    
    cout<<"How many die (1-5)? ";                                               //dice (user)
    cin>>dice;
    cin.ignore();
    while (dice < 1 || dice > 5)
    {
        cout<<endl<<"Invalid count, choose again (#): ";
        cin>>dice;
        cin.ignore();
    }
    
    cout<<endl<<"BALANCE:   "<<balance<<"ø"<<endl;                              //maxStake (auto) - depends on Dice
    if (dice == 1)
        maxStake = balance * 0.20;
    if (dice == 2)
        maxStake = balance * 0.25;
    if (dice == 3)
        maxStake = balance * 0.40;
    if (dice > 3)
        maxStake = balance * 0.30;
    stake = getStake(stake, minStake, maxStake);                                //stake (user)
    
    if (diceRoll (dice) == false)                                               //GAME
        stake = stake * -1;                                                     //negative if lost
    
    return stake;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool diceRoll (int dice)
{
    bool result = false;
    int min, max, roll, guess, uguess = 0;
    min = dice;
    max = dice * 6;
    
    cout<<endl<<"DICE RANGE ["<<min<<", "<<max<<"]"<<endl;                  //give range
    
    srand((unsigned int)time(0));                                           //random roll
    roll = rand()%(max - min + 1) + min;
    
    if (dice >= 1 && dice <= 3)                                              //1-3 ROLLING
    {
        cout<<"What do you guess? ";
        cin>>guess;
        cin.ignore();
        cout<<endl;
        
        if (guess > max || guess < min)                                     //test guess range
        {
            cout<<"That isn't possible!\n Rechoose: ";
            cin>>guess;
            cin.ignore();
        }
        
        if (roll == guess)                                                  //victory
        {
            cout<<"Correct!";
            result = true;
        }
        else
            cout<<"Incorrect!\nThe roll was "<<roll;                      //defeat
    }
    else if (dice > 3)                                                    //4-5 ROLLING
    {
        cout<<"Select a range of three,\n(may be autocorrected)\nyour lower guess is: ";
        cin>>guess;
        cin.ignore();
        
        if (guess <= (max - 3) && guess >= min)                          //auto-correct guess range
            uguess = guess + 3;
        else if (guess < min)
        {
            guess = min;
            uguess = guess + 3;
        }
        else if (guess >= min && guess > (max - 3))
        {
            uguess = max;
            guess = uguess - 3;
        }
        cout<<"GUESS RANGE ["<<guess<<", "<<uguess<<"]"<<endl<<endl;
        
        if (roll >= guess && roll <= uguess)                                     //victory
        {
            cout<<"Correct!"<<endl<<"the roll was "<<roll;
            result = true;
        }
        else                                                                    //defeat
            cout<<"Incorrect!\nThe roll was "<<roll;
    }
    return result;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double numberGame(Hero player)
{
    int numbers = 0;                                                               //minStake (auto) - depends on Balance
    double stake = 0, minStake = 1, maxStake = 0, revStake = 0;
    double balance = player.getBalance();
    minStake = getMinStake(balance);
    
    cout<<"Number length (4-7)? ";                                               //numbers (user)
    cin>>numbers;
    cin.ignore();
    while (numbers < 4 || numbers > 7)
    {
        cout<<endl<<"Invalid value, choose again (#): ";
        cin>>numbers;
        cin.ignore();
    }
    
    cout<<endl<<"BALANCE:   "<<balance<<"ø"<<endl;                              //maxStake (auto) - depends on Dice
    if (numbers <= 5)
        maxStake = balance * 0.10;
    else
        maxStake = balance * 0.20;
    
    stake = getStake(stake, minStake, maxStake);                                //stake (user)
    
    revStake = stake * numGuess(numbers);                                          //GAME
    if (stake > revStake)
    {
        revStake = stake - revStake;                                             //defeat
        revStake = revStake * -1;
    }
    else
        revStake = revStake - stake;                                             //victory
    
    return revStake;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double numGuess(int numbers)
{
    double multiplier = 1;
    int method = 0;
    
    int sequence[numbers];                                                      //randomizer
    srand((unsigned int)(time(0)));
    for (int i = 0; i < numbers; i++)
        sequence[i] = rand()%(9)+1;
    
    cout<<endl;
    cout<<"1. 1 by 1"<<endl;
    cout<<"2. X of #"<<endl;
    cout<<"Choose your method of guessing (#): ";
    cin>>method;
    cin.ignore();
    while (method != 1 && method != 2)
    {
        cout<<"Invalid selection, choose again (#): ";
        cin>>method;
        cin.ignore();
    }
    cout<<endl;
    
    if (method == 1)
        multiplier = onebyone(sequence, numbers);
    else
        multiplier = xofnum(sequence, numbers);
    
    return multiplier;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double onebyone(int sequence[], int numbers)
{
    double multiplier = 1;
    int guess[numbers], correct = 0;
    
    for (int i = 0; i < numbers; i++)
    {
        cout<<"GUESS "<<(i+1)<<": ";
        cin>>guess[i];
        cin.ignore();
        while (guess[i] < 1 || guess[i] > 9)
        {
            cout<<"Invalid (1-9)\nGUESS "<<(i+1)<<": ";
            cin>>guess[i];
            cin.ignore();
        }
        if (guess[i] == sequence[i])
        {
            multiplier += (numbers * 0.065);
            correct++;
        }
        else
            multiplier -= (numbers * 0.035);
    }
    
    cout<<endl<<"You got "<<correct<<" out of "<<numbers<<endl;
    cout<<"YOUR SEQUENCE   ";
    for (int i = 0; i < numbers; i++)
        cout<<guess[i];
    cout<<endl<<"TRUE SEQUENCE   ";
    for (int i = 0; i < numbers; i++)
        cout<<sequence[i];
    cout<<endl;
    
    return multiplier;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double xofnum(int sequence[], int numbers)
{
    double multiplier = 1;
    int guess = 0, count, correct = 0;
    
    cout<<"(enter 0 to abstain)"<<endl;
    for (int i = 1; i < 10; i++)
    {
        count = 0;
        cout<<i<<" COUNT: ";
        cin>>guess;
        cin.ignore();
        while (guess < 0 || guess > numbers)
        {
            cout<<"Invalid (1-"<<numbers<<")\n"<<i<<" COUNT: ";
            cin>>guess;
            cin.ignore();
        }
        if (guess == 0) {}
        else
        {
            for (int j = 0; j < numbers; j++)
            {
                if (sequence[j] == i)
                    count++;
            }
            if (count == guess)
            {
                multiplier += (numbers * 0.045);
                correct++;
            }
            else
                multiplier -= (numbers * 0.025);
        }
    }
    
    cout<<endl<<"You got "<<correct<<" guesses correct"<<endl;
    cout<<"TRUE SEQUENCE   ";
    for (int i = 0; i < numbers; i++)
        cout<<sequence[i];
    cout<<endl;
    
    return multiplier;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double getMinStake(double balance)
{
    double minStake = 0;
    if (balance > 100 && balance <= 10000)
        minStake = balance * 0.01;
    else if (balance > 10000)
        minStake = balance * 0.005;
    return minStake;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
double getStake(double stake, double minStake, double maxStake)
{
    cout<<"MAX STAKE: "<<maxStake<<"ø"<<endl;
    cout<<"MIN STAKE: "<<minStake<<"ø"<<endl;
    cout<<"What is your stake (#)? ";
    cin>>stake;
    cin.ignore();
    
    while (stake > maxStake || stake < minStake)                                //test stake range
    {
        cout<<"Stake is invalid, rechoose (#): ";
        cin>>stake;
        cin.ignore();
    }
    
    return stake;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void howToPlay(int choice)
{
    cout<<endl;
    if (choice == 1)
    {
        cout<<"DICE GAME: After selecting how many die to roll, guess the number for the total roll.\n";
        cout<<"If you were correct, you win your stake; if you were wrong, you lose your stake.";
    }
    else if (choice == 2)
    {
        cout<<"NUMBER GAME: An array is created based on your length selection.\n";
        cout<<"Each number in the sequence is from 1 to 9;\n";
        cout<<"Choose a method to guess the sequence:\n";
        cout<<"\tone by one allows you to guess each value sequentially\n";
        cout<<"\tx of number allows you to guess how much each value may show up\n";
        cout<<"You gain or lose money based on a stake multiplier onto your guesses.";
    }
    cout<<endl<<endl;
}
