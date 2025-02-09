#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <conio.h>

#include "Player.h"
#include "variables.h"
#include "Games.h"

using namespace std;

vector <Player> players = loadListPlayers();
const int ID = players.size() + 1;
bool isActualPlayerInPlayers = false;

int main()
{
	cout << "--------- WITAJ W KASYNIE! ---------\n\n";
	cout << "Aby rozpoczac gre, podaj swoje imie.\n";
	cout << "Imie moze skladac sie wylacznie z liter (min. 3 znaki): ";

	string name;
	getline(cin, name);

	while (!isValidInput(name, 3))
	{
		cout << "Sprobuj jeszcze raz: ";
		getline(cin, name);
	}

	srand(time(0));
	int money = rand() % 9000 + 1000;

	int isFirstUpper = false;
	for (char &ch : name)
	{
		ch = tolower(ch);
		if (!isFirstUpper)
		{
			ch = toupper(ch);
			isFirstUpper = true;
		}
	}

	Player p (ID, name, money, 0);
	showMenu(p);
}

//-----------FUNCKJE-----------\\

// menu
bool isOn = true, isName = false;
void showMenu(Player& p, int chosen)
{
	do
	{
		if (players.size() == 0 && p.getBiggestWin() > 0)
		{
			players.push_back(p);
			isActualPlayerInPlayers = true;
		}

		system("cls");

		if (!isName)
		{
			cout << "Witaj " << p.getName() << "!";
			cout << "\nMozesz juz zaczac gre!";
			isName = true;
		}

		if (chosen == 0)
		{
			cout << "\nTwoja aktualna pula pieniedzy: " << p.getMoney() << "\n";

			cout << "\n------ MENU ------\n"
				"1 - Blackjack (kurs 1.5)\n"
				"2 - Jednoreki Bandyta (kurs 5.0)\n"
				"3 - Ruletka (kursy: kolor = 2.0, numer = 3.0)\n"
				"4 - Lista TOP 100\n"
				"5 - Zakoncz gre\n";

			cout << "Wybierz opcje (1 - 5): ";
			chosen = choice(1, 5);
		}

		system("cls");

		switch (chosen)
		{
			case BJ:
			{
				cout << "---- BLACKJACK ----";
				double bet = playerBet(p.getMoney());
				Blackjack bj(bet);
				bj.play(p);
				break;
			}
			case SM:
			{
				cout << "---- JEDNOREKI BANDYTA ----";
				double bet = playerBet(p.getMoney());
				SlotMachine sm(bet);
				sm.play(p);
				break;
			}
			case R:
			{
				cout << "---- RULETKA ----";
				double bet = playerBet(p.getMoney());
				Roulette r(bet);
				r.play(p);
				break;
			}
			case TOP100:
			{
				cout << "---- TOP 100 NAJWIEKSZYCH WYGRANYCH ----";
				chosen = 0;
				showListTop100(p);
				break;
			}
			case END:
			{
				isOn = false;
				cout << "\nGra zakonczona.\n";
				if (p.getMoney() < 100)
					cout << "Nie masz juz pieniedzy";
				break;
			}
		}
	} 
	while (isOn);
}

// top100
void showListTop100(Player& p)
{
	if (players.size() == 0)
		cout << "\nTa lista jest na razie pusta!";
	else
	{
		// sortowanie i wsywietlenie listy
		if (!isActualPlayerInPlayers && p.getBiggestWin())
		{
			players.push_back(p);
			isActualPlayerInPlayers = true;
		}

		if (isActualPlayerInPlayers && p.getBiggestWin() != 0)
			for (auto& player : players)
				if (ID == player.getId())
				{
					player.setBiggestWin(p.getBiggestWin());
					break;
				}

		sort(players.begin(), players.end(), [](const Player& a, const Player& b)
		{
			return a.getBiggestWin() > b.getBiggestWin();
		});

		if (players.size() > 100)
			players.resize(100);

		cout << "\nLP\tID\tIMIE\t\tWYGRANA\n";
		int i = 1;
		for (const auto& player : players)
		{
			cout << i << ".\t" << player.getId() << "\t" << player.getName() << "\t\t" << player.getBiggestWin() << "\n";
			i++;
		}

		// zapis listy
		ofstream fileO("top100.txt");

		for (const auto& player : players)
			fileO << player.getId() << " " << player.getName() << " " << player.getBiggestWin() << "\n";

		fileO.close();
	}
	cout << "\nKliknij dowolny przycisk aby wrocic do menu...\n";
	_getch();
}

// lista graczy
vector<Player> loadListPlayers()
{
	fstream fileI("top100.txt");
	vector <Player> players;

	int id;
	string name;
	double win;

	if (fileI.peek() != EOF)
		while (fileI >> id >> name >> win)
		{
			Player p(id, name, 0, win);
			players.push_back(p);
		}

	fileI.close();

	return players;
}

// bet
double playerBet(double playerMoney)
{
	cout << "\n\nTwoje saldo: " << playerMoney;
	cout << "\nPodaj stawke za ktora chcesz zagrac (min. 100): ";
	double bet;
	cin >> bet;

	while (!isValidInput(bet) || bet > playerMoney || bet < MIN_VALUE_OF_MONEY)
	{
		cout << "Bledna kwota, sprobuj jeszcze raz: ";
		cin >> bet;
	}

	return bet;
}

// wprowadzenie 1 liczby
int choice(int x, int y)
{
	int choice;
	cin >> choice;

	while (!isValidInput(choice) || choice < x || choice > y)
	{
		cout << "Musisz wybrac liczbe w zakresie od " << x << " do " << y << ": ";
		cin >> choice;
	}
	return choice;
}

//--- walidacja ---//

// 1 liczba int
bool isValidInput(int val)
{
	while (!val)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}

	return true;
}

// 1 liczba double
bool isValidInput(double val)
{
	while (!val)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}

	return true;
}

// 1 slowo min. size znaki
bool isValidInput(string val, int size)
{
	if (val.size() < size) 
		return false;

	for (auto ch : val)
		if (!isalpha(ch))
			return false;	

	return true;
}