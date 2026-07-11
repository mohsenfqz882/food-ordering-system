#ifndef RESTAURANTVIEW_H
#define RESTAURANTVIEW_H

#include "DatabaseManager.h"

class RestaurantView {
private:
    DatabaseManager* database;
    int restaurantId;

public:
    RestaurantView(DatabaseManager* database, int restaurantId);

    void run();
};

#endif