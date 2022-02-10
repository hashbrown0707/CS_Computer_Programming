// Assignment10.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <vector>
#include "ICommand.h"

enum State
{
	_CheckBalance = 1,
	_WithDraw = 2,
	_Deposit = 3,
	_Quit = 4
};

using namespace std;
static float remainingMoney = 10000.f;   //500 * $20Bills

User LogIn(vector<User> userList, int const account, int const pin);
ICommand* InputState(int& const state);
int main()
{
#pragma region LogIn

	int accountNum, pin;
	vector<User> userList = { User(12345, 54321, 1000.f, 1200.f), User(98765, 56789, 200.f, 200.f) };

	cout << "Welcome! \n\nPlease enter your account number: ";
	cin >> accountNum;
	cout << "\n\nEnter your PIN: ";
	cin >> pin;

	User currentUser = LogIn(userList, accountNum, pin);

	if (currentUser == User::NullObject)
		return EXIT_FAILURE;

#pragma endregion

#pragma region MainMenu

	ICommand* command;
	int _state;

	while (true)
	{
		cout << "\nMain menu:\n"
			"1 - View my balance\n"
			"2 - Withdraw cash\n"
			"3 - Deposit funds\n"
			"4 - Exit\n\n"
			"Enter a choice : ";
		cin >> _state;

		command = InputState(_state);

		if (command)
			command->Execute(currentUser);
	}

#pragma endregion
}

User LogIn(vector<User> userList, int const account, int const pin)
{
	vector<User>::iterator it = userList.begin();

	for (; it != userList.end(); ++it)
		if (it->GetAccount() == account && it->GetPin() == pin)
			return *it;

	cout << "\nlogin fail\n";
	return User::NullObject;
}

ICommand* InputState(int& const state)
{
	switch (state)
	{
	case _CheckBalance:
		return new CheckBalance();
		break;
	case _WithDraw:
		return new WithDraw();
		break;
	case _Deposit:
		return new Deposit();
		break;
	case _Quit:
		cout << "\nExiting the system...\n\nThank you! Goodbye!";
		exit(EXIT_SUCCESS);
	default:
		return nullptr;
	}
}
