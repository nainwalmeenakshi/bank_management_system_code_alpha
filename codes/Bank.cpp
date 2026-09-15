#include "../include/Bank.h"


// Constructor

Bank::Bank() : nextCustomerID(1001), nextAccountNo(10001), nextTransactionID(1) {
}


// Helper: Find Customer Index by ID

int Bank::findCustomerIndex(int customerID) const {
    for (size_t i = 0; i < customers.size(); ++i) {
        if (customers[i].getCustomerID() == customerID) {
            return static_cast<int>(i);
        }
    }
    return -1;
}


// Helper: Find Account Index by Number

int Bank::findAccountIndex(int accountNo) const {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getAccountNo() == accountNo) {
            return static_cast<int>(i);
        }
    }
    return -1;
}


// Helper: Check if Customer ID is Taken

bool Bank::isCustomerIDTaken(int customerID) const {
    return findCustomerIndex(customerID) != -1;
}


// Helper: Check if Account No is Taken

bool Bank::isAccountNoTaken(int accountNo) const {
    return findAccountIndex(accountNo) != -1;
}


// Helper: Get Customer Name by ID

string Bank::getCustomerName(int customerID) const {
    int idx = findCustomerIndex(customerID);
    if (idx != -1) {
        return customers[idx].getName();
    }
    return "Unknown";
}


// Helper: Find Account Pointer

Account* Bank::findAccount(int accountNo) {
    int idx = findAccountIndex(accountNo);
    if (idx != -1) {
        return &accounts[idx];
    }
    return nullptr;
}


// Helper: Find Customer Pointer

Customer* Bank::findCustomer(int customerID) {
    int idx = findCustomerIndex(customerID);
    if (idx != -1) {
        return &customers[idx];
    }
    return nullptr;
}


// Input Validation: Get Integer Input

int Bank::getValidIntInput(const string& prompt, int minVal, int maxVal) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid input! Please enter a number." << endl;
        } else if (value < minVal || value > maxVal) {
            cout << "❌ Input out of range! Please enter between " 
                 << minVal << " and " << maxVal << "." << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}


// Input Validation: Get Double Input

double Bank::getValidDoubleInput(const string& prompt, double minVal) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Invalid input! Please enter a valid number." << endl;
        } else if (value < minVal) {
            cout << "❌ Value must be greater than " << minVal << "!" << endl;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}


// Input Validation: Get Non-Empty String

string Bank::getNonEmptyStringInput(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        // Trim whitespace
        size_t start = value.find_first_not_of(" \t");
        if (start == string::npos) {
            cout << "❌ Input cannot be empty! Please try again." << endl;
            continue;
        }
        value = value.substr(start);
        size_t end = value.find_last_not_of(" \t");
        value = value.substr(0, end + 1);
        if (!value.empty()) {
            return value;
        }
        cout << "❌ Input cannot be empty! Please try again." << endl;
    }
}


// Helper: Wait for Enter Key

void Bank::waitForEnter() {
    cout << "\nPress Enter to continue...";
    cin.get();
}


// 1. Add Customer

void Bank::addCustomer() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           ADD NEW CUSTOMER" << endl;
    cout << string(50, '=') << endl;

    int id = nextCustomerID;
    cout << "Customer ID (Auto-generated): " << id << endl;

    string name = getNonEmptyStringInput("Enter Name: ");
    string mobile;
    while (true) {
        mobile = getNonEmptyStringInput("Enter Mobile (10-15 digits): ");
        if (Customer::isValidMobile(mobile)) break;
        cout << "❌ Invalid mobile number! Please enter 10-15 digits." << endl;
    }

    string email;
    while (true) {
        email = getNonEmptyStringInput("Enter Email: ");
        if (Customer::isValidEmail(email)) break;
        cout << "❌ Invalid email format! Must contain '@' and '.'" << endl;
    }

    string address = getNonEmptyStringInput("Enter Address: ");
    string dob = getNonEmptyStringInput("Enter Date of Birth (DD/MM/YYYY): ");

    customers.push_back(Customer(id, name, mobile, email, address, dob));
    nextCustomerID++;

    cout << "\n✅ Customer added successfully!" << endl;
    cout << "   Customer ID: " << id << endl;
    cout << "   Name: " << name << endl;
    waitForEnter();
}


// 2. Update Customer

