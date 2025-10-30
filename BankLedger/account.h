/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <vector>
#include <string>
#include "transaction.h"

void clear_screen();

class Account {
    public:
        Account();
    
        void display_details();
        void get_history();

        void make_withdrawl(double withdrawl_amount);
        void make_deposit(double deposit_amount);

        void set_name(std::string name);
        void set_balance(double balance);
        std::string get_name();
        double get_balance();

        void add_transaction(const std::string timestamp, int transaction_type, double amount);

        void writeout_history();

    private:
        std::string owner_name;
        double balance;
        int past_withdrawls;
        int past_deposits;
        std::vector<Transaction> transactions;
};

#endif // ACCOUNT_H_
