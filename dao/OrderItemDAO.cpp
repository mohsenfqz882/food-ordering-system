#include "OrderItemDAO.h"

OrderItemDAO::OrderItemDAO(DatabaseManager* database) {
    this->database = database;
}

bool OrderItemDAO::addOrderItem(const OrderItem& item) {

    sqlite3* db = database->getDatabase();

    const char* sql =
            "INSERT INTO order_items(order_id,item_id,count)"
            " VALUES(?,?,?);";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int(stmt, 1, item.orderId);
    sqlite3_bind_int(stmt, 2, item.itemId);
    sqlite3_bind_int(stmt, 3, item.count);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);

    sqlite3_finalize(stmt);

    return success;
}

std::vector<OrderItem> OrderItemDAO::getOrderItems(int orderId) {

    std::vector<OrderItem> items;

    sqlite3* db = database->getDatabase();

    const char* sql =
            "SELECT id,order_id,item_id,count "
            "FROM order_items WHERE order_id=?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return items;

    sqlite3_bind_int(stmt, 1, orderId);

    while (sqlite3_step(stmt) == SQLITE_ROW) {

        OrderItem item;

        item.id = sqlite3_column_int(stmt, 0);
        item.orderId = sqlite3_column_int(stmt, 1);
        item.itemId = sqlite3_column_int(stmt, 2);
        item.count = sqlite3_column_int(stmt, 3);

        items.push_back(item);
    }

    sqlite3_finalize(stmt);

    return items;
}