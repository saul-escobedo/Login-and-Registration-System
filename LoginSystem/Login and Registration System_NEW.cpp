//
// Make function to create table
// Make function to add and delete users.
//
// Start thinking about being more intentional in youur project.
// How are you designing it and why?
//
// TODO: Make an README file or add a description in your project repository of
// - What the project is about, what it is.
// - What did i use to make the project
// TODO: Start thinking of how to make the GUI.
//
// I want to continue working on this project. I want it to turn into a web
// application.
//
#include <cstddef>
#include <cstdio>
#include <cstdio> // To use remove and rename in Delete_User() funct.
#include <ios>
#include <iostream>
#include <limits>
#include <sqlite3.h>
#include <string> // Use to_string & getline()

void create_table(sqlite3 *DB);
void Display(sqlite3 *DB);
bool Register(sqlite3 *DB, const std::string name, const std::string& password);
bool Register(sqlite3 *DB, const std::string& name, const std::string& password, const std::string& role);
// void Login(std::string name, std::string password);
void clearScreen() { std::cout << "\033[2J"; }
bool Delete_User(sqlite3 *DB, std::string nameToDelete);
bool is_Admin(sqlite3 *DB, std::string &name); // To check if a user is admin or not

int main() {
  sqlite3 *DB;
  int error_code = sqlite3_open("users.db", &DB);

  if (error_code) {
    std::cerr << "Error opening database: " << sqlite3_errmsg(DB) << std::endl;
    return -1;
  } else {
    std::cout << "Opened database successfully!" << std::endl;
  }

  create_table(DB);

  Display(DB);

  sqlite3_close(DB);

  return 0;
}

void create_table(sqlite3 *DB) {
  int error_code = sqlite3_open("users.db", &DB);

  const char *table = "CREATE TABLE IF NOT EXISTS users ("
                      "name TEXT NOT NULL, "
                      "password INT NOT NULL, "
                      "role TEXT NOT NULL DEFAULT 'user', "
                      "created_at TEXT DEFAULT CURRENT_TIMESTAMP);";

  char *message_error;
  error_code = sqlite3_exec(DB, table, NULL, 0, NULL);
  if (error_code != SQLITE_OK) {
    std::cerr << "Error Creating Table" << sqlite3_errmsg(DB) << std::endl;
  } else {
    std::cout << "Table Created Successfully" << std::endl;
  }
}

void Display(sqlite3 *DB) {
  int choice;
  std::string name, password;

  // std::cout << "1. Login\n";
  std::cout << "2. Register\n";
  std::cout << "3. Delete User\n";
  std::cout << "Welcome, please enter your choice: ";
  std::cin >> choice;

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  switch (choice) {
  case 1:
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your password: ";
    std::cin >> password;
    // Login(name, password);           //Make it so it automatically detects if
    // the account is admin or regular user.
    break;
  case 2:
    // TODO: Make it so you can make a admin account.
    std::cout << "Is it going to be admin(1) or regular user(2)? ";
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);

    if (choice == 1) {
      Register(DB, name, password,"admin");
    } else {
      Register(DB, name, password);
    }
    break;
  case 3:
    std::cout << "Enter name of user you want to delete [<>] : ";
    std::getline(std::cin, name);
    if (Delete_User(DB, name)) {
      std::cout << "User deleted successfully\n";
    } else {
      std::cout << "User not found or delete failed\n";
    }
    break;
  default:
    std::cout << "That is not a valid choice." << std::endl;
  }
}

// void Login(std::string name, std::string password) {
//   std::string file_Name, file_Password;

//   std::ifstream my_file("RegistrationInfo.txt");
//   if (!my_file.is_open()) {
//     std::cout << "Error opening file.";
//   }
//   std::string line;
//   bool is_Authenticated = false;

//   while (std::getline(my_file, line)) {
//     std::istringstream iss(line);

//     size_t commaPos = line.find(',');
//     if (commaPos != std::string::npos) {
//       file_Name = line.substr(0, commaPos);
//       file_Password = line.substr(commaPos + 2);
//     }

//     if (name == file_Name && password == file_Password) {
//       clearScreen();
//       std::cout << "Welcome back " << name << "!" << std::endl;
//       is_Authenticated = true;
//       break;
//     }
//   }
//   if (!is_Authenticated) {
//     std::cout << "Error. Incorrect name or password." << std::endl;}

//   my_file.close();
// }

bool Register(sqlite3 *DB, const std::string name, const std::string& password) {
  sqlite3_stmt *stmt;
  const char *insertSQL = "INSERT INTO users (name, password) VALUES (?, ?);";

  if (sqlite3_prepare_v2(DB, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Prepare failed: " << sqlite3_errmsg(DB) << "\n";
    return false;
  }

  sqlite3_bind_text(stmt, 1, name.c_str(), -1, nullptr);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, nullptr);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    std::cerr << "Insert failed: " << sqlite3_errmsg(DB) << "\n";
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);
  return true;
}

bool Register(sqlite3 *DB, const std::string& name, const std::string& password, const std::string& role) {
  sqlite3_stmt *stmt;
  const char *insertSQL = "INSERT INTO users (name, password, role) VALUES (?, ?, ?);";

  if (sqlite3_prepare_v2(DB, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Prepare failed: " << sqlite3_errmsg(DB) << "\n";
    return false;
  }

  sqlite3_bind_text(stmt, 1, name.c_str(), -1, nullptr);
  sqlite3_bind_text(stmt, 2, password.c_str(), -1, nullptr);
  sqlite3_bind_text(stmt, 3, role.c_str(), -1, SQLITE_TRANSIENT);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    std::cerr << "Insert failed: " << sqlite3_errmsg(DB) << "\n";
    sqlite3_finalize(stmt);
    return false;
  }

  sqlite3_finalize(stmt);
  return true;
}

bool Delete_User(sqlite3 *DB, std::string nameToDelete) {
  const char *sql = "DELETE FROM users WHERE name = ?;";

  sqlite3_stmt *stmt;
  if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
    std::cerr << "Prepare failed: " << sqlite3_errmsg(DB) << '\n';
    return false;
  }

  sqlite3_bind_text(stmt, 1, nameToDelete.c_str(), -1,
                    SQLITE_TRANSIENT); // Bind nameToDelete to the SQL statement

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    std::cerr << "Delete failed: " << sqlite3_errmsg(DB) << '\n';
    sqlite3_finalize(stmt);
    return false;
  }

  int rows_affected = sqlite3_changes(DB);
  sqlite3_finalize(stmt);
  return rows_affected > 0;
}

bool is_Admin(sqlite3 *DB, std::string &name) {
  const char *sql = "SELECT role FROM users WHERE name = ?;";
  sqlite3_stmt *stmt;

  sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr);
  sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);

  bool admin = false;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    std::string role =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
    admin = (role == "admin");
  }

  sqlite3_finalize(stmt);
  return admin;
}
