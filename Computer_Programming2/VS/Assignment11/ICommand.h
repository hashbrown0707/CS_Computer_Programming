#pragma once
#include <iostream>
#include <iomanip>
#include <map>
#include "User.h"

using namespace std;

class ICommand
{
public:
	virtual void Execute(User& user) = 0;
};

class IInputHandler
{
private:
	virtual void HandleInput(User& const user, int input) = 0;
};

class Deposit : public ICommand, private IInputHandler
{
public:
	virtual void Execute(User& user)
	{
		cout << "\nPlease enter a deposit amount in CENTS (or 0 to cancel): ";

		int input;
		cin >> input;

		HandleInput(user, input);

	}

private:
	virtual void HandleInput(User& const user, int input)
	{
		if (input != 0)
		{
			float dollar = (float)input / 100.f;
			cout << "\nPlease insert a deposit envelope containing" << fixed << setprecision(2) << dollar << "in the deposit slot.\n\n"
				"Your envelope has been received.\n"
				"NOTE: The money deposited will not be available until we\n"
				"verify the amount of any enclosed cash, and any enclosed checks clear.\n\n";

			user.SetTotalBalance(user.GetTotalBalance() + dollar);
			remainingMoney += dollar;
		}
	}
};

class WithDraw : public ICommand, private IInputHandler
{
public:
	virtual void Execute(User& user)
	{
		loop = true;

		while (loop)
		{
			cout << "\nWithdrawal options:\n"
				"1 - $20\n"
				"2 - $40\n"
				"3 - $60\n"
				"4 - $100\n"
				"5 - $200\n"
				"6 - Cancel transaction\n\n"
				"Choose a withdrawal option(1 - 6) : ";

			int input;
			cin >> input;

			HandleInput(user, input);
		}
	}

private:
	const map<int, float> moneyDict = { {1, 20.f}, {2, 40.f}, {3, 60.f}, {4, 100.f}, {5, 200.f} };
	bool loop = true;

	virtual void HandleInput(User& const user, int const input)
	{
		map<int, float>::const_iterator it = moneyDict.find(input);

		if (it != moneyDict.cend()) //option avaliable
		{
			if (it->second <= user.GetBalance())
			{
				user.SetBalance(user.GetBalance() - it->second);
				user.SetTotalBalance(user.GetTotalBalance() - it->second);
				remainingMoney -= it->second;
				loop = false;
				cout << "\nPlease take your cash from the cash dispenser.\n";
			}
			else if (remainingMoney < it->second)
			{
				cout << "\nATM doesn't have that much money remains, try tomorrow.\n\n";
			}
			else
				cout << "\nU don't have that much money.\n\n";
		}
		else
			loop = false;
	}
};

class CheckBalance : public ICommand
{
public:
	virtual void Execute(User& user)
	{
		cout << "\nBalance Information: \n"
			"- Available balance : " << fixed << setprecision(2) << user.GetBalance() << "\n"
			"- Total balance : " << user.GetTotalBalance() << "\n\n";
	}
};