void Bank::updateCustomer() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           UPDATE CUSTOMER DETAILS" << endl;
    cout << string(50, '=') << endl;

    int id = getValidIntInput("Enter Customer ID to update: ", 1001, 99999);
    Customer* customer = findCustomer(id);

    if (customer == nullptr) {
        cout << "❌ Customer with ID " << id << " not found!" << endl;
        waitForEnter();
        return;
    }

    cout << "\nUpdating details for: " << customer->getName() << endl;
    cout << "Leave blank to keep current value.\n" << endl;

    string input;
    
    cout << "Current Name: " << customer->getName() << endl;
    cout << "Enter New Name (or press Enter to skip): ";
    getline(cin, input);
    if (!input.empty()) customer->setName(input);

    cout << "Current Mobile: " << customer->getMobile() << endl;
    cout << "Enter New Mobile (or press Enter to skip): ";
    getline(cin, input);
    if (!input.empty() && Customer::isValidMobile(input)) customer->setMobile(input);

    cout << "Current Email: " << customer->getEmail() << endl;
    cout << "Enter New Email (or press Enter to skip): ";
    getline(cin, input);
    if (!input.empty() && Customer::isValidEmail(input)) customer->setEmail(input);

    cout << "Current Address: " << customer->getAddress() << endl;
    cout << "Enter New Address (or press Enter to skip): ";
    getline(cin, input);
    if (!input.empty()) customer->setAddress(input);

    cout << "\n✅ Customer details updated successfully!" << endl;
    customer->display();
    waitForEnter();
}


// 3. Search Customer

void Bank::searchCustomer() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           SEARCH CUSTOMER" << endl;
    cout << string(50, '=') << endl;

    int id = getValidIntInput("Enter Customer ID to search: ", 1001, 99999);
    int idx = findCustomerIndex(id);

    if (idx == -1) {
        cout << "❌ Customer with ID " << id << " not found!" << endl;
    } else {
        customers[idx].display();
    }
    waitForEnter();
}


// 4. Delete Customer

void Bank::deleteCustomer() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           DELETE CUSTOMER" << endl;
    cout << string(50, '=') << endl;

    int id = getValidIntInput("Enter Customer ID to delete: ", 1001, 99999);
    int idx = findCustomerIndex(id);

    if (idx == -1) {
        cout << "❌ Customer with ID " << id << " not found!" << endl;
        waitForEnter();
        return;
    }

    customers[idx].display();
    
    // Check if customer has active accounts
    if (!customers[idx].getAccountNumbers().empty()) {
        cout << "\n⚠️  Customer has " << customers[idx].getAccountNumbers().size() 
             << " active account(s)." << endl;
        cout << "Please close all accounts before deleting customer." << endl;
        waitForEnter();
        return;
    }

    cout << "\nAre you sure you want to delete this customer? (y/n): ";
    char choice;
    cin >> choice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (choice == 'y' || choice == 'Y') {
        customers.erase(customers.begin() + idx);
        cout << "✅ Customer deleted successfully!" << endl;
    } else {
        cout << "❌ Deletion cancelled." << endl;
    }
    waitForEnter();
}


// 5. Display All Customers

void Bank::displayAllCustomers() {
    cout << "\n" << string(60, '=') << endl;
    cout << "           ALL CUSTOMERS" << endl;
    cout << string(60, '=') << endl;

    if (customers.empty()) {
        cout << "\n📭 No customers found in the system." << endl;
        waitForEnter();
        return;
    }

    cout << left << setw(15) << "Customer ID" 
         << setw(25) << "Name" 
         << setw(20) << "Mobile" 
         << "Accounts" << endl;
    cout << string(60, '-') << endl;

    for (const auto& c : customers) {
        cout << left << setw(15) << c.getCustomerID()
             << setw(25) << c.getName()
             << setw(20) << c.getMobile()
             << c.getAccountNumbers().size() << endl;
    }
    cout << string(60, '-') << endl;
    cout << "Total Customers: " << customers.size() << endl;
    waitForEnter();
}


// 6. Open Account

