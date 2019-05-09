#pragma once
#include "Account.h"
class SavingsAccount :
	public Account
{
private:
	double interestRate;
public:
	SavingsAccount(double, const char*, int, double);
	SavingsAccount(const SavingsAccount&);
	SavingsAccount& operator=(const SavingsAccount&);
	~SavingsAccount();
	double getInterestRate() const;
	void deposit(double);
	bool withdraw(double);
	void display() const;
};

