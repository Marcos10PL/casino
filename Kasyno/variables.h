#pragma once

#include <vector>
#include <string>

bool isValidInput(int val);
bool isValidInput(double val);
bool isValidInput(std::string val, int size);

double playerBet(double playerScore);

void showMenu(Player& p, int chosen = 0);

void showListTop100(Player& p);
std::vector <Player> loadListPlayers();

std::string nameOfGameType(int gt);

int choice(int x, int y);

const int MIN_VALUE_OF_MONEY = 100;
const int BJ = 1;
const int SM = 2;
const int R = 3;
const int TOP100 = 4;
const int END = 5;