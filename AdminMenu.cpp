#include "AdminMenu.h"

#include <iostream>

#include "dao/UserDAO.h"
#include "dao/RestaurantDAO.h"
#include "dao/OrderDAO.h"

AdminMenu::AdminMenu(DatabaseManager* database) {
    this->database = database;
}

void AdminMenu::run() {

    UserDAO userDAO(database);
    RestaurantDAO restaurantDAO(database);
    OrderDAO orderDAO(database);

    while (true) {

        int choice;

        std::cout << "\n===== Admin Menu =====\n";
        std::cout << "1. View Users\n";
        std::cout << "2. Delete User\n";
        std::cout << "3. View Restaurants\n";
        std::cout << "4. Change Restaurant Status\n";
        std::cout << "5. View All Orders\n";
        std::cout << "0. Logout\n";
        std::cout << "Choice: ";

        std::cin >> choice;

        if (choice == 0)
            break;

        switch (choice) {

            case 1: {

                std::vector<User> users = userDAO.getAllUsers();

                if (users.empty()) {

                    std::cout << "No users found.\n";
                    break;
                }

                std::cout << "\n===== Users =====\n";

                for (const User& user : users) {

                    std::cout << "ID: " << user.getId()
                              << " | Username: " << user.getUsername()
                              << std::endl;
                }

                break;
            }

            case 2: {

                std::vector<User> users = userDAO.getAllUsers();

                if (users.empty()) {

                    std::cout << "No users found.\n";
                    break;
                }

                std::cout << "\n===== Users =====\n";

                for (const User& user : users) {

                    std::cout << "ID: " << user.getId()
                              << " | Username: " << user.getUsername()
                              << std::endl;
                }

                int id;

                std::cout << "\nUser ID (0 Back): ";
                std::cin >> id;

                if (id == 0)
                    break;

                if (userDAO.deleteUser(id))
                    std::cout << "User deleted successfully.\n";
                else
                    std::cout << "Delete failed.\n";

                break;
            }

            case 3: {

                std::vector<Restaurant> restaurants =
                        restaurantDAO.getAllRestaurants();

                if (restaurants.empty()) {

                    std::cout << "No restaurants found.\n";
                    break;
                }

                std::cout << "\n===== Restaurants =====\n";

                for (const Restaurant& restaurant : restaurants) {

                    std::cout << "ID: " << restaurant.id
                              << " | " << restaurant.name
                              << " | "
                              << (restaurant.isActive ? "Active" : "Inactive")
                              << std::endl;
                }

                break;
            }

            case 4: {

                std::vector<Restaurant> restaurants =
                        restaurantDAO.getAllRestaurants();

                if (restaurants.empty()) {

                    std::cout << "No restaurants found.\n";
                    break;
                }

                std::cout << "\n===== Restaurants =====\n";

                for (const Restaurant& restaurant : restaurants) {

                    std::cout << "ID: " << restaurant.id
                              << " | " << restaurant.name
                              << " | "
                              << (restaurant.isActive ? "Active" : "Inactive")
                              << std::endl;
                }

                int id;

                std::cout << "\nRestaurant ID (0 Back): ";
                std::cin >> id;

                if (id == 0)
                    break;

                if (restaurantDAO.toggleRestaurantStatus(id))
                    std::cout << "Restaurant status changed successfully.\n";
                else
                    std::cout << "Update failed.\n";

                break;
            }

            case 5: {

                std::vector<Order> orders = orderDAO.getAllOrders();

                if (orders.empty()) {

                    std::cout << "No orders found.\n";
                    break;
                }

                std::cout << "\n===== Orders =====\n";

                for (const Order& order : orders) {

                    std::cout << "Order ID: " << order.id
                              << " | User: " << order.userId
                              << " | Restaurant: " << order.restaurantId
                              << " | Status: " << order.status
                              << " | Total: " << order.totalPrice
                              << std::endl;
                }

                break;
            }

            default:

                std::cout << "Invalid choice.\n";
        }
    }
}