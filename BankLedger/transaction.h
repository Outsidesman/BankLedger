/*
    Copyright (c) 2025 - Matt C
    All rights reserved.
*/

#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <string>

#define DEPOSIT     1
#define WITHDRAWL   2

class Transaction {
    public:
        // Constructor
        Transaction(const std::string timestamp, int type, double amount);

        // Show the details of the transaction or write them to a file
        void show_details();
        void write_details(std::string owner_name);

        // Access or modify
        std::string get_timestamp();
        std::string get_amount();

    private:
        std::string transaction_timestamp;
        int transaction_type;
        double transaction_amount;
};


#endif // TRANSACTION_H_