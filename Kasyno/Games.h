#pragma once

#include "Player.h"

class Game
{
	protected:
		double bet;
		virtual void result(Player& p, bool isGiveUp = false) = 0;
		void finalMenu(Player& p, int nr);
	public:
		virtual void play(Player& p) = 0;
};

class Blackjack : public Game
{
	private:
		int playerScore;
		int pcScore;
		int pcHiddenScore;

		bool isHit;

		int rand1();
		int rand2();

		void hit(int points);
		void doubleDown(Player& p, int points);
		void result(Player& p, bool isGiveUp = false) override;

	public:
		Blackjack(double bet);
		void play(Player& p) override;
};

class SlotMachine : public Game
{
	private:
		int playerSymbol;
		int x, y, z;
		void draw();
		void result(Player& p, bool isGiveUp = false) override;

	public:
		SlotMachine(double bet);
		void play(Player& p) override;
};

class Roulette : public Game
{
	private:
		bool color;			// true - czarny, false - czerwony
		int number;
		int playerNumber;
		bool playerColor;
		void draw();
		void result(Player& p, bool isGiveUp = false) override;

	public:
		Roulette(double bet);
		void play(Player& p) override;
};