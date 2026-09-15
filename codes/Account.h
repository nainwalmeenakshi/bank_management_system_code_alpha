#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

/**
 * @class Account
 * @brief Represents a bank account with type, balance, and status management
 * 
 * Supports Savings and Current account types. Provides methods for
 * deposits, withdrawals, and account closure with proper validation.
 */
class Account {
public:
    enum AccountType { SAVINGS = 1, CURRENT = 2 };
    enum AccountStatus { ACTIVE = 1, INACTIVE = 2, CLOSED = 3 };

private:
    int accountNo;              ///< Unique account number
    int customerID;             ///< Owner customer ID
    AccountType accountType;    ///< Savings or Current
    double balance;             ///< Current balance
    AccountStatus status;       ///< Active, Inactive, or Closed
    string dateCreated;         ///< Account opening date

public:
    // Constructor
    Account();
    Account(int accNo, int custID, AccountType type, double initialBalance);

    // Getters
    int getAccountNo() const;
    int getCustomerID() const;
    AccountType getAccountType() const;
    string getAccountTypeStr() const;
    double getBalance() const;
    AccountStatus getStatus() const;
    string getStatusStr() const;
    string getDateCreated() const;

    // Setters
    void setAccountType(AccountType type);
    void setStatus(AccountStatus newStatus);

    // Core operations
    bool deposit(double amount);
    bool withdraw(double amount);
    bool closeAccount();

    // Display
    void display() const;

    // Static helpers
    static string getCurrentDate();
    static bool isValidAmount(double amount);
};

#endif // ACCOUNT_H

