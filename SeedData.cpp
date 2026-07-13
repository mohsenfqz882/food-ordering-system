#include "SeedData.h"

#include "dao/RestaurantDAO.h"
#include "dao/MenuItemDAO.h"

#include "Restaurant.h"
#include "FoodItem.h"
#include "DrinkItem.h"

void SeedData::initialize(DatabaseManager* database) {

    RestaurantDAO restaurantDAO(database);

    if (!restaurantDAO.getAllRestaurants().empty())
        return;

    restaurantDAO.addRestaurant(
            Restaurant(0,
                       "Shandiz",
                       "Mashhad",
                       "05138450000",
                       "Traditional food",
                       25,
                       1));

    restaurantDAO.addRestaurant(
            Restaurant(0,
                       "Ashooneh",
                       "Mashhad",
                       "05138770000",
                       "Iranian food",
                       20,
                       1));

    restaurantDAO.addRestaurant(
            Restaurant(0,
                       "Pizza Time",
                       "Mashhad",
                       "05138110000",
                       "Fast food",
                       15,
                       1));

    MenuItemDAO menuItemDAO(database);

    // ---------- Restaurant 1 ----------

    menuItemDAO.addMenuItem(
            1,
            new FoodItem(0,
                         "Jooje Kabab",
                         "Chicken kebab",
                         220000,
                         true,
                         25));

    menuItemDAO.addMenuItem(
            1,
            new FoodItem(0,
                         "Koobide",
                         "Iranian kebab",
                         190000,
                         true,
                         20));

    menuItemDAO.addMenuItem(
            1,
            new DrinkItem(0,
                          "Doogh",
                          "Local drink",
                          35000,
                          true,
                          300));

    // ---------- Restaurant 2 ----------

    menuItemDAO.addMenuItem(
            2,
            new FoodItem(0,
                         "Ghorme Sabzi",
                         "Traditional food",
                         180000,
                         true,
                         15));

    menuItemDAO.addMenuItem(
            2,
            new FoodItem(0,
                         "Gheymeh",
                         "Iranian food",
                         175000,
                         true,
                         15));

    menuItemDAO.addMenuItem(
            2,
            new DrinkItem(0,
                          "Noshabe",
                          "Cold drink",
                          25000,
                          true,
                          330));

    // ---------- Restaurant 3 ----------

    menuItemDAO.addMenuItem(
            3,
            new FoodItem(0,
                         "Pizza Makhsoos",
                         "Italian pizza",
                         280000,
                         true,
                         20));

    menuItemDAO.addMenuItem(
            3,
            new FoodItem(0,
                         "Cheese Burger",
                         "Beef burger",
                         210000,
                         true,
                         15));

    menuItemDAO.addMenuItem(
            3,
            new DrinkItem(0,
                          "Ab Mineral",
                          "Water",
                          12000,
                          true,
                          500));
}