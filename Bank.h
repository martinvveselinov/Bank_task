#pragma once
#include <iostream>
#include <vector>

#include "Customer.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "CurrentAccount.h"
#include "PrivilegeAccount.h"

class Bank
{
private:
	char* name;
	char* adress;
	std::vector <Customer*> customers;
	std::vector <Account*> accounts;
public:
	Bank(const char*, const char*);
	Bank(const Bank&);
	Bank& operator=(const Bank&);
	~Bank();

	char* getName() const;
	char* getAdress() const;
	void addCustomer(int, const char*, const char*);
	void listCustomers() const;
	void deleteCustomer(int);
	void addAccount(const char*, const char*, int, double);
	void deleteAccount(const char*);
	void listAccounts() const;
	void listCustomerAccount(int) const;
	bool transfer(const char*, const char*, double);
	void display() const;

	void menu();
	int getAccSize() const;
};

