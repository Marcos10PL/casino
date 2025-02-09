#include "Player.h"
#include <iostream>

Player::Player(int id, std::string name, double money, double biggestWin)
{
	this->id = id;
	this->name = name;
	this->money = money;
	this->biggestWin = biggestWin;
}

int Player::getId() const
{
	return id;
}

double Player::getMoney() const
{ 
	return money; 
}

void Player::addMoney(double money) 
{ 
	this->money += money; 
}

double Player::getBiggestWin() const
{
	return biggestWin;
}

void Player::setBiggestWin(double win)
{
	if (win > biggestWin)
		biggestWin = win;
}

void Player::substractMoney(double money) 
{ 
	this->money -= money; 
}

std::string Player::getName() const
{ 
	return name; 
}

