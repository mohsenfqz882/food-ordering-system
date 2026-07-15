#include "RestaurantDAO.h"

RestaurantDAO::RestaurantDAO(DatabaseManager* database) {
    this->database = database;
}

bool RestaurantDAO::addRestaurant(const Restaurant& restaurant) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "INSERT INTO restaurants(name,address,phone,description,prep_time,is_active) "
            "VALUES(?,?,?,?,?,?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, restaurant.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, restaurant.address.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, restaurant.phone.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, restaurant.description.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, restaurant.prepTime);
    sqlite3_bind_int(stmt, 6, restaurant.isActive);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

std::vector<Restaurant> RestaurantDAO::getAllRestaurants() {

    std::vector<Restaurant> restaurants;

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,name,address,phone,description,prep_time,is_active "
            "FROM restaurants;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return restaurants;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        Restaurant restaurant;

        restaurant.id = sqlite3_column_int(stmt, 0);
        restaurant.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        restaurant.address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        restaurant.phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        restaurant.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        restaurant.prepTime = sqlite3_column_int(stmt, 5);
        restaurant.isActive = sqlite3_column_int(stmt, 6);

        restaurants.push_back(restaurant);
    }

    sqlite3_finalize(stmt);

    return restaurants;
}

std::vector<Restaurant> RestaurantDAO::getActiveRestaurants() {

    std::vector<Restaurant> restaurants;

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,name,address,phone,description,prep_time,is_active "
            "FROM restaurants WHERE is_active=1;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return restaurants;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        Restaurant restaurant;

        restaurant.id = sqlite3_column_int(stmt, 0);
        restaurant.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        restaurant.address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        restaurant.phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        restaurant.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        restaurant.prepTime = sqlite3_column_int(stmt, 5);
        restaurant.isActive = sqlite3_column_int(stmt, 6);

        restaurants.push_back(restaurant);
    }

    sqlite3_finalize(stmt);

    return restaurants;
}

Restaurant RestaurantDAO::getRestaurantById(int id) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,name,address,phone,description,prep_time,is_active "
            "FROM restaurants WHERE id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return Restaurant();

    sqlite3_bind_int(stmt, 1, id);

    Restaurant restaurant;

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        restaurant.id = sqlite3_column_int(stmt, 0);
        restaurant.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        restaurant.address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        restaurant.phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        restaurant.description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        restaurant.prepTime = sqlite3_column_int(stmt, 5);
        restaurant.isActive = sqlite3_column_int(stmt, 6);
    }

    sqlite3_finalize(stmt);

    return restaurant;
}

bool RestaurantDAO::toggleRestaurantStatus(int id) {

    Restaurant restaurant = getRestaurantById(id);

    sqlite3* db = database->getDatabase();

    const char* sql =
            "UPDATE restaurants SET is_active=? WHERE id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, !restaurant.isActive);
    sqlite3_bind_int(stmt, 2, id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

bool RestaurantDAO::updateRestaurant(const Restaurant& restaurant) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "UPDATE restaurants "
            "SET name=?, address=?, phone=?, description=?, prep_time=?, is_active=? "
            "WHERE id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, restaurant.name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, restaurant.address.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, restaurant.phone.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, restaurant.description.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, restaurant.prepTime);
    sqlite3_bind_int(stmt, 6, restaurant.isActive);
    sqlite3_bind_int(stmt, 7, restaurant.id);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}