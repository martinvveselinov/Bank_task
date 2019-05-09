#include <iostream>

#include "PrivilegeAccount.h"

PrivilegeAccount::PrivilegeAccount(double over, const char* ib, int id, double am) : Account(ib, id, am)
{
	overdraft = over;
}
PrivilegeAccount::PrivilegeAccount(const PrivilegeAccount & other) : Account(other)
{
	overdraft = other.getOver();
}
PrivilegeAccount & PrivilegeAccount::operator=(const PrivilegeAccount & other)
{
	if (this != &other)
	{
		Account::operator=(other);
		overdraft = other.getOver();
	}
	return *this;
}
PrivilegeAccount::~PrivilegeAccount()
{
}

double PrivilegeAccount::getOver() const
{
	return overdraft;
}

void PrivilegeAccount::deposit(double d)
{
	Account::deposit(d);
}

bool PrivilegeAccount::withdraw(double w)
{
	if (getBalance() + getOver() < w || w < 0) return false;
	else{
		return Account::withdraw(w);
	}
}

void PrivilegeAccount::display() const
{
	std::cout << "Privilege Account: ";
	Account::display();
	std::cout << ",overdraft allowed: " << getOver() << std::endl;
}
