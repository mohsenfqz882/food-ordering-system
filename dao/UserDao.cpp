#include "UserDAO.h"

UserDAO::UserDAO(DatabaseManager* database) {
    this->database = database;
}

bool UserDAO::addUser(const User& user) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "INSERT INTO users(username, password, role) VALUES(?, ?, ?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, user.getUsername().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, user.getPassword().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, "customer", -1, SQLITE_STATIC);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

bool UserDAO::usernameExists(const string& username) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id FROM users WHERE username=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);

    return exists;
}

bool UserDAO::login(const string& username, const string& password) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id FROM users WHERE username=? AND password=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);

    return success;
}

User UserDAO::getUser(const string& username) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id, username, password FROM users WHERE username=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return User();

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    User user;

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        user = User(
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))
        );
    }

    sqlite3_finalize(stmt);

    return user;
}

string UserDAO::getRole(const string& username) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT role FROM users WHERE username=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return "";

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    string role = "";

    if (sqlite3_step(stmt) == SQLITE_ROW)
        role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));

    sqlite3_finalize(stmt);

    return role;
}

std::vector<User> UserDAO::getAllUsers() {

    std::vector<User> users;

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id, username, password FROM users;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return users;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        User user(
                sqlite3_column_int(stmt, 0),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)),
                reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2))
        );

        users.push_back(user);
    }

    sqlite3_finalize(stmt);

    return users;
}
bool UserDAO::deleteUser(int id) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "DELETE FROM users WHERE id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}