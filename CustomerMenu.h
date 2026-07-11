#ifndef CUSTOMERMENU_H
#define CUSTOMERMENU_H

#include "DatabaseManager.h"

class CustomerMenu {
private:
    DatabaseManager* database;

public:
    CustomerMenu(DatabaseManager* database);

    void run();
};

#endif