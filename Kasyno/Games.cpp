#include <iostream>
#include <windows.h>

#include "Games.h"
#include "variables.h"

using namespace std;

//--------------GAME--------------//

void Game::finalMenu(Player& p, int nr)
{
	if (p.getMoney() < MIN_VALUE_OF_MONEY)
	{
		Sleep(3500);
		showMenu(p, END);
	}
	else
	{
		int chosen;

		cout << "\n\n1 - wyjdz do menu\n";
		cout << "2 - zagraj jeszcze raz\n";

		cout << "Wybierz opcje (1 lub 2): ";
		chosen = choice(1, 2);

		switch (chosen)
		{
		case 1:
			showMenu(p);
			break;
		case 2:
			showMenu(p, nr);
			break;
		}
	}
}

//--------------BlACKJACK--------------//

Blackjack::Blackjack(double bet)
{
	pcScore = rand1();
	pcHiddenScore = rand2();
	playerScore = rand1() + rand2();
	this->bet = bet;
	isHit = false;
}

int Blackjack::rand1()
{ 
	return (rand() % 11 + 1); 
}

int Blackjack::rand2()
{ 
	return (rand() % 10 + 1);
}

void Blackjack::hit(int points)
{
	playerScore += points;
	isHit = true;
}

void Blackjack::doubleDown(Player& p, int points)
 {
	 bet *= 2;
	 hit(points);
	 result(p);
 }

void Blackjack::play(Player& p)
{
	int chosen;
	system("cls");

	cout << "---- BLACKJACK ---- \n";
	cout << "\nTwoje saldo: " << p.getMoney();
	cout << "\nPodaj stawke za ktora chcesz zagrac (min. 100): " << bet;

	cout << "\n\nWynik komputera: " << pcScore << " + X (" << pcScore << " + X < 22)\n";
	cout << "Twoj aktualny wynik: " << playerScore << "\n\n";

	if (playerScore > 21)
	{
		result(p);
		return;
	}

	if (bet * 2 > p.getMoney())
		isHit = true;

	cout << "Wartosc blizsza, ale nie wieksza niz 21 wygrywa!";
	cout << "\nUwaga, PC moze dobrac punkty jesli " << pcScore << " + X < 17\n";

	cout << "1 - dobierz punkty(0 - 10) \n"
		"2 - nie dobieraj i zakoncz gre\n"
		"3 - poddaj sie (-50%)\n";
	if (!isHit)
		cout << "4 - podwoj stawke i dobierz punkty (tylko raz)\n";

	cout << "Twoj ruch: ";
	if(!isHit)
		chosen = choice(1, 4);
	else
		chosen = choice(1, 3);

	if (chosen == 1)
	{
		hit(rand1());
		play(p);
	}
	else if (chosen == 2)
		result(p);
	else if (chosen == 3)
		result(p, true);
	else if (chosen == 4 && !isHit)
	{
		int x = rand1();
		cout << "\nPodwojona stawka: " << this->bet * 2;
		cout << "\nAktualne punkty: " << playerScore + x << "\n";
		doubleDown(p, x);
	}
}

void Blackjack::result(Player& p, bool isGiveUp)
{
	if (playerScore > 21)
	{
		cout << "Przegrales (twoj wynik jest wiekszy niz 21), tracisz " << bet;
		p.substractMoney(bet);
	}
	else if (isGiveUp)
	{
		cout << "\nPoddales sie, tracisz " << bet * 0.5;
		p.substractMoney(bet * 0.5);
	}
	else
	{
		if (pcScore + pcHiddenScore < 17)
			cout << "\nKomputer dobiera punkty (jego wynik jest mniejszy niz 17)\n";

		while (pcScore + pcHiddenScore < 17)
			pcScore += rand1();

		cout << "\nTwoj wynik: " << playerScore;
		cout << "\nCalkowity wynik komputera: " << pcScore + pcHiddenScore << "\n";

		if (pcScore + pcHiddenScore > playerScore && pcScore + pcHiddenScore <= 21)
		{
			cout << "\nPrzegrales, tracisz " << bet;
			p.substractMoney(bet);
		}
		else if (playerScore == pcScore + pcHiddenScore)
			cout << "\nRemis. Nic nie straciles";
		else
		{
			cout << "\nWygrales! Otrzymujesz " << bet * 1.5;
			p.addMoney(bet * 1.5);
			p.setBiggestWin(bet * 1.5);
		}
	}

	finalMenu(p, BJ);
 }

