#include "UserDAO.h"

UserDAO::UserDAO(DatabaseManager* database) {
    this->database = database;
}

bool UserDAO::addUser(const User& user) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "INSERT INTO users(username, password, role) "
            "VALUES(?, ?, ?);";

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
            "SELECT id FROM users WHERE username = ?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    bool exists = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);

    return exists;
}