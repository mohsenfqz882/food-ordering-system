#include "RestaurantView.h"

#include <iostream>

#include "dao/MenuItemDAO.h"
#include "dao/OrderDAO.h"
#include "dao/OrderItemDAO.h"

RestaurantView::RestaurantView(DatabaseManager* database,
                               int restaurantId,
                               int userId) {
    this->database = database;
    this->restaurantId = restaurantId;
    this->userId = userId;
}

void RestaurantView::run() {

    MenuItemDAO menuItemDAO(database);
    OrderDAO orderDAO(database);
    OrderItemDAO orderItemDAO(database);

    while (true) {

        auto items = menuItemDAO.getMenuItemsByRestaurant(restaurantId);

        std::cout << "\n===== Restaurant Menu =====\n";

        for (MenuItem* item : items)
            item->display();

        std::cout << "\n1. Add Item\n";
        std::cout << "2. View Cart\n";
        std::cout << "3. Change Item Count\n";
        std::cout << "4. Remove Item\n";
        std::cout << "5. Checkout\n";
        std::cout << "0. Back\n";
        std::cout << "Choice: ";

        int choice;
        std::cin >> choice;

        if (choice == 0) {

            for (MenuItem* item : items)
                delete item;

            break;
        }

        if (choice == 1) {

            int itemId;
            int count;

            std::cout << "Item ID: ";
            std::cin >> itemId;

            std::cout << "Count: ";
            std::cin >> count;

            cart.addItem(itemId, count);

            std::cout << "Item added successfully.\n";
        }

        else if (choice == 2) {

            cart.display();
        }

        else if (choice == 3) {

            int itemId;
            int count;

            std::cout << "Item ID: ";
            std::cin >> itemId;

            std::cout << "New Count: ";
            std::cin >> count;

            cart.changeCount(itemId, count);

            std::cout << "Cart updated successfully.\n";
        }

        else if (choice == 4) {

            int itemId;

            std::cout << "Item ID: ";
            std::cin >> itemId;

            cart.removeItem(itemId);

            std::cout << "Item removed successfully.\n";
        }

        else if (choice == 5) {

            if (cart.empty()) {

                std::cout << "Cart is empty.\n";
            }
            else {

                double totalPrice = 0;

                for (const auto& cartItem : cart.getItems()) {

                    MenuItem* item = menuItemDAO.getMenuItemById(cartItem.itemId);

                    if (item != nullptr) {

                        totalPrice += item->getPrice() * cartItem.count;
                        delete item;
                    }
                }

                Order order;

                order.userId = userId;
                order.restaurantId = restaurantId;
                order.status = "preparing";
                order.totalPrice = totalPrice;

                orderDAO.addOrder(order);

                auto orders = orderDAO.getAllOrders();

                int orderId = orders.back().id;

                for (const auto& cartItem : cart.getItems()) {

                    OrderItem orderItem;

                    orderItem.orderId = orderId;
                    orderItem.itemId = cartItem.itemId;
                    orderItem.count = cartItem.count;

                    orderItemDAO.addOrderItem(orderItem);
                }

                cart.clear();

                std::cout << "\nOrder registered successfully.\n";
                std::cout << "Total Price: " << totalPrice << " Toman\n";
            }
        }

        else {

            std::cout << "Invalid choice.\n";
        }

        for (MenuItem* item : items)
            delete item;
    }
}