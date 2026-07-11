#include "OrderDAO.h"

OrderDAO::OrderDAO(DatabaseManager* database) {
    this->database = database;
}

bool OrderDAO::addOrder(const Order& order) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "INSERT INTO orders(user_id,restaurant_id,status,total_price)"
            " VALUES(?,?,?,?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, order.userId);
    sqlite3_bind_int(stmt, 2, order.restaurantId);
    sqlite3_bind_text(stmt, 3, order.status.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 4, order.totalPrice);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

std::vector<Order> OrderDAO::getAllOrders() {

    std::vector<Order> orders;

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,user_id,restaurant_id,status,total_price FROM orders;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return orders;

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        Order order;

        order.id = sqlite3_column_int(stmt, 0);
        order.userId = sqlite3_column_int(stmt, 1);
        order.restaurantId = sqlite3_column_int(stmt, 2);
        order.status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        order.totalPrice = sqlite3_column_double(stmt, 4);

        orders.push_back(order);
    }

    sqlite3_finalize(stmt);

    return orders;
}