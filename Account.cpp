#include "Account.h"

#include <string.h>

Account::Account(const char * i, int o, double a)
{
	ownerid = o;
	amount = a;
	iban = new char[strlen(i) + 1];
	strcpy_s(iban, strlen(i) + 1, i);
}

Account::Account(const Account & other)
{
	int size = strlen(other.getIban()) + 1;
	iban = new char[size];
	strcpy_s(iban, size, other.getIban());
	ownerid = other.getOwner();
	amount = other.getBalance();
}

Account & Account::operator=(const Account &other)
{
	if (this != &other)
	{
		delete[] iban;
		int size = strlen(other.getIban()) + 1;
		iban = new char[size];
		strcpy_s(iban, size, other.getIban());
		ownerid = other.getOwner();
		amount = other.getBalance();
	}
	return *this;
}

Account::~Account()
{
	delete[] iban;
}
	
double Account::getBalance() const
{
	return amount;
}

void Account::setAmount(double d)
{
	amount = d;
}

char * Account::getIban() const
{
	return iban;
}

int Account::getOwner() const
{
	return ownerid;
}