//--------------SLOT MACHINE--------------//

 SlotMachine::SlotMachine(double bet)
 {
	 this->bet = bet;
 }

 void SlotMachine::draw()
 {
	cout << "\nTrwa losowanie...\n";
	for (int i = 0; i <= 20000; i++)
	{
		x = rand() % 5 + 1;
		y = rand() % 5 + 1;
		z = rand() % 5 + 1;
		cout << "\b\b\b\b\b";
		cout << x << " " << y << " " << z;
	}
 }

 void SlotMachine::play(Player& p)
 {
	int chosen;

	cout << "\nWygrywa tylko wyloswana trojka odgadnietego symobolu.\n";

	cout << "Wybierz numer symbolu od 1 do 5: ";
	chosen = choice(1, 5);

	playerSymbol = chosen;
	result(p);
 }
 
 void SlotMachine::result(Player& p, bool isGiveUp)
 {
	draw();

	if (x == y == z == playerSymbol)
	{
		cout << "\nWygrales! Otrzymujesz " << bet * 3;
		p.addMoney(bet * 3);
		p.setBiggestWin(bet * 3);
	}
	else
	{
		cout << "\nPrzegrales, tracisz " << bet;
		p.substractMoney(bet);
	}

	 finalMenu(p, SM);
 }

//--------------ROULETTE--------------//

Roulette::Roulette(double bet)
{
	this->bet = bet;	
	color = false;			// czerwona
	playerColor = false;
} 

void Roulette::draw()
{
	int czarne[16] = { 2, 5, 7, 8, 10, 11, 12, 15, 16, 17, 21, 25, 26, 27, 29, 32 };

	number = rand() % 33;	

	for (int i = 0; i < 16; i++)
		if (czarne[i] == number)
		{
			color = true;			// czarna
			break;
		}
}

void Roulette::play(Player& p)
{
	int chosen;

	cout << "\n";

	cout << "Wybierz numer od 1 do 32: ";
	chosen = choice(1, 32);

	playerNumber = chosen;

	cout << "\nWybierz kolor (1 - czwerony, 2 - czarny): ";
	chosen = choice(1, 2);

	if (chosen == 2)
		playerColor = true;

	result(p);
}

void Roulette::result(Player& p, bool isGiveUp)
{
	draw();

	cout << "\nWylosowana liczba: " << number;
	cout << "\nTa liczba ma kolor "<< (color ? "czarny" : "czerwony");

	double win = 0;
	if (playerColor == color && playerNumber == number)
	{
		win = bet * 6;
		cout << "\nTrafiles dwojke! Twoja stawka zostaje pomnozona razy 6, wygrywasz " <<  win;

	}
	else if (playerColor == color)
	{
		win = bet * 2;
		cout << "\nTrafiles w kolor! Twoja stawka zostaje pomnozona razy 2, wygrywasz " <<  win;
	}
	else if(playerNumber == number)
	{
		win = bet * 3;
		cout << "\nTrafiles w numer! Twoja stawka zostaje pomnozona razy 3, wygrywasz " << bet * 3;
	}
	else
	{
		cout << "\nPrzegrywasz, tracisz " << bet;
		p.substractMoney(bet);
	}

	if (win)
	{
		p.addMoney(win);
		p.setBiggestWin(win);
	}

	finalMenu(p, R);
}