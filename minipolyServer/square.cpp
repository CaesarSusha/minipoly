#include "square.h"

Square:: Square()
{
    this->collection = -1;
    this->price = -1;
    this->rent = -1;
    this->owner = Player();
}

Square::Square(int collection, int price, int rent)
{
    this->collection = collection;
    this->price = price;
    this->rent = rent;
    this->owner = Player();
}

void Square::setOwner(Player newOwner)
{
    owner = newOwner;
}

Player Square::getOwner()
{
    return owner;
}

int Square::getCollection()
{
    return collection;
}

int Square::getPrice()
{
    return price;
}

int Square::getRent()
{
    return rent;
}
