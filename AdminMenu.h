#ifndef ADMINMENU_H
#define ADMINMENU_H

#include "DatabaseManager.h"

class AdminMenu {
private:
    DatabaseManager* database;

public:
    AdminMenu(DatabaseManager* database);

    void run();
};

#endif