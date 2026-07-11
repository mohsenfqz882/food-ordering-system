#pragma once

#include "../DatabaseManager.h"
#include "../Restaurant.h"

#include <vector>

class RestaurantDAO {
private:
    DatabaseManager* database;

public:
    RestaurantDAO(DatabaseManager* database);

    bool addRestaurant(const Restaurant& restaurant);

    std::vector<Restaurant> getAllRestaurants();

    std::vector<Restaurant> getActiveRestaurants();
};