void Bank::openAccount() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           OPEN NEW ACCOUNT" << endl;
    cout << string(50, '=') << endl;

    int custID = getValidIntInput("Enter Customer ID: ", 1001, 99999);
    int custIdx = findCustomerIndex(custID);

    if (custIdx == -1) {
        cout << "❌ Customer with ID " << custID << " not found!" << endl;
        cout << "Please add the customer first." << endl;
        waitForEnter();
        return;
    }

    cout << "\nCustomer: " << customers[custIdx].getName() << endl;

    cout << "\nAccount Types:" << endl;
    cout << "1. Savings" << endl;
    cout << "2. Current" << endl;
    int typeChoice = getValidIntInput("Select Account Type (1-2): ", 1, 2);
    Account::AccountType accType = (typeChoice == 1) ? Account::SAVINGS : Account::CURRENT;

    double initialBalance = getValidDoubleInput("Enter Initial Deposit ($): ", 0.0);

    int accNo = nextAccountNo;
    accounts.push_back(Account(accNo, custID, accType, initialBalance));
    customers[custIdx].addAccount(accNo);
    nextAccountNo++;

    // Record initial deposit as a transaction if balance > 0
    if (initialBalance > 0) {
        transactions.push_back(Transaction(
            nextTransactionID++, Transaction::DEPOSIT, initialBalance,
            0, accNo, initialBalance, Transaction::SUCCESS
        ));
    }

    cout << "\n✅ Account created successfully!" << endl;
    cout << "   Account Number: " << accNo << endl;
    cout << "   Account Type: " << (typeChoice == 1 ? "Savings" : "Current") << endl;
    cout << "   Initial Balance: $" << fixed << setprecision(2) << initialBalance << endl;
    waitForEnter();
}


// 7. Display Account Info

void Bank::displayAccountInfo() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           ACCOUNT INFORMATION" << endl;
    cout << string(50, '=') << endl;

    int accNo = getValidIntInput("Enter Account Number: ", 10001, 999999);
    int idx = findAccountIndex(accNo);

    if (idx == -1) {
        cout << "❌ Account #" << accNo << " not found!" << endl;
        waitForEnter();
        return;
    }

    const Account& acc = accounts[idx];
    int custID = acc.getCustomerID();
    string custName = getCustomerName(custID);

    cout << "\n" << string(50, '=') << endl;
    cout << "           COMPLETE ACCOUNT INFO" << endl;
    cout << string(50, '=') << endl;
    cout << left << setw(22) << "Customer Name:" << custName << endl;
    cout << left << setw(22) << "Customer ID:" << custID << endl;
    cout << left << setw(22) << "Account No:" << acc.getAccountNo() << endl;
    cout << left << setw(22) << "Account Type:" << acc.getAccountTypeStr() << endl;
    cout << left << setw(22) << "Current Balance:" << "$" << fixed << setprecision(2) << acc.getBalance() << endl;
    cout << left << setw(22) << "Status:" << acc.getStatusStr() << endl;
    cout << left << setw(22) << "Date Created:" << acc.getDateCreated() << endl;
    
    // Count total transactions for this account
    int transCount = 0;
    string lastTransDate = "N/A";
    for (const auto& t : transactions) {
        if (t.getSenderAccountNo() == accNo || t.getReceiverAccountNo() == accNo) {
            transCount++;
            lastTransDate = t.getDateTime();
        }
    }
    cout << left << setw(22) << "Total Transactions:" << transCount << endl;
    cout << left << setw(22) << "Last Transaction:" << lastTransDate << endl;
    cout << string(50, '-') << endl;
    waitForEnter();
}


// 8. Check Balance

void Bank::checkBalance() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           CHECK BALANCE" << endl;
    cout << string(50, '=') << endl;

    int accNo = getValidIntInput("Enter Account Number: ", 10001, 999999);
    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "❌ Account #" << accNo << " not found!" << endl;
        waitForEnter();
        return;
    }

    cout << "\n💰 Account #" << accNo << " Balance: $" 
         << fixed << setprecision(2) << acc->getBalance() << endl;
    cout << "   Account Type: " << acc->getAccountTypeStr() << endl;
    cout << "   Status: " << acc->getStatusStr() << endl;
    waitForEnter();
}


// 9. Close Account

