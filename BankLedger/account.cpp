/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#include <iostream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <string>
#include <unistd.h>
#include "account.h"
#include "transaction.h"

static std::string get_timestamp(){
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;

#ifdef _WIN32
    localTime_s(&localTime, &currentTime);
#else
    localTime = *std::localtime(&currentTime);
#endif
    std::ostringstream oss;
    oss << std::put_time(&localTime, "%Y-%m-%d_%H:%M:%S");
    return oss.str();

}

void clear_screen() {
    #ifdef _WIN32
        system("cls");  // Windows
    #else
        system("clear"); // Linux/macOS
    #endif
}

// Constructor
Account::Account() {
    past_deposits = 0;
    past_withdrawls = 0;
}

void Account::display_details() {
    std::cout << "\n     -" << owner_name << "-\n";
    std::cout << "     Current balance: $" << balance << "\n";
    std::cout << "     Past withdrawls: " << past_withdrawls << "\n";
    std::cout << "     Past deposits  : " << past_deposits << "\n\n";
}

void Account::make_withdrawl(double withdrawl_amount) {
    std::cout << "PREVIOUS BALANCE: $" << balance << "\n";
    std::cout << "WITHDRAWING: $" << withdrawl_amount << "\n" << "\n";
    std::string timestamp = get_timestamp();
    add_transaction(timestamp, WITHDRAWL, withdrawl_amount);
}

void Account::make_deposit(double deposit_amount) {
    clear_screen();
    std::cout << "PREVIOUS BALANCE: $" << balance << "\n";
    std::cout << "DEPOSITING: $" << deposit_amount << "\n" << "\n";
    std::string timestamp = get_timestamp();
    add_transaction(timestamp, DEPOSIT, deposit_amount);
}

void Account::set_name(std::string name) {
    owner_name = name;}

void Account::set_balance(double new_balance) {
    balance = new_balance;}

std::string Account::get_name() {
    return owner_name;}

double Account::get_balance() {
    return balance;}

void Account::add_transaction(const std::string timestamp, int transaction_type, double amount) {
    if(transaction_type == DEPOSIT){
        balance += amount;
        past_deposits++;
    } else {
        balance -= amount;
        past_withdrawls++;
    }
    //std::cout << "NEW BALANCE: $" << balance << "\n";
    transactions.emplace_back(timestamp, transaction_type, amount);
}

void Account::get_history() {
    clear_screen();
    std::cout << "\nAccount holder: " << owner_name << "\n";
    std::cout << "Balance: $" << balance << "\n";
    std::cout << "-Transaction History-\n";
    for(auto& transaction : transactions) {
        transaction.show_details();
    }
    std::cout << "\n\n";
}

void Account::writeout_history() {
    std::string fileName = owner_name + "_transactions.txt";
    std::ofstream accountFile;

    // Open in write mode, write header
    accountFile.open(fileName);
    if(accountFile.is_open()) {
        accountFile << "Account holder: " << owner_name << "\n";
        accountFile << "-Transaction History-\n";
        accountFile.close();
    } else {
        std::cout << "Error opening file to write transaction history.\n";
        return;
    }

    for(auto& transaction : transactions) {
        transaction.write_details(owner_name);
    }

    // Write the balance to the customer file
    accountFile.open(fileName, std::ios::app);
    accountFile << "\nBALANCE: $" << balance << "\n";
}
