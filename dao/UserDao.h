#pragma once

#include <string>
#include <vector>
#include <sqlite3.h>

#include "../DatabaseManager.h"
#include "../User.h"

using namespace std;

class UserDAO {
private:
    DatabaseManager* database;

public:
    UserDAO(DatabaseManager* database);

    bool addUser(const User& user,
                 const string& role = "customer");

    bool usernameExists(const string& username);

    bool login(const string& username,
               const string& password);

    User getUser(const string& username);

    string getRole(const string& username);

    std::vector<User> getAllUsers();

    bool deleteUser(int id);
};