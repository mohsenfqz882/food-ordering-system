#include "RestaurantView.h"

#include <iostream>

#include "dao/MenuItemDAO.h"

RestaurantView::RestaurantView(DatabaseManager* database, int restaurantId) {
    this->database = database;
    this->restaurantId = restaurantId;
}

void RestaurantView::run() {

    MenuItemDAO menuItemDAO(database);

    while (true) {

        std::cout << "\n===== Restaurant Menu =====\n";

        auto items = menuItemDAO.getMenuItemsByRestaurant(restaurantId);

        if (items.empty()) {
            std::cout << "No menu items found.\n";
        }
        else {
            for (MenuItem* item : items) {
                item->display();
            }
        }

        std::cout << "\n0. Back\n";
        std::cout << "Select item id (ordering will be added later): ";

        int choice;
        std::cin >> choice;

        for (MenuItem* item : items)
            delete item;

        if (choice == 0)
            break;

        std::cout << "Ordering section will be implemented later.\n";
    }
}