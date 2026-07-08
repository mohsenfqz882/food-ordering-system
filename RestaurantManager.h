#pragma once

#include "User.h"

class RestaurantManager : public User {
public:
    RestaurantManager();

    RestaurantManager(int id,
                      const string& username,
                      const string& password);

    ~RestaurantManager() override = default;
};

// Default Constructor
inline RestaurantManager::RestaurantManager()
    : User() {}

// Parameterized Constructor
inline RestaurantManager::RestaurantManager(int id,
                                           const string& username,
                                           const string& password)
    : User(id, username, password) {}