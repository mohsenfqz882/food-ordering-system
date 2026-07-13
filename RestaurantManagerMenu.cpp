#include "RestaurantManagerMenu.h"

#include <iostream>

#include "FoodItem.h"
#include "DrinkItem.h"

#include "dao/MenuItemDAO.h"
#include "dao/RestaurantDAO.h"
#include "dao/OrderDAO.h"

RestaurantManagerMenu::RestaurantManagerMenu(DatabaseManager* database,
                                             int restaurantId) {
    this->database = database;
    this->restaurantId = restaurantId;
}

void RestaurantManagerMenu::run() {

    RestaurantDAO restaurantDAO(database);
    MenuItemDAO menuItemDAO(database);
    OrderDAO orderDAO(database);

    while (true) {

        int choice;

        std::cout << "\n===== Restaurant Manager =====\n";
        std::cout << "1. Restaurant Information\n";
        std::cout << "2. View Orders\n";
        std::cout << "3. Add Menu Item\n";
        std::cout << "4. Edit Menu Item\n";
        std::cout << "5. Remove Menu Item\n";
        std::cout << "6. Change Item Availability\n";
        std::cout << "0. Logout\n";
        std::cout << "Choice: ";

        std::cin >> choice;

        if (choice == 0)
            break;

        switch (choice) {

        case 1: {

            Restaurant restaurant =
                    restaurantDAO.getRestaurantById(restaurantId);

            std::cout << "\n===== Restaurant Information =====\n";
            std::cout << "Name: " << restaurant.name << '\n';
            std::cout << "Address: " << restaurant.address << '\n';
            std::cout << "Phone: " << restaurant.phone << '\n';
            std::cout << "Description: " << restaurant.description << '\n';
            std::cout << "Preparation Time: "
                      << restaurant.prepTime
                      << " min\n";
            std::cout << "Status: "
                      << (restaurant.isActive ? "Active" : "Inactive")
                      << "\n";

            break;
        }

        case 2: {

            auto orders =
                    orderDAO.getOrdersByRestaurant(restaurantId);

            if (orders.empty()) {

                std::cout << "\nNo orders found.\n";
                break;
            }

            std::cout << "\n===== Orders =====\n";

            for (const auto& order : orders) {

                std::cout << "\nOrder ID: "
                          << order.id << '\n';

                std::cout << "Customer ID: "
                          << order.userId << '\n';

                std::cout << "Status: "
                          << order.status << '\n';

                std::cout << "Total Price: "
                          << order.totalPrice
                          << " Toman\n";
            }

            int orderId;

            std::cout << "\nOrder ID (0 Back): ";
            std::cin >> orderId;

            if (orderId == 0)
                break;

            Order order =
                    orderDAO.getOrderById(orderId);

            if (order.id == 0) {

                std::cout << "Invalid Order.\n";
                break;
            }

            std::cout << "\n1. preparing\n";
            std::cout << "2. ready_to_send\n";
            std::cout << "3. delivered\n";
            std::cout << "Choice: ";

            int statusChoice;
            std::cin >> statusChoice;

            std::string status;

            if (statusChoice == 1)
                status = "preparing";
            else if (statusChoice == 2)
                status = "ready_to_send";
            else if (statusChoice == 3)
                status = "delivered";
            else {

                std::cout << "Invalid choice.\n";
                break;
            }

            if (orderDAO.updateOrderStatus(orderId, status))
                std::cout << "Status updated successfully.\n";
            else
                std::cout << "Update failed.\n";

            break;
        }

        case 3: {

            int type;

            std::cout << "\n1. Food\n";
            std::cout << "2. Drink\n";
            std::cout << "Choice: ";

            std::cin >> type;

            std::string name;
            std::string description;

            double price;

            std::cout << "Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Description: ";
            std::getline(std::cin, description);

            std::cout << "Price: ";
            std::cin >> price;
            if (type == 1) {

                int cookingTime;

                std::cout << "Cooking Time (min): ";
                std::cin >> cookingTime;

                FoodItem food(0,
                              name,
                              description,
                              price,
                              true,
                              cookingTime);

                if (menuItemDAO.addMenuItem(restaurantId, &food))
                    std::cout << "Food added successfully.\n";
                else
                    std::cout << "Failed to add food.\n";
            }
            else if (type == 2) {

                int volume;

                std::cout << "Volume (ml): ";
                std::cin >> volume;

                DrinkItem drink(0,
                                name,
                                description,
                                price,
                                true,
                                volume);

                if (menuItemDAO.addMenuItem(restaurantId, &drink))
                    std::cout << "Drink added successfully.\n";
                else
                    std::cout << "Failed to add drink.\n";
            }
            else {

                std::cout << "Invalid choice.\n";
            }

            break;
        }

            case 4:

                std::cout << "Edit menu item section will be implemented.\n";
                break;

            case 5:

                std::cout << "Remove menu item section will be implemented.\n";
                break;

            case 6:

                std::cout << "Change availability section will be implemented.\n";
                break;

            default:

                std::cout << "Invalid choice.\n";
        }
    }
}