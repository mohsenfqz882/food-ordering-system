#include "Cart.h"

void Cart::addItem(int itemId, int count) {

    for (auto& item : items) {

        if (item.itemId == itemId) {
            item.count += count;
            return;
        }
    }

    OrderItem item;

    item.itemId = itemId;
    item.count = count;

    items.push_back(item);
}

void Cart::removeItem(int itemId) {

    for (auto it = items.begin(); it != items.end(); ++it) {

        if (it->itemId == itemId) {

            items.erase(it);
            return;
        }
    }
}

void Cart::changeCount(int itemId, int newCount) {

    for (auto& item : items) {

        if (item.itemId == itemId) {

            if (newCount <= 0)
                removeItem(itemId);
            else
                item.count = newCount;

            return;
        }
    }
}

void Cart::clear() {
    items.clear();
}

bool Cart::empty() const {
    return items.empty();
}

void Cart::display() const {

    if (items.empty()) {

        std::cout << "\nCart is empty.\n";
        return;
    }

    std::cout << "\n===== Cart =====\n";

    for (const auto& item : items) {

        std::cout << "Item ID: "
                  << item.itemId
                  << "   Count: "
                  << item.count
                  << std::endl;
    }
}

const std::vector<OrderItem>& Cart::getItems() const {
    return items;
}