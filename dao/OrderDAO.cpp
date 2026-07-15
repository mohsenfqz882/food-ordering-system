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

std::vector<Order> OrderDAO::getOrdersByUser(int userId) {

    std::vector<Order> orders;

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,user_id,restaurant_id,status,total_price "
            "FROM orders WHERE user_id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return orders;

    sqlite3_bind_int(stmt, 1, userId);

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

std::vector<Order> OrderDAO::getOrdersByRestaurant(int restaurantId) {

    std::vector<Order> orders;

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,user_id,restaurant_id,status,total_price "
            "FROM orders WHERE restaurant_id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return orders;

    sqlite3_bind_int(stmt, 1, restaurantId);

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

Order OrderDAO::getOrderById(int id) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,user_id,restaurant_id,status,total_price "
            "FROM orders WHERE id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return Order();

    sqlite3_bind_int(stmt, 1, id);

    Order order;

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        order.id = sqlite3_column_int(stmt, 0);
        order.userId = sqlite3_column_int(stmt, 1);
        order.restaurantId = sqlite3_column_int(stmt, 2);
        order.status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        order.totalPrice = sqlite3_column_double(stmt, 4);
    }

    sqlite3_finalize(stmt);

    return order;
}

bool OrderDAO::updateOrderStatus(int orderId,
                                 const std::string& status) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "UPDATE orders SET status=? WHERE id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, status.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, orderId);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

int OrderDAO::getOrderCount() {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT COUNT(*) FROM orders;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return 0;

    int count = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW)
        count = sqlite3_column_int(stmt, 0);

    sqlite3_finalize(stmt);

    return count;
}

double OrderDAO::getTotalSales() {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT IFNULL(SUM(total_price),0) FROM orders;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return 0;

    double total = 0;

    if (sqlite3_step(stmt) == SQLITE_ROW)
        total = sqlite3_column_double(stmt, 0);

    sqlite3_finalize(stmt);

    return total;
}