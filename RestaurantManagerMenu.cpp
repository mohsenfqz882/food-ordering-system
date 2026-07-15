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

                std::cout << "\n1. Edit Restaurant Information\n";
                std::cout << "0. Back\n";
                std::cout << "Choice: ";

                int editChoice;
                std::cin >> editChoice;

                if (editChoice == 0)
                    break;

                std::cin.ignore();

                std::cout << "New Name: ";
                std::getline(std::cin, restaurant.name);

                std::cout << "New Address: ";
                std::getline(std::cin, restaurant.address);

                std::cout << "New Phone: ";
                std::getline(std::cin, restaurant.phone);

                std::cout << "New Description: ";
                std::getline(std::cin, restaurant.description);

                std::cout << "Preparation Time: ";
                std::cin >> restaurant.prepTime;

                int active;

                std::cout << "Active (1/0): ";
                std::cin >> active;

                restaurant.isActive = active;

                if (restaurantDAO.updateRestaurant(restaurant))
                    std::cout << "Restaurant updated successfully.\n";
                else
                    std::cout << "Update failed.\n";

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

            case 4: {

            auto items = menuItemDAO.getMenuItemsByRestaurant(restaurantId);

            if (items.empty()) {

                std::cout << "No menu items found.\n";
                break;
            }

            std::cout << "\n===== Menu Items =====\n";

            for (MenuItem* item : items)
                item->display();

            int itemId;

            std::cout << "\nItem ID (0 Back): ";
            std::cin >> itemId;

            if (itemId == 0) {

                for (MenuItem* item : items)
                    delete item;

                break;
            }

            MenuItem* item = menuItemDAO.getMenuItemById(itemId);

            if (item == nullptr) {

                std::cout << "Item not found.\n";

                for (MenuItem* i : items)
                    delete i;

                break;
            }

            std::string name;
            std::string description;
            double price;

            std::cin.ignore();

            std::cout << "New Name: ";
            std::getline(std::cin, name);

            std::cout << "New Description: ";
            std::getline(std::cin, description);

            std::cout << "New Price: ";
            std::cin >> price;

            item->setName(name);
            item->setDescription(description);
            item->setPrice(price);

            if (item->getType() == "Food") {

                int time;

                std::cout << "Cooking Time: ";
                std::cin >> time;

                dynamic_cast<FoodItem*>(item)->setCookingTime(time);
            }
            else {

                int volume;

                std::cout << "Volume: ";
                std::cin >> volume;

                dynamic_cast<DrinkItem*>(item)->setVolume(volume);
            }

            if (menuItemDAO.updateMenuItem(item))
                std::cout << "Updated successfully.\n";
            else
                std::cout << "Update failed.\n";

            delete item;

            for (MenuItem* i : items)
                delete i;

            break;
            };

            case 5: {

                auto items = menuItemDAO.getMenuItemsByRestaurant(restaurantId);

                if (items.empty()) {

                    std::cout << "No menu items found.\n";
                    break;
                }

                std::cout << "\n===== Menu Items =====\n";

                for (MenuItem* item : items)
                    item->display();

                int id;

                std::cout << "\nItem ID (0 Back): ";
                std::cin >> id;

                if (id == 0) {

                    for (MenuItem* item : items)
                        delete item;

                    break;
                }

                if (menuItemDAO.deleteMenuItem(id))
                    std::cout << "Item deleted successfully.\n";
                else
                    std::cout << "Delete failed.\n";

                for (MenuItem* item : items)
                    delete item;

                break;
            }

            case 6: {

                auto items = menuItemDAO.getMenuItemsByRestaurant(restaurantId);

                if (items.empty()) {

                    std::cout << "No menu items found.\n";
                    break;
                }

                std::cout << "\n===== Menu Items =====\n";

                for (MenuItem* item : items)
                    item->display();

                int id;

                std::cout << "\nItem ID (0 Back): ";
                std::cin >> id;

                if (id == 0) {

                    for (MenuItem* item : items)
                        delete item;

                    break;
                }

                MenuItem* item = menuItemDAO.getMenuItemById(id);

                if (item == nullptr) {

                    std::cout << "Item not found.\n";

                    for (MenuItem* i : items)
                        delete i;

                    break;
                }

                bool newStatus = !item->isAvailable();

                item->setAvailable(newStatus);

                if (menuItemDAO.updateMenuItem(item))
                    std::cout << "Availability changed successfully.\n";
                else
                    std::cout << "Update failed.\n";

                delete item;

                for (MenuItem* i : items)
                    delete i;

                break;
            }

            default:

                std::cout << "Invalid choice.\n";
        }
    }
}