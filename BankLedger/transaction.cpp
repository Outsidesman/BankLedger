/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#include <iostream>
#include <string>
#include <fstream>
#include "transaction.h"

Transaction::Transaction(const std::string timestamp, int type, double amount)
    : transaction_timestamp(timestamp), transaction_type(type), transaction_amount(amount) {}

void Transaction::show_details() {
    std::string details = "\n";

    if(transaction_type == DEPOSIT) {
        details += "DEPOSIT\t\t$";

    } else {
        details += "WITHDRAWL\t$";
    }
    details += std::to_string(transaction_amount);
    details += "\t\t";
    details += transaction_timestamp;

    std::cout << details;
}

void Transaction::write_details(std::string owner_name) {
    std::string fileName = owner_name + "_transactions.txt";
    std::ofstream accountFile;

    accountFile.open(fileName, std::ios::app);

    if(accountFile.is_open()) {
        std::string details = "";

        if(transaction_type == DEPOSIT) {
            details += "DEPOSIT\t\t$";
    
        } else {
            details += "WITHDRAWL\t$";
        }
        details += std::to_string(transaction_amount);
        details += "\t\t";
        details += transaction_timestamp;
        details += "\n";
    
        accountFile << details;
        accountFile.close();
    } else {
        std::cout << "Error opening file to write transaction history.\n";
    }
}