void Bank::closeAccount() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           CLOSE ACCOUNT" << endl;
    cout << string(50, '=') << endl;

    int accNo = getValidIntInput("Enter Account Number: ", 10001, 999999);
    int accIdx = findAccountIndex(accNo);

    if (accIdx == -1) {
        cout << "❌ Account #" << accNo << " not found!" << endl;
        waitForEnter();
        return;
    }

    accounts[accIdx].display();
    
    if (accounts[accIdx].closeAccount()) {
        // Remove from customer's account list
        int custID = accounts[accIdx].getCustomerID();
        Customer* cust = findCustomer(custID);
        if (cust != nullptr) {
            cust->removeAccount(accNo);
        }
    }
    waitForEnter();
}


// 10. Search Account

void Bank::searchAccount() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           SEARCH ACCOUNT" << endl;
    cout << string(50, '=') << endl;

    int accNo = getValidIntInput("Enter Account Number: ", 10001, 999999);
    int idx = findAccountIndex(accNo);

    if (idx == -1) {
        cout << "❌ Account #" << accNo << " not found!" << endl;
    } else {
        accounts[idx].display();
    }
    waitForEnter();
}


// 11. Display All Accounts

void Bank::displayAllAccounts() {
    cout << "\n" << string(70, '=') << endl;
    cout << "           ALL ACCOUNTS" << endl;
    cout << string(70, '=') << endl;

    if (accounts.empty()) {
        cout << "\n📭 No accounts found in the system." << endl;
        waitForEnter();
        return;
    }

    cout << left << setw(15) << "Account No"
         << setw(15) << "Customer ID"
         << setw(15) << "Type"
         << setw(15) << "Balance"
         << "Status" << endl;
    cout << string(70, '-') << endl;

    for (const auto& acc : accounts) {
        cout << left << setw(15) << acc.getAccountNo()
             << setw(15) << acc.getCustomerID()
             << setw(15) << acc.getAccountTypeStr()
             << "$" << setw(13) << fixed << setprecision(2) << acc.getBalance()
             << acc.getStatusStr() << endl;
    }
    cout << string(70, '-') << endl;
    cout << "Total Accounts: " << accounts.size() << endl;
    waitForEnter();
}


// 12. Deposit Money

void Bank::depositMoney() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           DEPOSIT MONEY" << endl;
    cout << string(50, '=') << endl;

    int accNo = getValidIntInput("Enter Account Number: ", 10001, 999999);
    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "❌ Account #" << accNo << " not found!" << endl;
        waitForEnter();
        return;
    }

    double amount = getValidDoubleInput("Enter Deposit Amount ($): ", 0.01);
    double balanceBefore = acc->getBalance();

    if (acc->deposit(amount)) {
        // Record transaction
        transactions.push_back(Transaction(
            nextTransactionID++, Transaction::DEPOSIT, amount,
            0, accNo, acc->getBalance(), Transaction::SUCCESS
        ));
    } else {
        // Record failed attempt
        transactions.push_back(Transaction(
            nextTransactionID++, Transaction::DEPOSIT, amount,
            0, accNo, balanceBefore, Transaction::FAILED
        ));
    }
    waitForEnter();
}


// 13. Withdraw Money

void Bank::withdrawMoney() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           WITHDRAW MONEY" << endl;
    cout << string(50, '=') << endl;

    int accNo = getValidIntInput("Enter Account Number: ", 10001, 999999);
    Account* acc = findAccount(accNo);

    if (acc == nullptr) {
        cout << "❌ Account #" << accNo << " not found!" << endl;
        waitForEnter();
        return;
    }

    cout << "Current Balance: $" << fixed << setprecision(2) << acc->getBalance() << endl;
    double amount = getValidDoubleInput("Enter Withdrawal Amount ($): ", 0.01);
    double balanceBefore = acc->getBalance();

    if (acc->withdraw(amount)) {
        // Record transaction
        transactions.push_back(Transaction(
            nextTransactionID++, Transaction::WITHDRAWAL, amount,
            accNo, 0, acc->getBalance(), Transaction::SUCCESS
        ));
    } else {
        // Record failed attempt
        transactions.push_back(Transaction(
            nextTransactionID++, Transaction::WITHDRAWAL, amount,
            accNo, 0, balanceBefore, Transaction::FAILED
        ));
    }
    waitForEnter();
}


// 14. Transfer Funds

