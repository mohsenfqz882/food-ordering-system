#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <iostream>
#include <string>
#include <sqlite3.h>

class DatabaseManager {
private:
    sqlite3* db;

public:
    DatabaseManager() {
        db = nullptr;
    }

    bool open(const std::string& filename) {
        int rc = sqlite3_open(filename.c_str(), &db);
        if (rc != SQLITE_OK) {
            std::cout << "Error: cannot open database\n";
            return false;
        }
        return true;
    }

    bool execute(const std::string& sql) {
        char* errMsg = nullptr;
        int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);

        if (rc != SQLITE_OK) {
            std::cout << "SQL error: " << errMsg << "\n";
            sqlite3_free(errMsg);
            return false;
        }

        return true;
    }

    void init() {
        execute("CREATE TABLE IF NOT EXISTS users ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "username TEXT, "
                "password TEXT, "
                "role TEXT);");

        execute("CREATE TABLE IF NOT EXISTS restaurants ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "name TEXT, "
                "address TEXT, "
                "phone TEXT, "
                "description TEXT, "
                "prep_time INTEGER, "
                "is_active INTEGER);");

        execute("CREATE TABLE IF NOT EXISTS menu_items ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "restaurant_id INTEGER, "
                "name TEXT, "
                "description TEXT, "
                "price REAL, "
                "type TEXT, "
                "extra INTEGER, "
                "is_available INTEGER);");

        execute("CREATE TABLE IF NOT EXISTS orders ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "user_id INTEGER, "
                "restaurant_id INTEGER, "
                "status TEXT, "
                "total_price REAL);");

        execute("CREATE TABLE IF NOT EXISTS order_items ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                "order_id INTEGER, "
                "item_id INTEGER, "
                "count INTEGER);");
    }

    sqlite3* getDatabase() {
        return db;
    }

    void close() {
        if (db != nullptr) {
            sqlite3_close(db);
            db = nullptr;
        }
    }

    ~DatabaseManager() {
        close();
    }
};

#endif