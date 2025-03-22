/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>
#include <sstream>
#include "account.h"
#include "transaction.h"

void show_menu() {
    std::cout << "\nChoose from the following options: " << "\n";
    std::cout << "1. Deopsit\n";
    std::cout << "2. Withdraw\n";
    std::cout << "3. View Account Details\n";
    std::cout << "4. Get Transaction History\n";
    std::cout << "5. Change User\n";
    std::cout << "6. Exit and update account file\n";
    std::cout << ">";
}

void process_account(Account& newAccount){
    // Check if a file matching that name exists.
    std::string fileName = newAccount.get_name() + "_transactions.txt";
    std::ifstream accountFile;

    // If the account already exists
    if(access(fileName.c_str(), F_OK) == 0){
        std::cout << "Welcome back, " << newAccount.get_name() << "\n";

        // Open the file and parse it and add the transactions to the account
        accountFile.open(fileName);
        if(accountFile.is_open()){
            std::string line;
            int lines = 0;
            std::cout << "Reading your file...\n";

            while (std::getline(accountFile, line)) {
                if(lines >= 2){
                    // Skip empty line
                    if (line.empty()) {
                        continue;
                    }

                    //  Stop at the balance line
                    std::stringstream ss(line);
                    std::string firstWord;
                    ss >> firstWord;
                    if (firstWord == "BALANCE:") {
                        break;
                    }

                    // Extract the values
                    std::string type;
                    std::string timestamp;
                    std::string amount;
                    type = firstWord;
                    ss >> amount >> timestamp;

                    // Strip off dollar sign from amount string
                    amount = amount.substr(1, amount.size()-1);

                    // If it's a deposit, add deposit, else add withdrawl
                    if (type == "DEPOSIT"){
                        newAccount.add_transaction(timestamp, DEPOSIT, std::stod(amount));
                    } else {
                        newAccount.add_transaction(timestamp, WITHDRAWL, std::stod(amount));
                    }
                }
                lines++;
            }
            accountFile.close();
        } else {
            std::cout << "Error reading account details.\n";
            exit(1);
        }
    } else {
        std::cout << "Welcome, " << newAccount.get_name() << "\n";
    }
}

int main(){
    Account newAccount;
    std::string name;
    double amount = 0;
    bool usingAccount = true;

    clear_screen();
    std::cout << "Enter the account holder's name. " << "\n" << ">";
    std::cin >> name;

    newAccount.set_name(name);
    newAccount.set_balance(amount);

    clear_screen();
    process_account(newAccount);

    while (usingAccount){
        show_menu();
        int choice;
        std::cin >> choice;
        switch(choice) {
            case 1:
                clear_screen();
                std::cout << "Enter the deposit amount: $";
                std::cin >> amount;
                newAccount.make_deposit(amount);
                std::cout << "NEW BALANCE: $" << newAccount.get_balance() << "\n";
                break;
            case 2:
                clear_screen();
                std::cout << "Enter the withdrawl amount: $";
                std::cin >> amount;
                clear_screen();
                newAccount.make_withdrawl(amount);
                std::cout << "NEW BALANCE: $" << newAccount.get_balance() << "\n";
                break;
            case 3:
                clear_screen();
                newAccount.display_details();
                break;
            case 4:
                newAccount.get_history();
                break;
            case 5:
                newAccount.writeout_history();
                usingAccount = false;
                main();
                return 0;
                break;
            case 6:
                newAccount.writeout_history();
                std::cout << "Goodbye." << "\n";
                usingAccount = false;
                break;
            default:
                clear_screen();
                break;
        }
    }
    return 0;
}
