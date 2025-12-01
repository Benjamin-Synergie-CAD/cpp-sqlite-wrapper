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
    explicit Database(const string& filename);
    ~Database();

    //CREATE UPDATE INSERT DELETE
    [[nodiscard]] bool execute(const string& sql) const;

    //SELECT
    [[nodiscard]] vector<vector<string>> query(const string& query) const;

    static void print_query(const vector<vector<string>>& query);
    private:
    sqlite3* db_ = nullptr;
};


#endif //CPPSQLITEPROJECT_DATABASE_H