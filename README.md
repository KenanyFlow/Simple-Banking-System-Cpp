# Simple Banking System - C++

A console-based banking system built in C++ that provides functionalities to manage client accounts, process transactions, and maintain records using file storage.

## Features  
- **Client Management**  
  - Add new clients  
  - Update client information  
  - Delete clients  
  - Find a specific client  

- **Transaction Handling**  
  - Deposit money  
  - Withdraw money  
  - View total balances  

- **Data Storage**  
  - Uses a text file (`Clients_Data.txt`) to store client information persistently  

## How It Works  
1. The system loads existing client data from a file.  
2. Users can perform banking operations through a **menu-driven interface**.  
3. Transactions update the balance and are saved back to the file.  

## Technologies Used  
- C++ (for logic and implementation)  
- File Handling (to store and retrieve client data)  
- Object-Oriented Programming (OOP) (structs for client records)  
