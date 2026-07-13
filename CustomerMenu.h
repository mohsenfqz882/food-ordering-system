#ifndef CUSTOMERMENU_H
#define CUSTOMERMENU_H

#include "DatabaseManager.h"

class CustomerMenu {
private:
    DatabaseManager* database;
    int userId;

public:
    CustomerMenu(DatabaseManager* database, int userId);

    void run();
};

#endif