#ifndef SEEDDATA_H
#define SEEDDATA_H

#include "DatabaseManager.h"

class SeedData {
public:
    static void initialize(DatabaseManager* database);
};

#endif