void Bank::transferFunds() {
    cout << "\n" << string(50, '=') << endl;
    cout << "           TRANSFER FUNDS" << endl;
    cout << string(50, '=') << endl;

    int senderAccNo = getValidIntInput("Enter Sender Account Number: ", 10001, 999999);
    Account* sender = findAccount(senderAccNo);

    if (sender == nullptr) {
        cout << "❌ Sender Account #" << senderAccNo << " not found!" << endl;
        waitForEnter();
        return;
    }

    if (sender->getStatus() != Account::ACTIVE) {
        cout << "❌ Sender account is not active! Status: " 
             << sender->getStatusStr() << endl;
        waitForEnter();
        return;
    }

    int receiverAccNo = getValidIntInput("Enter Receiver Account Number: ", 10001, 999999);
    
    if (senderAccNo == receiverAccNo) {
        cout << "❌ Sender and receiver accounts cannot be the same!" << endl;
        waitForEnter();
        return;
    }

    Account* receiver = findAccount(receiverAccNo);
    if (receiver == nullptr) {
        cout << "❌ Receiver Account #" << receiverAccNo << " not found!" << endl;
        waitForEnter();
        return;
    }

    if (receiver->getStatus() != Account::ACTIVE) {
        cout << "❌ Receiver account is not active! Status: " 
             << receiver->getStatusStr() << endl;
        waitForEnter();
        return;
    }

    cout << "\nSender: Account #" << senderAccNo 
         << " | Balance: $" << fixed << setprecision(2) << sender->getBalance() << endl;
    cout << "Receiver: Account #" << receiverAccNo 
         << " | Balance: $" << fixed << setprecision(2) << receiver->getBalance() << endl;

    double amount = getValidDoubleInput("\nEnter Transfer Amount ($): ", 0.01);
    double senderBalanceBefore = sender->getBalance();

    if (sender->withdraw(amount)) {
        receiver->deposit(amount);
        
        // Record transfer transaction for sender
        transactions.push_back(Transaction(
            nextTransactionID++, Transaction::TRANSFER, amount,
            senderAccNo, receiverAccNo, sender->getBalance(), Transaction::SUCCESS
        ));

        cout << "\n✅ Transfer completed successfully!" << endl;
        cout << "   Amount: $" << fixed << setprecision(2) << amount << endl;
        cout << "   From: Account #" << senderAccNo << " (" << getCustomerName(sender->getCustomerID()) << ")" << endl;
        cout << "   To: Account #" << receiverAccNo << " (" << getCustomerName(receiver->getCustomerID()) << ")" << endl;
        cout << "   Sender New Balance: $" << sender->getBalance() << endl;
        cout << "   Receiver New Balance: $" << receiver->getBalance() << endl;
    } else {
        // Record failed transfer
        transactions.push_back(Transaction(
            nextTransactionID++, Transaction::TRANSFER, amount,
            senderAccNo, receiverAccNo, senderBalanceBefore, Transaction::FAILED
        ));
    }
    waitForEnter();
}


// 15. View Transaction History

