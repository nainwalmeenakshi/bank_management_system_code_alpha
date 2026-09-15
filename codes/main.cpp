/**
 * @file main.cpp
 * @brief Entry point for the Banking Management System
 * 
 * This file creates an instance of the Bank class and starts
 * the menu-driven banking application.
 * 
 * @author Banking System Project
 * @version 1.0
 */

#include <iostream>
#include "../include/Bank.h"

using namespace std;

/**
 * @brief Main function - Program entry point
 * 
 * Initializes the Bank system and runs the main menu loop.
 * 
 * @return int Returns 0 on successful execution
 */
int main() {
    // Display welcome banner
    cout << "\n\n";
    cout << string(55, '=') << endl;
    cout << "     🏦  WELCOME TO BANKING SYSTEM  🏦" << endl;
    cout << string(55, '=') << endl;
    cout << "   A complete Object-Oriented Banking Solution" << endl;
    cout << string(55, '=') << endl;
    cout << "\nPress Enter to continue...";
    cin.get();

    // Create and run the banking system
    Bank bank;
    bank.run();

    return 0;
}

