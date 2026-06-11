#ifndef DRINKITEM_H
#define DRINKITEM_H

#include "MenuItem.h"

class DrinkItem : public MenuItem {
private:
    int volume; // volume in milliliters

public:
    DrinkItem(int id, std::string name, std::string description,
              double price, bool available, int volume)
        : MenuItem(id, name, description, price, available) {
        this->volume = volume;
    }

    int getVolume() { return volume; }

    std::string getType() override { return "Drink"; }

    void display() override {
        std::cout << "[" << id << "] " << name
                  << " (Drink) - " << price << " Toman | "
                  << (available ? "Available" : "Unavailable") << "\n"
                  << "    " << description << "\n"
                  << "    Volume: " << volume << " ml\n";
    }
};

#endif