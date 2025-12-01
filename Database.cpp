//
// Created by constant on 01/12/2025.
//

#include "Database.h"

#include <iostream>
#include <ostream>

Database::Database(const string &filename) {
    int exit = sqlite3_open(filename.c_str(), &db_);
    if (exit != SQLITE_OK) {
        cerr << sqlite3_errmsg(db_) << endl;
    } else {
        cout << "Database successfully opened" << endl;
    }
}

Database::~Database() {
    if (db_) {
        sqlite3_close(db_);
        cout << "Database closed" << endl;
    }
}

bool Database::execute(const string &sql) {
    char* errmsg = nullptr;
    int exit = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errmsg);

    if (exit != SQLITE_OK) {
        cerr << sqlite3_errmsg(db_) << endl;
        sqlite3_free(errmsg);
        return false;
    }
    return true;
}

vector<vector<string>> Database::query(const string &query) {
    vector<vector<string>> results;
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << sqlite3_errmsg(db_) << endl;
        return results;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        vector<string> row;
        int colCount = sqlite3_column_count(stmt);

        for (int i = 0; i < colCount; i++) {
            const char* val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            row.emplace_back(val ? val : "NULL");
        }
        results.push_back(row);
    }
    sqlite3_finalize(stmt);
    return results;
}
