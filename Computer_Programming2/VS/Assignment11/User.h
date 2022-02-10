#pragma once


class User 
{
private:
	int account;
	int pin;
	float balance;
	float totalBalance;

public:
	User()
		:account(0),
		pin(0),
		balance(0),
		totalBalance(0)
	{
	}

	User(int account, int pin, float balance, float totalBalance)
		:account(account),
		pin(pin),
		balance(balance),
		totalBalance(totalBalance)
	{
	}

	~User()
	{
	}

	int GetAccount() const
	{
		return account;
	}

	int GetPin() const
	{
		return pin;
	}

	float GetBalance() const
	{
		return balance;
	}

	void SetBalance(float const balance)
	{
		this->balance = balance;
	}

	float GetTotalBalance() const
	{
		return totalBalance;
	}

	void SetTotalBalance(float const totalBalance)
	{
		this->totalBalance = totalBalance;
	}

	bool operator==(User& user)
	{
		if (account != user.account)
			return false;

		if (pin != user.pin)
			return false;

		if (balance != user.balance)
			return false;

		if (totalBalance != user.totalBalance)
			return false;

		return true;
	}

	static User NullObject;
};

User User::NullObject;
