#include <iostream>
#include <vector>
#include "MenuItem.h"
#include "FoodItem.h"
#include "DrinkItem.h"
#include "Customer.h"
#include "User.h"
#include "RestaurantManager.h"
#include "Admin.h"
#include "DatabaseManager.h"

int main() {
    std::vector<MenuItem*> menu;
    menu.push_back(new FoodItem(1, "Kabab Koobideh", "Grilled minced meat with rice", 180000, true, 25));
    menu.push_back(new FoodItem(2, "Joojeh Kabab", "Saffron chicken kebab", 160000, true, 20));
    menu.push_back(new DrinkItem(3, "Doogh", "Local yogurt drink", 25000, true, 300));
    menu.push_back(new DrinkItem(4, "Soda", "Canned soda", 20000, false, 330));

    std::cout << "----- Restaurant Menu -----\n\n";

    for (MenuItem* item : menu) {
        item->display();
        std::cout << "\n";
    }
    for (MenuItem* item : menu) {
        delete item;
    }
    menu.clear();
    DatabaseManager db;
    db.open("food.db");
    db.init();
    std::cout << "\nDatabase ready: food.db\n";

    return 0;
}