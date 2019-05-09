#pragma once
#include "Account.h"
class CurrentAccount :
	public Account
{
public:
	CurrentAccount(const char*, int, double);
	CurrentAccount(const CurrentAccount&);
	CurrentAccount& operator=(const CurrentAccount&);
	~CurrentAccount();
	void deposit(double);
	bool withdraw(double);
	void display() const;
};

