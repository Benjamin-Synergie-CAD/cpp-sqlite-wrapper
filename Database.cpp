//
// Created by constant on 01/12/2025.
//

#include "Database.h"

#include <iostream>
#include <ostream>
#include <sstream>
#include <fstream>

Database::Database(const string &filename) {
    if (const int exit = sqlite3_open(filename.c_str(), &db_); exit != SQLITE_OK) {
        cerr << sqlite3_errmsg(db_) << endl;
    } else {
        cout << "Database successfully opened" << endl;
    }
}

Database::~Database() {
    if (db_) {
        sqlite3_close(db_);
        cout << "Database successfully closed" << endl;
    }
}

bool Database::execute(const string &sql) const {
    char* errmsg = nullptr;

    if (const int exit = sqlite3_exec(db_, sql.c_str(), nullptr, nullptr, &errmsg); exit != SQLITE_OK) {
        cerr << sqlite3_errmsg(db_) << endl;
        sqlite3_free(errmsg);
        return false;
    }
    return true;
}

bool Database::execute_file(const string &filename) const {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file " << filename << endl;
        return false;
    }
    stringstream buffer;
    buffer << file.rdbuf();
    string sql_content = buffer.str();
    return execute(sql_content);
}

vector<vector<string>> Database::query(const string &query) const {
    vector<vector<string>> results;
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db_, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << sqlite3_errmsg(db_) << endl;
        return results;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        vector<string> row;
        const int colCount = sqlite3_column_count(stmt);

        for (int i = 0; i < colCount; i++) {
            const char* val = reinterpret_cast<const char*>(sqlite3_column_text(stmt, i));
            row.emplace_back(val ? val : "NULL");
        }
        results.push_back(row);
    }
    sqlite3_finalize(stmt);
    return results;
}

void Database::print_query(const vector<vector<string>> &query) {
    for (const auto & i : query) { //boucle sur les lignes
        for (const auto & j : i) { //boucle sur les colones
            cout << j << " | "; // Affiche l'element et un pipe
        }
        cout << endl; //Saut de ligne
    }
}
