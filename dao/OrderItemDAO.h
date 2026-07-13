#pragma once

#include "../DatabaseManager.h"
#include "../OrderItem.h"

#include <vector>

class OrderItemDAO {
private:
    DatabaseManager* database;

public:
    OrderItemDAO(DatabaseManager* database);

    bool addOrderItem(const OrderItem& item);

    std::vector<OrderItem> getOrderItems(int orderId);
};