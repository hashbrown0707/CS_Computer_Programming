#include <iostream>
#include <fstream>
using namespace std;

struct Account
{
	int accountNumber;    // account number
	int pin;              // personal identification number
	int availableBalance; // funds available for withdrawal
	int totalBalance;     // funds available + funds waiting to clear
};

// retrieve Account object (from Accounts.dat) containing specified accountNumber and pin,
// put this object to currentAccount,
// and put the record number (in Accounts.dat) of this object into recordNumber.
// if this object exists, returns true; otherwise returns false.
bool loadAccount(int accountNumber, int pin, Account& currentAccount, int& recordNumber);

// display the main menu and perform transactions
void performTransactions(Account& currentAccount, int& recordNumber, int& remainingBills);

// perform withdrawal transaction
void withdrawal(Account& currentAccount, int& remainingBills);

// perform deposit transaction
void deposit(Account& currentAccount);

// write currentAccount into the n-th record of Accounts.dat
void saveAccount(Account currentAccount, int n);

const int INITIAL_BILLS = 5; // the number bills loaded each day

int main()
{
	// the number of remaining bills in the cash dispenser
	int remainingBills = INITIAL_BILLS;
	int recordNumber;
	Account currentAccount;

	// welcome and authenticate user; perform transactions
	while (true)
	{
		int accountNumber;
		int pin;

		do {
			cout << "Welcome!\n";
			cout << "\nPlease enter your account number: ";
			cin >> accountNumber;
			cout << "\nEnter your PIN: ";
			cin >> pin; // input PIN
		} while (!loadAccount(accountNumber, pin, currentAccount, recordNumber));

		performTransactions(currentAccount, recordNumber, remainingBills);
		cout << "\nThank you! Goodbye!\n\n";
	}
} // end function main

