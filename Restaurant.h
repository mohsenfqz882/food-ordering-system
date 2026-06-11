#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include <iostream>

// کلاس رستوران - منطبق بر جدول restaurants
class Restaurant {
public:
    int id;
    std::string name;
    std::string address;
    std::string phone;
    std::string description;
    int prepTime;   // زمان آماده سازی (دقیقه)
    int isActive;   // 0 یا 1

    Restaurant() : id(0), prepTime(0), isActive(1) {}

    Restaurant(int id, const std::string& name, const std::string& address,
               const std::string& phone, const std::string& description,
               int prepTime, int isActive)
        : id(id), name(name), address(address), phone(phone),
          description(description), prepTime(prepTime), isActive(isActive) {}

    // نمایش اطلاعات رستوران
    void display() const {
        std::cout << "[" << id << "] " << name
                  << " | " << address
                  << " | prep: " << prepTime << " min"
                  << (isActive ? " | active" : " | inactive") << "\n";
    }
};

#endif