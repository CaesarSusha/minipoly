#include "dice.h"
#include <random>
#include <cctype>

Dice::Dice()
{
    this->Eyes = 0;
}

Dice::Dice(int Eyes)
{
    this->Eyes = Eyes;
}

int Dice::rollDice()
{
    if (Eyes == 0)
    {
        return 0;
    }
    //Gibt eine Zufällige Zahl zwischen 1 und der Anzahl der Augen des Würfels aus
    std::random_device os_seed;
    const uint_least32_t seed = os_seed();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribute(1, Eyes);
    return distribute(generator);
}
