#include "dice.h"
#include <ctime>
#include <random>
#include <cctype>

Dice::Dice()
{
    this->eyes = 0;
}

Dice::Dice(int Eyes)
{
    this->eyes = Eyes;
}

/*
int Dice::rollDice()
{
    if (eyes == 0)
    {
        return -1;
    }
    //Gibt eine Zufällige Zahl zwischen 1 und der Anzahl der Augen des Würfels aus
    std::random_device os_seed;
    const uint_least32_t seed = os_seed();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(1, eyes);
    //return distribute(generator);
}
*/

int Dice::rollDice()
{
    //Den seed des Zufallsgenerators setzen
    srand((unsigned) time(NULL));
    //Die Zufallszahl soll Werte von 1 bis 12 annehmen können
    return 1 + (rand() % 12);
}
