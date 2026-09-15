#ifndef BANK_H
#define BANK_H

#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>

#include "Customer.h"
#include "Account.h"
#include "Transaction.h"

using namespace std;

/**
 * @class Bank
 * @brief Central controller class that manages all banking operations
 * 
 * Maintains collections of customers, accounts, and transactions.
 * Provides the complete business logic and menu-driven interface
 * for the banking system.
 */
class Bank {
private:
    vector<Customer> customers;             ///< All customers
    vector<Account> accounts;               ///< All accounts
    vector<Transaction> transactions;       ///< All transactions
    int nextCustomerID;                     ///< Auto-increment customer ID counter
    int nextAccountNo;                      ///< Auto-increment account number counter
    int nextTransactionID;                  ///< Auto-increment transaction ID counter

    // Helper methods
    int findCustomerIndex(int customerID) const;
    int findAccountIndex(int accountNo) const;
    bool isCustomerIDTaken(int customerID) const;
    bool isAccountNoTaken(int accountNo) const;
    string getCustomerName(int customerID) const;
    Account* findAccount(int accountNo);
    Customer* findCustomer(int customerID);

    // Validation helpers
    int getValidIntInput(const string& prompt, int minVal, int maxVal);
    double getValidDoubleInput(const string& prompt, double minVal);
    string getNonEmptyStringInput(const string& prompt);
    void waitForEnter();

public:
    // Constructor
    Bank();

    // ===== Customer Management =====
    void addCustomer();
    void updateCustomer();
    void searchCustomer();
    void deleteCustomer();
    void displayAllCustomers();

    // ===== Account Management =====
    void openAccount();
    void displayAccountInfo();
    void checkBalance();
    void closeAccount();
    void searchAccount();
    void displayAllAccounts();

    // ===== Core Banking Operations =====
    void depositMoney();
    void withdrawMoney();
    void transferFunds();

    // ===== Transaction History =====
    void viewTransactionHistory();

    // ===== Main Menu =====
    void run();
};

#endif // BANK_H

