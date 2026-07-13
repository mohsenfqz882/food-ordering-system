#pragma once

#include "../DatabaseManager.h"
#include "../Order.h"

#include <vector>

class OrderDAO {
private:
    DatabaseManager* database;

public:
    OrderDAO(DatabaseManager* database);

    bool addOrder(const Order& order);

    std::vector<Order> getAllOrders();

    std::vector<Order> getOrdersByUser(int userId);
};