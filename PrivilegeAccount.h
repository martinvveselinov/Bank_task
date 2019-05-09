#pragma once
#include "Account.h"
class PrivilegeAccount :
	public Account
{
private:
	double overdraft;
public:
	PrivilegeAccount(double, const char*, int, double);
	PrivilegeAccount(const PrivilegeAccount&);
	PrivilegeAccount& operator=(const PrivilegeAccount&);
	~PrivilegeAccount();

	double getOver() const;
	void deposit(double);
	bool withdraw(double);
	void display() const;
};

