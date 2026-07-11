#pragma once

#include "../DatabaseManager.h"
#include "../MenuItem.h"

#include <vector>

class MenuItemDAO {
private:
    DatabaseManager* database;

public:
    MenuItemDAO(DatabaseManager* database);

    bool addMenuItem(MenuItem* item);

    std::vector<MenuItem*> getAllMenuItems();

    std::vector<MenuItem*> getMenuItemsByRestaurant(int restaurantId);
};