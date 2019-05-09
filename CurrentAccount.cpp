#include <iostream>

#include "CurrentAccount.h"



CurrentAccount::CurrentAccount(const char * i, int o, double a) : Account(i, o, a)
{
}

CurrentAccount::CurrentAccount(const CurrentAccount &other) : Account(other)
{

}

CurrentAccount & CurrentAccount::operator=(const CurrentAccount & other)
{
	if (this != &other)
	{
		Account::operator=(other);
	}
	return *this;
}

CurrentAccount::~CurrentAccount()
{
}

void CurrentAccount::deposit(double d)
{
	Account::deposit(d);
}

bool CurrentAccount::withdraw(double w)
{
	return Account::withdraw(w);
}

void CurrentAccount::display() const
{
	std::cout << "Current Account : ";
	Account::display();
	std::cout << std::endl;
}