void Bank::viewTransactionHistory() {
    cout << "\n" << string(50, '=') << endl;
    cout << "        TRANSACTION HISTORY" << endl;
    cout << string(50, '=') << endl;

    if (transactions.empty()) {
        cout << "\n📭 No transactions found in the system." << endl;
        waitForEnter();
        return;
    }

    int choice = getValidIntInput(
        "1. View All Transactions\n"
        "2. View Last 10 Transactions\n"
        "3. Search Transaction by ID\n"
        "4. View Transactions by Account\n"
        "Enter choice (1-4): ", 1, 4
    );

    switch (choice) {
        case 1: {
            cout << "\n--- ALL TRANSACTIONS ---" << endl;
            for (const auto& t : transactions) {
                t.display();
            }
            cout << "\nTotal Transactions: " << transactions.size() << endl;
            break;
        }
        case 2: {
            cout << "\n--- LAST 10 TRANSACTIONS ---" << endl;
            int start = max(0, (int)transactions.size() - 10);
            for (int i = start; i < (int)transactions.size(); ++i) {
                transactions[i].display();
            }
            break;
        }
        case 3: {
            int transID = getValidIntInput("Enter Transaction ID: ", 1, 999999);
            bool found = false;
            for (const auto& t : transactions) {
                if (t.getTransactionID() == transID) {
                    t.display();
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "❌ Transaction with ID " << transID << " not found!" << endl;
            }
            break;
        }
        case 4: {
            int accNo = getValidIntInput("Enter Account Number: ", 10001, 999999);
            bool found = false;
            int count = 0;
            for (const auto& t : transactions) {
                if (t.getSenderAccountNo() == accNo || t.getReceiverAccountNo() == accNo) {
                    if (!found) {
                        cout << "\n--- TRANSACTIONS FOR ACCOUNT #" << accNo << " ---" << endl;
                        found = true;
                    }
                    t.display();
                    count++;
                }
            }
            if (!found) {
                cout << "📭 No transactions found for Account #" << accNo << endl;
            } else {
                cout << "\nTotal transactions for Account #" << accNo << ": " << count << endl;
            }
            break;
        }
    }
    waitForEnter();
}


// Main Menu

void Bank::run() {
    int choice;
    
    do {
        cout << "\n" << string(55, '=') << endl;
        cout << "     🏦  BANKING MANAGEMENT SYSTEM  🏦" << endl;
        cout << string(55, '=') << endl;
        
        cout << "\n📋 MAIN MENU" << endl;
        cout << string(40, '-') << endl;
        
        cout << "  [1]  Customer Management" << endl;
        cout << "  [2]  Account Management" << endl;
        cout << "  [3]  💵 Deposit Money" << endl;
        cout << "  [4]  💸 Withdraw Money" << endl;
        cout << "  [5]  🔄 Transfer Funds" << endl;
        cout << "  [6]  📊 View Account Details" << endl;
        cout << "  [7]  📜 View Transaction History" << endl;
        cout << "  [8]  🔍 Search Customer" << endl;
        cout << "  [9]  🔍 Search Account" << endl;
        cout << "  [10] 👥 Display All Customers" << endl;
        cout << "  [11] 💳 Display All Accounts" << endl;
        cout << "  [12] 🚪 Exit" << endl;
        
        cout << string(40, '-') << endl;
        choice = getValidIntInput("Enter your choice (1-12): ", 1, 12);
        
        switch (choice) {
            case 1: {
                int subChoice;
                do {
                    cout << "\n--- CUSTOMER MANAGEMENT ---" << endl;
                    cout << "1. Add Customer" << endl;
                    cout << "2. Update Customer" << endl;
                    cout << "3. Search Customer" << endl;
                    cout << "4. Delete Customer" << endl;
                    cout << "5. Display All Customers" << endl;
                    cout << "6. Back to Main Menu" << endl;
                    subChoice = getValidIntInput("Enter choice (1-6): ", 1, 6);
                    
                    switch (subChoice) {
                        case 1: addCustomer(); break;
                        case 2: updateCustomer(); break;
                        case 3: searchCustomer(); break;
                        case 4: deleteCustomer(); break;
                        case 5: displayAllCustomers(); break;
                        case 6: break;
                    }
                } while (subChoice != 6);
                break;
            }
            case 2: {
                int subChoice;
                do {
                    cout << "\n--- ACCOUNT MANAGEMENT ---" << endl;
                    cout << "1. Open New Account" << endl;
                    cout << "2. Display Account Info" << endl;
                    cout << "3. Check Balance" << endl;
                    cout << "4. Close Account" << endl;
                    cout << "5. Search Account" << endl;
                    cout << "6. Display All Accounts" << endl;
                    cout << "7. Back to Main Menu" << endl;
                    subChoice = getValidIntInput("Enter choice (1-7): ", 1, 7);
                    
                    switch (subChoice) {
                        case 1: openAccount(); break;
                        case 2: displayAccountInfo(); break;
                        case 3: checkBalance(); break;
                        case 4: closeAccount(); break;
                        case 5: searchAccount(); break;
                        case 6: displayAllAccounts(); break;
                        case 7: break;
                    }
                } while (subChoice != 7);
                break;
            }
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: transferFunds(); break;
            case 6: displayAccountInfo(); break;
            case 7: viewTransactionHistory(); break;
            case 8: searchCustomer(); break;
            case 9: searchAccount(); break;
            case 10: displayAllCustomers(); break;
            case 11: displayAllAccounts(); break;
            case 12: {
                cout << "\n" << string(50, '=') << endl;
                cout << "   🙏 Thank you for using the Banking System!" << endl;
                cout << "   👋 Goodbye!" << endl;
                cout << string(50, '=') << endl;
                break;
            }
        }
    } while (choice != 12);
}

