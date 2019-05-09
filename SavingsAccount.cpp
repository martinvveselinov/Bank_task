#include "stdafx.h"
#include <iostream>

#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(double inte, const char* iban, int id, double amount) : Account(iban, id, amount)
{
	interestRate = inte;
}

SavingsAccount::SavingsAccount(const SavingsAccount & other) : Account(other)
{
	interestRate = other.getInterestRate();
}

SavingsAccount & SavingsAccount::operator=(const SavingsAccount & other)
{
	if (this != &other)
	{
		Account::operator=(other);
		interestRate = other.getInterestRate();
	}
	return *this;
}

double SavingsAccount::getInterestRate() const
{
	return interestRate;
}

void SavingsAccount::deposit(double d)
{
	setAmount(getBalance() + d);
}


SavingsAccount::~SavingsAccount()
{
}

bool SavingsAccount::withdraw(double w)
{
	if (getBalance() < w) return false;
	else {
		setAmount(getBalance() - w);
		return true;
	}
}

void SavingsAccount::display() const
{
	std::cout << "Savings Account : ";
	Account::display();
	std::cout << ", interest rate: " <<  getInterestRate() << std::endl;
}

