cmake_minimum_required(VERSION 3.20)
project(FoodOrderingSystem CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SQLite amalgamation
add_library(sqlite3 STATIC external/sqlite3.c)
target_include_directories(sqlite3 PUBLIC external)

add_executable(FoodOrderingSystem
        main.cpp
        MenuItem.h
        FoodItem.h
        DrinkItem.h
        Restaurant.h
        OrderItem.h
        Order.h
        DatabaseManager.h
        User.h
        Customer.h
        RestaurantManager.h
        Admin.h
        dao/UserDao.h
        dao/UserDao.cpp
        membership/MembershipLevel.h
        membership/NormalLevel.h
        membership/SilverLevel.h
        membership/GoldLevel.h
        membership/VipLevel.h)
target_link_libraries(FoodOrderingSystem PRIVATE sqlite3)