#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>
#include <iostream>
#include "OrderItem.h"

// کلاس سفارش - منطبق بر جدول orders
class Order {
public:
    int id;
    int userId;
    int restaurantId;
    std::string status;   // preparing / ready_to_send / delivered
    double totalPrice;
    std::vector<OrderItem> items;   // اقلام سفارش

    Order() : id(0), userId(0), restaurantId(0),
              status("preparing"), totalPrice(0.0) {}

    Order(int id, int userId, int restaurantId,
          const std::string& status, double totalPrice)
        : id(id), userId(userId), restaurantId(restaurantId),
          status(status), totalPrice(totalPrice) {}

    // افزودن یک قلم به سفارش
    void addItem(const OrderItem& item) {
        items.push_back(item);
    }

    // نمایش اطلاعات سفارش
    void display() const {
        std::cout << "Order #" << id
                  << " | user: " << userId
                  << " | restaurant: " << restaurantId
                  << " | status: " << status
                  << " | total: " << totalPrice << "\n";
        for (const auto& it : items) {
            std::cout << "   item " << it.itemId
                      << " x" << it.count << "\n";
        }
    }
};

#endif