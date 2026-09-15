#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

/**
 * @class Transaction
 * @brief Represents a single financial transaction with full audit trail
 * 
 * Records all transaction details including ID, timestamp, type,
 * amount, involved accounts, balance after transaction, and status.
 */
class Transaction {
public:
    enum TransactionType { DEPOSIT = 1, WITHDRAWAL = 2, TRANSFER = 3 };
    enum TransactionStatus { SUCCESS = 1, FAILED = 2 };

private:
    int transactionID;              ///< Unique transaction identifier
    string dateTime;                ///< Date and time of transaction
    TransactionType type;           ///< Type of transaction
    double amount;                  ///< Transaction amount
    int senderAccountNo;            ///< Source account (0 if deposit)
    int receiverAccountNo;          ///< Destination account (0 if withdrawal)
    double balanceAfterTransaction; ///< Balance after transaction
    TransactionStatus status;       ///< Success or Failed

public:
    // Constructor
    Transaction();
    Transaction(int transID, TransactionType t, double amt, 
                int senderAcc, int receiverAcc, double balanceAfter, TransactionStatus s);

    // Getters
    int getTransactionID() const;
    string getDateTime() const;
    TransactionType getType() const;
    string getTypeStr() const;
    double getAmount() const;
    int getSenderAccountNo() const;
    int getReceiverAccountNo() const;
    double getBalanceAfterTransaction() const;
    TransactionStatus getStatus() const;
    string getStatusStr() const;

    // Display
    void display() const;

    // Static helpers
    static string getCurrentDateTime();
};

#endif // TRANSACTION_H

