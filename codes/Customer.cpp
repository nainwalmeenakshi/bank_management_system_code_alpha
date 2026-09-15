#include "../include/Customer.h"
#include <regex>

// Default Constructor

Customer::Customer() 
    : customerID(0), name(""), mobile(""), email(""), address(""), dateOfBirth("") {
}

// Parameterized Constructor

Customer::Customer(int id, string custName, string mob, string em, string addr, string dob)
    : customerID(id), name(custName), mobile(mob), email(em), address(addr), dateOfBirth(dob) {
}

// Getters

int Customer::getCustomerID() const { return customerID; }
string Customer::getName() const { return name; }
string Customer::getMobile() const { return mobile; }
string Customer::getEmail() const { return email; }
string Customer::getAddress() const { return address; }
string Customer::getDateOfBirth() const { return dateOfBirth; }
vector<int> Customer::getAccountNumbers() const { return accountNumbers; }

// ======================================================================
// Setters
// ======================================================================
void Customer::setName(const string& newName) { name = newName; }
void Customer::setMobile(const string& newMobile) { mobile = newMobile; }
void Customer::setEmail(const string& newEmail) { email = newEmail; }
void Customer::setAddress(const string& newAddress) { address = newAddress; }
void Customer::setDateOfBirth(const string& newDob) { dateOfBirth = newDob; }

// ======================================================================
// Account Association
// ======================================================================
void Customer::addAccount(int accountNo) {
    accountNumbers.push_back(accountNo);
}

void Customer::removeAccount(int accountNo) {
    auto it = find(accountNumbers.begin(), accountNumbers.end(), accountNo);
    if (it != accountNumbers.end()) {
        accountNumbers.erase(it);
    }
}

bool Customer::hasAccount(int accountNo) const {
    return find(accountNumbers.begin(), accountNumbers.end(), accountNo) != accountNumbers.end();
}

// Display Customer Information

void Customer::display() const {
    cout << "\n" << string(50, '=') << endl;
    cout << "           CUSTOMER DETAILS" << endl;
    cout << string(50, '=') << endl;
    cout << left << setw(20) << "Customer ID:" << customerID << endl;
    cout << left << setw(20) << "Name:" << name << endl;
    cout << left << setw(20) << "Mobile:" << mobile << endl;
    cout << left << setw(20) << "Email:" << email << endl;
    cout << left << setw(20) << "Address:" << address << endl;
    cout << left << setw(20) << "Date of Birth:" << dateOfBirth << endl;
    cout << left << setw(20) << "Active Accounts:" << accountNumbers.size() << endl;
    if (!accountNumbers.empty()) {
        cout << left << setw(20) << "Account Nos:";
        for (size_t i = 0; i < accountNumbers.size(); ++i) {
            cout << accountNumbers[i];
            if (i < accountNumbers.size() - 1) cout << ", ";
        }
        cout << endl;
    }
    cout << string(50, '-') << endl;
}

// Validation Helpers

bool Customer::isValidMobile(const string& mob) {
    if (mob.length() < 10 || mob.length() > 15) return false;
    for (char c : mob) {
        if (!isdigit(c) && c != '+' && c != '-') return false;
    }
    return true;
}

bool Customer::isValidEmail(const string& em) {
    // Simple email validation: must contain @ and .
    size_t atPos = em.find('@');
    size_t dotPos = em.find('.');
    return atPos != string::npos && dotPos != string::npos && dotPos > atPos + 1;
}

