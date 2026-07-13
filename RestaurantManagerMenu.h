#ifndef RESTAURANTMANAGERMENU_H
#define RESTAURANTMANAGERMENU_H

#include "DatabaseManager.h"

class RestaurantManagerMenu {
private:
    DatabaseManager* database;
    int restaurantId;

public:
    RestaurantManagerMenu(DatabaseManager* database, int restaurantId);

    void run();
};

#endif