#include "CustomerMenu.h"

#include <iostream>

#include "dao/RestaurantDAO.h"
#include "RestaurantView.h"

CustomerMenu::CustomerMenu(DatabaseManager* database) {
    this->database = database;
}

void CustomerMenu::run() {

    RestaurantDAO restaurantDAO(database);

    while (true) {

        int choice;

        std::cout << "\n===== Customer Menu =====\n";
        std::cout << "1. View Restaurants\n";
        std::cout << "2. Order History\n";
        std::cout << "0. Logout\n";
        std::cout << "Choice: ";

        std::cin >> choice;

        if (choice == 0)
            break;

        if (choice == 1) {

            auto restaurants = restaurantDAO.getActiveRestaurants();

            if (restaurants.empty()) {
                std::cout << "No restaurant found.\n";
                continue;
            }

            std::cout << "\n===== Restaurants =====\n";

            for (const auto& restaurant : restaurants)
                restaurant.display();

            int restaurantId;

            std::cout << "\nRestaurant ID (0 Back): ";
            std::cin >> restaurantId;

            if (restaurantId == 0)
                continue;

            RestaurantView restaurantView(database, restaurantId);
            restaurantView.run();
        }

        else if (choice == 2) {

            std::cout << "Order history will be implemented later.\n";
        }

        else {

            std::cout << "Invalid choice.\n";
        }
    }
}