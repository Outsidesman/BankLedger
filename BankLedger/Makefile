#
#   Copyright (c) 2025 - Matt C
#    All rights reserved.
#

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Source files
SRC = main.cpp account.cpp transaction.cpp

# Header files
HEADERS = account.h transaction.h

# Output file
TARGET = BankLedger

# Build
$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)

# Clean
clean:
	rm -rf $(TARGET)