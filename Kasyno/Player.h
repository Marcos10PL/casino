#pragma once

#include <string>

class Player
{
	private:
		int id;
		std::string name;
		double money;
		double biggestWin;
	public:
		Player() = default;
		Player(int id, std::string name, double money, double win);
		std::string getName() const;
		int getId() const;
		double getMoney() const;
		double getBiggestWin() const;
		void setBiggestWin(double win);
		void addMoney(double money);
		void substractMoney(double money);
};