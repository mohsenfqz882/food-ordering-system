#ifndef FOODITEM_H
#define FOODITEM_H

#include "MenuItem.h"

class FoodItem : public MenuItem {
private:
    int cookingTime;

public:
    FoodItem(int id, std::string name, std::string description,
             double price, bool available, int cookingTime)
        : MenuItem(id, name, description, price, available) {
        this->cookingTime = cookingTime;
    }

    int getCookingTime() {
        return cookingTime;
    }

    void setCookingTime(int cookingTime) {
        this->cookingTime = cookingTime;
    }

    std::string getType() override {
        return "Food";
    }

    void display() override {
        std::cout << "[" << id << "] " << name
                  << " (Food) - " << price << " Toman | "
                  << (available ? "Available" : "Unavailable") << "\n"
                  << "    " << description << "\n"
                  << "    Cooking time: " << cookingTime << " min\n";
    }
};

#endif