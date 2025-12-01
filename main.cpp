#include <iostream>
#include "Database.h"

int main() {
    // L'objet db est créé, la connexion est ouverte
    Database db("test.db");

    // 1. Création de table
    db.execute("CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY, Name TEXT, Age INT);");

    // 2. Insertion
    //db.execute("INSERT INTO Users (Name, Age) VALUES ('Alice', 30);");
    //db.execute("INSERT INTO Users (Name, Age) VALUES ('Bob', 25);");

    // 3. Lecture
    std::cout << "\n--- Liste des utilisateurs ---" << std::endl;
    auto data = db.query("SELECT * FROM Users;");

    for (const auto& row : data) {
        std::cout << "ID: " << row[0]
                  << " | Nom: " << row[1]
                  << " | Age: " << row[2] << std::endl;
    }

    return 0;
    // Ici, le destructeur ~Database() est appelé automatiquement.
    // La base est fermée proprement.
}