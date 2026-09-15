#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

/**
 * @class Customer
 * @brief Represents a bank customer with personal details and account associations
 * 
 * This class encapsulates customer information including name, contact details,
 * address, date of birth, and a list of associated account numbers.
 */
class Customer {
private:
    int customerID;                ///< Unique customer identifier
    string name;                   ///< Customer full name
    string mobile;                 ///< Mobile phone number
    string email;                  ///< Email address
    string address;                ///< Residential address
    string dateOfBirth;            ///< Date of birth (DD/MM/YYYY)
    vector<int> accountNumbers;    ///< List of account numbers owned by this customer

public:
    // Constructor
    Customer();
    Customer(int id, string custName, string mob, string em, string addr, string dob);

    // Getters
    int getCustomerID() const;
    string getName() const;
    string getMobile() const;
    string getEmail() const;
    string getAddress() const;
    string getDateOfBirth() const;
    vector<int> getAccountNumbers() const;

    // Setters
    void setName(const string& newName);
    void setMobile(const string& newMobile);
    void setEmail(const string& newEmail);
    void setAddress(const string& newAddress);
    void setDateOfBirth(const string& newDob);

    // Account association
    void addAccount(int accountNo);
    void removeAccount(int accountNo);
    bool hasAccount(int accountNo) const;

    // Display
    void display() const;

    // Static helper
    static bool isValidMobile(const string& mob);
    static bool isValidEmail(const string& em);
};

#endif // CUSTOMER_H

