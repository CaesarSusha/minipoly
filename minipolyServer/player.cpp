#include "player.h"

Player::Player()
{
    this->id = -1;
    position = 0;
    purse = 10000;
}

Player::Player(QWebSocket *socket, int id)
{
    this->socket = socket;
    this->id = id;
    position = 0;
    purse = 10000;
}

int Player::getId()
{
    return id;
}

QWebSocket* Player::getSocket()
{
    return socket;
}

void Player::setPosition(int position)
{
    this->position = position;
}

int Player::getPosition()
{
    return position;
}

void Player::setPurse(int amount)
{
    purse = amount;
}

int Player::getPurse()
{
    return purse;
}
