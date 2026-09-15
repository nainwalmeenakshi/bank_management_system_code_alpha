# 🏦 Banking System - C++ Console Application

A complete object-oriented console-based Banking Management System built in C++ that enables users to create and manage customers, bank accounts, deposits, withdrawals, fund transfers, and transaction history.

## ✨ Features

### 👥 Customer Management
- Add new customers
- Update customer details
- Search customers by ID
- Delete customers
- View all customers

### 💳 Account Management
- Open savings/current accounts
- Display account details
- Check account balance
- Close accounts
- Search accounts by number
- View all accounts

### 💰 Core Banking Operations
- **Deposit Money** - Add funds with validation
- **Withdraw Money** - Withdraw with balance checks
- **Fund Transfer** - Transfer between accounts with full validation

### 📊 Transaction History
- View all transactions
- View last 10 recent transactions
- Search transactions by ID
- View transactions by account
- Records: ID, date/time, type, amount, sender, receiver, balance, status

## 🛠️ Technology

- **Language:** C++
- **Paradigm:** Object-Oriented Programming (OOP)
- **Storage:** In-memory (STL containers)
- **Interface:** Console-based menu-driven

## 📁 Project Structure

```
BANKING/
├── include/          # Header files (.h)
│   ├── Customer.h
│   ├── Account.h
│   ├── Transaction.h
│   └── Bank.h
├── src/              # Source files (.cpp)
│   ├── Customer.cpp
│   ├── Account.cpp
│   ├── Transaction.cpp
│   ├── Bank.cpp
│   └── main.cpp
├── Makefile          # Build automation
└── README.md         # Documentation
```

## 🚀 How to Run

### Prerequisites
- C++ compiler (g++, clang++, etc.)
- `make` (optional, for using Makefile)

### Compilation with Make (Recommended)
```bash
make         # Build the project
make run     # Build and run
make clean   # Remove build files
```

### Manual Compilation
```bash
g++ -std=c++11 -Iinclude src/*.cpp -o banking
```

### Run
```bash
./banking
```

## 🎮 Usage

The system presents a main menu with 12 options:

1. Customer Management
2. Account Management
3. Deposit Money
4. Withdraw Money
5. Transfer Funds
6. View Account Details
7. View Transaction History
8. Search Customer
9. Search Account
10. Display All Customers
11. Display All Accounts
12. Exit

## 🧱 Class Architecture

### Customer Class
- `customerID`, `name`, `mobile`, `email`, `address`, `dob`
- Manages associated accounts

### Account Class
- `accountNo`, `customerID`, `accountType`, `balance`, `status`
- Handles deposits, withdrawals, and closure

### Transaction Class
- `transactionID`, `dateTime`, `type`, `amount`
- Records full transaction details

### Bank Class (Main Controller)
- Manages collections of customers, accounts, transactions
- All business logic and menu-driven interface

## ✅ Validation Rules
- Unique Customer ID & Account Number
- No negative deposits or withdrawals
- Withdrawal cannot exceed balance
- Transfer only between active accounts
- Sender != Receiver for transfers
- Proper input validation everywhere

## 🔮 Future Enhancements
- Password protection & login
- File handling for data persistence
- Interest calculation
- GUI interface
- Database integration

## 📄 License
MIT