// retrieve Account object (from Accounts.dat) containing specified accountNumber and pin,
// put this object to currentAccount,
// and put the record number of this object into recordNumber.
// if this object exists, returns true; otherwise returns false.
bool loadAccount(int accountNumber, int pin, Account& currentAccount, int& recordNumber)
{
	ifstream ifs("Accounts.dat", ios::binary);

	if (!ifs.is_open())
	{
		cout << "\nFile was not loaded.\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

	int a;

	while (ifs.good())
	{
		ifs.read((char*)&a, sizeof(int));
		cout << a;
	}
	ifs.clear();

	ifs.seekg(0, ios::end);
	int size = ifs.tellg() / sizeof(Account);
	ifs.seekg(0, ios::beg);

	for (recordNumber = 0; recordNumber < size; ++recordNumber)
	{
		Account temp;
		ifs.read((char*)&temp.accountNumber, sizeof(temp.accountNumber));
		ifs.read((char*)&temp.pin, sizeof(temp.pin));
		ifs.read((char*)&temp.availableBalance, sizeof(temp.availableBalance));
		ifs.read((char*)&temp.totalBalance, sizeof(temp.totalBalance));

		if (temp.accountNumber != accountNumber)
			continue;

		if (temp.pin != pin)
			continue;

		currentAccount = temp;
		ifs.close();
		return true;
	}

	ifs.close();
	cout << "\nInvalid account number or PIN. Please try again.\n\n";
	return false;
} // end function loadAccount

// display the main menu and perform transactions
void performTransactions(Account& currentAccount, int& recordNumber, int& remainingBills)
{
	while (true)
	{
		cout << "\nMain menu: \n"
			<< "1 - View my balance \n"
			<< "2 - Withdraw cash \n"
			<< "3 - Deposit funds \n"
			<< "4 - Exit \n\n"
			<< "Enter a choice: ";

		int option;
		cin >> option;

		switch (option)
		{
		case 1:
			cout << "\nBalance Information: \n"
				<< " - Available balance: $" << currentAccount.availableBalance << "\n"
				<< " - Total balance:     $" << currentAccount.totalBalance << "\n";
			break;
		case 2:
			withdrawal(currentAccount, remainingBills);
			saveAccount(currentAccount, recordNumber);
			break;
		case 3:
			deposit(currentAccount);
			break;
		case 4:
			cout << "\nExiting the system... \n";
			return;
		default:
			cout << "\nYou did not enter a valid selection. Try again.\n";
		}
	}

} // end function performTransactions

// perform withdrawal transaction
void withdrawal(Account& currentAccount, int& remainingBills)
{
	while (true)
	{
		cout << "\nWithdrawal options: \n"
			<< "1 - $20 \n"
			<< "2 - $40 \n"
			<< "3 - $60 \n"
			<< "4 - $100 \n"
			<< "5 - $200 \n"
			<< "6 - Cancel transaction \n\n"
			<< "Choose a withdrawal option (1-6): ";

		int option;
		cin >> option;

		switch (option)
		{
		case 1:
			if (currentAccount.availableBalance < 20)
			{
				cout << "\nInsufficient funds in your account.\n"
					<< "Please choose a smaller amount.\n";
			}
			else if(remainingBills < 1)
			{
				cout << "\nInsufficient cash available in the ATM.\n"
					<< "Please choose a smaller amount.\n";
			}
			else
			{
				cout << "\nPlease take your cash from the cash dispenser.\n";
				currentAccount.availableBalance -= 20;
				currentAccount.totalBalance -= 20;
				remainingBills -= 1;
				return;  //to menu
			}
			break;
		case 2:
			if (currentAccount.availableBalance < 40)
			{
				cout << "\nInsufficient funds in your account.\n"
					<< "Please choose a smaller amount.\n";
			}
			else if (remainingBills < 2)
			{
				cout << "\nInsufficient cash available in the ATM.\n"
					<< "Please choose a smaller amount.\n";
			}
			else
			{
				cout << "\nPlease take your cash from the cash dispenser.\n";
				currentAccount.availableBalance -= 40;
				currentAccount.totalBalance -= 40;
				remainingBills -= 2;
				return;  //to menu
			}
			break;
		case 3:
			if (currentAccount.availableBalance < 60)
			{
				cout << "\nInsufficient funds in your account.\n"
					<< "Please choose a smaller amount.\n";
			}
			else if (remainingBills < 3)
			{
				cout << "\nInsufficient cash available in the ATM.\n"
					<< "Please choose a smaller amount.\n";
			}
			else
			{
				cout << "\nPlease take your cash from the cash dispenser.\n";
				currentAccount.availableBalance -= 60;
				currentAccount.totalBalance -= 60;
				remainingBills -= 3;
				return;  //to menu
			}
			break;
		case 4:
			if (currentAccount.availableBalance < 100)
			{
				cout << "\nInsufficient funds in your account.\n"
					<< "Please choose a smaller amount.\n";
			}
			else if (remainingBills < 5)
			{
				cout << "\nInsufficient cash available in the ATM.\n"
					<< "Please choose a smaller amount.\n";
			}
			else
			{
				cout << "\nPlease take your cash from the cash dispenser.\n";
				currentAccount.availableBalance -= 100;
				currentAccount.totalBalance -= 100;
				remainingBills -= 5;
				return;  //to menu
			}
			break;
		case 5:
			if (currentAccount.availableBalance < 200)
			{
				cout << "\nInsufficient funds in your account.\n"
									<< "Please choose a smaller amount.\n";
			}
			else if (remainingBills < 10)
			{
				cout << "\nInsufficient cash available in the ATM.\n"
					<< "Please choose a smaller amount.\n";
			}
			else
			{
				cout << "\nPlease take your cash from the cash dispenser.\n";
				currentAccount.availableBalance -= 200;
				currentAccount.totalBalance -= 200;
				remainingBills -= 10;
				return;  //to menu
			}
			break;
		case 6:
			cout << "\nCanceling transaction...\n";
			return;
		default:
			cout << "\nInvalid selection. Try again.\n";
		}
	}
} // end function withdrawal

// perform deposit transaction
void deposit(Account& currentAccount)
{
	cout << "\nPlease enter a deposit amount in dollars (or 0 to cancel): ";
	int amount;
	cin >> amount; // receive input of deposit amount

	// check whether user entered a deposit amount or canceled
	if (amount == 0)
		cout << "\nCanceling transaction...\n";
	else // user canceled instead of entering amount
	{
		// request deposit envelope containing specified amount
		cout << "\nPlease insert a deposit envelope containing ";
		cout << "$" << amount;
		cout << " in the deposit slot.\n";

		cout << "\nYour envelope has been received."
			<< "\nNOTE: The money deposited will not be available until we"
			<< "\nverify the amount of any enclosed cash, and any enclosed checks clear.\n";

		// credit account to reflect the deposit
		currentAccount.totalBalance += amount; // add to total balance
	} // end if 
} // end function deposit

void saveAccount(Account currentAccount, int n)   //覆蓋新資料在dat的原始位置上
{
	fstream fs("Accounts.dat", ios::binary | ios::in | ios::out);

	if (!fs.is_open())
	{
		cout << "\nFile was not loaded.\n";
		system("pause");
		exit(EXIT_FAILURE);
	}

	fs.seekp(sizeof(int) * 4 * n + sizeof(int) * 2, ios::beg);
	//cout << fs.tellp() << "\n";
	fs.write((char*)&currentAccount.availableBalance, sizeof(currentAccount.availableBalance));
	fs.write((char*)&currentAccount.totalBalance, sizeof(currentAccount.totalBalance));
	//cout << fs.tellp() << "\n";

	fs.close();
}