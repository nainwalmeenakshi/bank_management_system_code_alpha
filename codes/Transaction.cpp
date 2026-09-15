#include "../include/Transaction.h"


// Default Constructor

Transaction::Transaction()
    : transactionID(0), type(DEPOSIT), amount(0.0), 
      senderAccountNo(0), receiverAccountNo(0), 
      balanceAfterTransaction(0.0), status(SUCCESS) {
    dateTime = getCurrentDateTime();
}


// Parameterized Constructor

Transaction::Transaction(int transID, TransactionType t, double amt, 
                         int senderAcc, int receiverAcc, 
                         double balanceAfter, TransactionStatus s)
    : transactionID(transID), type(t), amount(amt), 
      senderAccountNo(senderAcc), receiverAccountNo(receiverAcc), 
      balanceAfterTransaction(balanceAfter), status(s) {
    dateTime = getCurrentDateTime();
}


// Getters

int Transaction::getTransactionID() const { return transactionID; }
string Transaction::getDateTime() const { return dateTime; }
Transaction::TransactionType Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
int Transaction::getSenderAccountNo() const { return senderAccountNo; }
int Transaction::getReceiverAccountNo() const { return receiverAccountNo; }
double Transaction::getBalanceAfterTransaction() const { return balanceAfterTransaction; }
Transaction::TransactionStatus Transaction::getStatus() const { return status; }


// Get Transaction Type as String

string Transaction::getTypeStr() const {
    switch (type) {
        case DEPOSIT: return "Deposit";
        case WITHDRAWAL: return "Withdrawal";
        case TRANSFER: return "Transfer";
        default: return "Unknown";
    }
}


// Get Status as String

string Transaction::getStatusStr() const {
    switch (status) {
        case SUCCESS: return "Success";
        case FAILED: return "Failed";
        default: return "Unknown";
    }
}


// Display Transaction Details

void Transaction::display() const {
    cout << "\n" << string(60, '-') << endl;
    cout << left << setw(22) << "Transaction ID:" << transactionID << endl;
    cout << left << setw(22) << "Date & Time:" << dateTime << endl;
    cout << left << setw(22) << "Type:" << getTypeStr() << endl;
    cout << left << setw(22) << "Amount:" << "$" << fixed << setprecision(2) 
         << amount << endl;
    
    if (type == DEPOSIT) {
        cout << left << setw(22) << "Account:" << receiverAccountNo << endl;
    } else if (type == WITHDRAWAL) {
        cout << left << setw(22) << "Account:" << senderAccountNo << endl;
    } else if (type == TRANSFER) {
        cout << left << setw(22) << "From Account:" << senderAccountNo << endl;
        cout << left << setw(22) << "To Account:" << receiverAccountNo << endl;
    }

    cout << left << setw(22) << "Balance After:" << "$" << fixed << setprecision(2) 
         << balanceAfterTransaction << endl;
    cout << left << setw(22) << "Status:" << getStatusStr() << endl;
    cout << string(60, '-') << endl;
}

// Get Current Date and Time as String

string Transaction::getCurrentDateTime() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    char buffer[30];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", localTime);
    return string(buffer);
}

