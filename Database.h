//
// Created by constant on 01/12/2025.
//

#ifndef CPPSQLITEPROJECT_DATABASE_H
#define CPPSQLITEPROJECT_DATABASE_H

#include <string>
#include <vector>

#include "sqlite3.h"
using namespace std;


class Database {
    public:
    Database(const string& filename);
    ~Database();

    //CREATE UPDATE INSERT DELETE
    bool execute(const string& sql);

    //SELECT
    vector<vector<string>> query(const string& query);
    private:
    sqlite3* db_ = nullptr;
};


#endif //CPPSQLITEPROJECT_DATABASE_H