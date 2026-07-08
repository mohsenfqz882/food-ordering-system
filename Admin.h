#pragma once

#include "User.h"

class Admin : public User {
public:
    Admin();

    Admin(int id,
          const string& username,
          const string& password);

    ~Admin() override = default;
};

// Default Constructor
inline Admin::Admin()
    : User() {}

// Parameterized Constructor
inline Admin::Admin(int id,
                    const string& username,
                    const string& password)
    : User(id, username, password) {}