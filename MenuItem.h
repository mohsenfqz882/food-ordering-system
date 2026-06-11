#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
#include <iostream>

class MenuItem {
protected:
    int id;
    std::string name;
    std::string description;
    double price;
    bool available;

public:
    MenuItem(int id, std::string name, std::string description,
             double price, bool available) {
        this->id = id;
        this->name = name;
        this->description = description;
        this->price = price;
        this->available = available;
    }

    virtual ~MenuItem() {}

    // getters (encapsulation)
    int getId() { return id; }
    std::string getName() { return name; }
    std::string getDescription() { return description; }
    double getPrice() { return price; }
    bool isAvailable() { return available; }

    // item type - polymorphism
    virtual std::string getType() { return "MenuItem"; }

    // display info - polymorphism
    virtual void display() {
        std::cout << "[" << id << "] " << name
                  << " - " << price << " Toman | "
                  << (available ? "Available" : "Unavailable") << "\n"
                  << "    " << description << "\n";
    }
};

#endif