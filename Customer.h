#pragma once

#include "User.h"

class Customer : public User {
public:
    Customer();

    Customer(int id,
             const string& username,
             const string& password);

    ~Customer() override = default;
};

// Default Constructor
inline Customer::Customer()
    : User() {}

// Parameterized Constructor
inline Customer::Customer(int id,
                          const string& username,
                          const string& password)
    : User(id, username, password) {}