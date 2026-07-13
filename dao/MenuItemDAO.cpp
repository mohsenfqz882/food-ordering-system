#include "MenuItemDAO.h"
#include "../FoodItem.h"
#include "../DrinkItem.h"

MenuItemDAO::MenuItemDAO(DatabaseManager* database) {
    this->database = database;
}

bool MenuItemDAO::addMenuItem(int restaurantId, MenuItem* item) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "INSERT INTO menu_items(restaurant_id,name,description,price,type,extra,is_available)"
            " VALUES(?,?,?,?,?,?,?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, restaurantId);
    sqlite3_bind_text(stmt, 2, item->getName().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, item->getDescription().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, item->getPrice());

    std::string type = item->getType();
    sqlite3_bind_text(stmt, 5, type.c_str(), -1, SQLITE_TRANSIENT);

    if (type == "Food") {
        FoodItem* food = dynamic_cast<FoodItem*>(item);
        sqlite3_bind_int(stmt, 6, food->getCookingTime());
    } else {
        DrinkItem* drink = dynamic_cast<DrinkItem*>(item);
        sqlite3_bind_int(stmt, 6, drink->getVolume());
    }

    sqlite3_bind_int(stmt, 7, item->isAvailable());

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

std::vector<MenuItem*> MenuItemDAO::getAllMenuItems() {

    std::vector<MenuItem*> items;

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,name,description,price,type,extra,is_available FROM menu_items;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return items;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        double price = sqlite3_column_double(stmt, 3);
        std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        int extra = sqlite3_column_int(stmt, 5);
        bool available = sqlite3_column_int(stmt, 6);

        if (type == "Food")
            items.push_back(new FoodItem(id, name, description, price, available, extra));
        else
            items.push_back(new DrinkItem(id, name, description, price, available, extra));
    }

    sqlite3_finalize(stmt);

    return items;
}

std::vector<MenuItem*> MenuItemDAO::getMenuItemsByRestaurant(int restaurantId) {

    std::vector<MenuItem*> items;

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,name,description,price,type,extra,is_available "
            "FROM menu_items WHERE restaurant_id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return items;

    sqlite3_bind_int(stmt, 1, restaurantId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        int id = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        double price = sqlite3_column_double(stmt, 3);
        std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        int extra = sqlite3_column_int(stmt, 5);
        bool available = sqlite3_column_int(stmt, 6);

        if (type == "Food")
            items.push_back(new FoodItem(id, name, description, price, available, extra));
        else
            items.push_back(new DrinkItem(id, name, description, price, available, extra));
    }

    sqlite3_finalize(stmt);

    return items;
}

MenuItem* MenuItemDAO::getMenuItemById(int id) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,name,description,price,type,extra,is_available "
            "FROM menu_items WHERE id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return nullptr;

    sqlite3_bind_int(stmt, 1, id);

    MenuItem* item = nullptr;

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        int itemId = sqlite3_column_int(stmt, 0);
        std::string name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        double price = sqlite3_column_double(stmt, 3);
        std::string type = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        int extra = sqlite3_column_int(stmt, 5);
        bool available = sqlite3_column_int(stmt, 6);

        if (type == "Food")
            item = new FoodItem(itemId, name, description, price, available, extra);
        else
            item = new DrinkItem(itemId, name, description, price, available, extra);
    }

    sqlite3_finalize(stmt);

    return item;
}