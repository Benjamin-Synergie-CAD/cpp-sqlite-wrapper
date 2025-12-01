#include "Database.h"

int main() {
    // L'objet db est créé, la connexion est ouverte
    const Database db("test.db");

    // 1. Création de table
    bool success = db.execute("CREATE TABLE IF NOT EXISTS Users (ID INTEGER PRIMARY KEY, Name TEXT, Age INT);");

    // 2. Insertion
    //db.execute("INSERT INTO Users (Name, Age) VALUES ('Alice', 30);");
    //db.execute("INSERT INTO Users (Name, Age) VALUES ('Bob', 25);");
    success = db.execute("UPDATE Users SET Name = 'Axel' WHERE Id = 2");

    // 3. Lecture

    const auto data = db.query("SELECT * FROM Users;");
    Database::print_query(data);

    return 0;
    // Ici, le destructeur ~Database() est appelé automatiquement.
    // La base est fermée proprement.
}