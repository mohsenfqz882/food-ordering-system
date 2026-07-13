#ifndef RESTAURANTVIEW_H
#define RESTAURANTVIEW_H

#include "DatabaseManager.h"
#include "Cart.h"

class RestaurantView {
private:
    DatabaseManager* database;
    int restaurantId;
    int userId;
    Cart cart;

public:
    RestaurantView(DatabaseManager* database,
                   int restaurantId,
                   int userId);

    void run();
};

#endif