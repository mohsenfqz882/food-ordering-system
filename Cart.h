#ifndef CART_H
#define CART_H

#include <vector>
#include <iostream>

#include "OrderItem.h"

class Cart {
private:
    std::vector<OrderItem> items;

public:
    void addItem(int itemId, int count);

    void removeItem(int itemId);

    void changeCount(int itemId, int newCount);

    void clear();

    bool empty() const;

    void display() const;

    const std::vector<OrderItem>& getItems() const;
};

#endif