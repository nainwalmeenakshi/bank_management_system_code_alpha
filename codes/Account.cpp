#include "../include/Account.h"

// Default Constructor

Account::Account()
    : accountNo(0), customerID(0), accountType(SAVINGS), 
      balance(0.0), status(ACTIVE), dateCreated(getCurrentDate()) {
}


// Parameterized Constructor

Account::Account(int accNo, int custID, AccountType type, double initialBalance)
    : accountNo(accNo), customerID(custID), accountType(type), 
      balance(initialBalance), status(ACTIVE), dateCreated(getCurrentDate()) {
}

// Getters

int Account::getAccountNo() const { return accountNo; }
int Account::getCustomerID() const { return customerID; }
Account::AccountType Account::getAccountType() const { return accountType; }
double Account::getBalance() const { return balance; }
Account::AccountStatus Account::getStatus() const { return status; }
string Account::getDateCreated() const { return dateCreated; }

// Get Account Type as String

string Account::getAccountTypeStr() const {
    switch (accountType) {
        case SAVINGS: return "Savings";
        case CURRENT: return "Current";
        default: return "Unknown";
    }
}

// Get Status as String

string Account::getStatusStr() const {
    switch (status) {
        case ACTIVE: return "Active";
        case INACTIVE: return "Inactive";
        case CLOSED: return "Closed";
        default: return "Unknown";
    }
}

// Setters

void Account::setAccountType(AccountType type) { accountType = type; }
void Account::setStatus(AccountStatus newStatus) { status = newStatus; }

// Deposit Money

bool Account::deposit(double amount) {
    if (!isValidAmount(amount)) {
        cout << "❌ Error: Deposit amount must be positive!" << endl;
        return false;
    }
    if (status != ACTIVE) {
        cout << "❌ Error: Account is not active! Current status: " 
             << getStatusStr() << endl;
        return false;
    }
    balance += amount;
    cout << "✅ Deposit successful! Amount: $" << fixed << setprecision(2) 
         << amount << endl;
    cout << "💰 New Balance: $" << balance << endl;
    return true;
}

// Withdraw Money

bool Account::withdraw(double amount) {
    if (!isValidAmount(amount)) {
        cout << "❌ Error: Withdrawal amount must be positive!" << endl;
        return false;
    }
    if (status != ACTIVE) {
        cout << "❌ Error: Account is not active! Current status: " 
             << getStatusStr() << endl;
        return false;
    }
    if (amount > balance) {
        cout << "❌ Error: Insufficient balance!" << endl;
        cout << "   Available Balance: $" << fixed << setprecision(2) 
             << balance << endl;
        cout << "   Withdrawal Amount: $" << amount << endl;
        return false;
    }
    balance -= amount;
    cout << "✅ Withdrawal successful! Amount: $" << fixed << setprecision(2) 
         << amount << endl;
    cout << "💰 Remaining Balance: $" << balance << endl;
    return true;
}

// Close Account

bool Account::closeAccount() {
    if (status == CLOSED) {
        cout << "❌ Error: Account is already closed!" << endl;
        return false;
    }
    if (balance > 0) {
        cout << "⚠️  Warning: Account has balance of $" << fixed << setprecision(2) 
             << balance << ". Please withdraw before closing." << endl;
        cout << "   Do you still want to close? (y/n): ";
        char choice;
        cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            cout << "❌ Account closure cancelled." << endl;
            return false;
        }
    }


    status = CLOSED;
    balance = 0.0;
    cout << "✅ Account #" << accountNo << " has been closed successfully." << endl;
    return true;
}

// Display Account Details

void Account::display() const {
    cout << "\n" << string(50, '=') << endl;
    cout << "           ACCOUNT DETAILS" << endl;
    cout << string(50, '=') << endl;
    cout << left << setw(22) << "Account No:" << accountNo << endl;
    cout << left << setw(22) << "Customer ID:" << customerID << endl;
    cout << left << setw(22) << "Account Type:" << getAccountTypeStr() << endl;
    cout << left << setw(22) << "Balance:" << "$" << fixed << setprecision(2) 
         << balance << endl;
    cout << left << setw(22) << "Status:" << getStatusStr() << endl;
    cout << left << setw(22) << "Date Created:" << dateCreated << endl;
    cout << string(50, '-') << endl;
}

// Get Current Date as String

string Account::getCurrentDate() {
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%d/%m/%Y", localTime);
    return string(buffer);
}

// Validate Amount

bool Account::isValidAmount(double amount) {
    return amount > 0.0;
}

