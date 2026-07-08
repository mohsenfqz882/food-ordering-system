#pragma once

#include <string>
#include <sqlite3.h>

#include "../DatabaseManager.h"
#include "../User.h"

using namespace std;

class UserDAO {
private:
    DatabaseManager* database;

public:
    UserDAO(DatabaseManager* database);

    bool addUser(const User& user);

    bool usernameExists(const string& username);
};