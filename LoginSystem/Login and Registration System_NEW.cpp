//
// Make function to create table
// Make function to add and delete users.
//
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string> // Use to_string & getline()
#include <cstdio> // To use remove and rename in Delete_User() funct.
#include <sqlite3.h>

void create_table(sqlite3* DB);
void Display(sqlite3* DB);
bool Register(sqlite3* DB, const std::string name, int password);
// void Login(std::string name, std::string password);
void clearScreen() { std::cout << "\033[2J"; }
void Delete_User(std::string nameToDelete);



int main() {
    sqlite3* DB;
    int error_code = sqlite3_open("users.db",&DB);

    if (error_code) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(DB) << std::endl;
        return -1;
    } else {
        std::cout << "Opened database successfully!" << std::endl;
    }

    create_table(DB);



  Display(DB);

  return 0;
}

void create_table(sqlite3* DB) {
    int error_code = sqlite3_open("users.db",&DB);

    const char* table = "CREATE TABLE IF NOT EXISTS users ("
                        "name TEXT NOT NULL, "
                        "password INT NOT NULL);";
    char* message_error;
     error_code = sqlite3_exec(DB, table, NULL, 0, NULL);
     if (error_code != SQLITE_OK) {
         std::cerr << "Error Creating Table" << sqlite3_errmsg(DB) << std::endl;
     } else {
         std::cout << "Table Created Successfully" << std::endl;
     }

}

void Display(sqlite3* DB) {
  int choice;
  std::string name;
  int password;

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
    // Login(name, password);
    break;
  case 2:
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your password: ";
    std::cin >> password;
    Register(DB, name, password);
    break;
  case 3:
    std::cout << "Enter name of user you want to delete [<>] : ";
    std::getline(std::cin, name);
    Delete_User(name);
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

bool Register(sqlite3* DB, const std::string name, int password) {
    sqlite3_stmt *stmt;
    const char *insertSQL = "INSERT INTO users (name, password) VALUES (?, ?);";

    if (sqlite3_prepare_v2(DB, insertSQL, -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Prepare failed: " << sqlite3_errmsg(DB) << "\n";
        sqlite3_close(DB);
        return false;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, nullptr);
    sqlite3_bind_int(stmt, 2, password);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        std::cerr << "Insert failed: " << sqlite3_errmsg(DB) << "\n";
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

void Delete_User(std::string nameToDelete) {
  std::ifstream inFile("RegistrationInfo.txt");
  std::ofstream outFile("temp.txt");

  if (!inFile || !outFile) {
    std::cout << "<> Error Opening Files <> \n";
  }
  std::string line;
  bool deleted = false;

  while (getline(inFile, line)) {
    size_t commaPos = line.find(',');
    std::string username = line.substr(0, commaPos);

    if (username != nameToDelete) {
      outFile << line << std::endl;
    } else { deleted = true; }
  }
  inFile.close();
  outFile.close();

  std::remove("RegistrationInfo.txt");
  std::rename("temp.txt", "RegistrationInfo.txt");

  if (deleted) {
    std::cout << "<> User [" << nameToDelete << "] deleted sucessfully <>" << std::endl;
  } else { std::cout << "User not found\n";}
}
