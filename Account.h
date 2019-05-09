#pragma once
#include <iostream>
class Account
{
private:
	char* iban;
	int ownerid;
	double amount;
public:
	Account(const char*, int, double);
	Account(const Account&);
	Account& operator=(const Account&);
	virtual ~Account();

	virtual void deposit(double d) = 0
	{
		amount += d;
	}
	virtual bool withdraw(double w) = 0
	{
		if (getBalance() < w) return false;
		else {
			setAmount(getBalance() - w);
			return true;
		}
	}
	virtual void display() const = 0
	{
		std::cout << "IBAN: " << getIban() << ", owner ID: " << getOwner() << ", balance: " << getBalance() << " ";
	}

	double getBalance() const;
	void setAmount(double);
	char* getIban() const;
	int getOwner() const;

};

