//Add function to delete user.
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string> // Use to_string & getline()
#include <cstdio> // To use remove and rename in Delete_User() funct.

void Display();
void Register(std::string name, std::string password);
void Login(std::string name, std::string password);
void clearScreen() { std::cout << "\033[2J"; }
void Delete_User(std::string nameToDelete);

int main() {

  Display();

  return 0;
}

void Display() {
  int choice;
  std::string name, password;

  std::cout << "1. Login\n";
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
    std::getline(std::cin, password);
    Login(name, password);
    break;
  case 2:
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your password: ";
    std::getline(std::cin, password);
    Register(name, password);
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

void Login(std::string name, std::string password) {
  std::string file_Name, file_Password;

  std::ifstream my_file("RegistrationInfo.txt");
  if (!my_file.is_open()) {
    std::cout << "Error opening file.";
  }
  std::string line;
  bool is_Authenticated = false;

  while (std::getline(my_file, line)) {
    std::istringstream iss(line);

    size_t commaPos = line.find(',');
    if (commaPos != std::string::npos) {
      file_Name = line.substr(0, commaPos);
      file_Password = line.substr(commaPos + 2);
    }

    if (name == file_Name && password == file_Password) {
      clearScreen();
      std::cout << "Welcome back " << name << "!" << std::endl;
      is_Authenticated = true;
      break;
    }
  }
  if (!is_Authenticated) {
    std::cout << "Error. Incorrect name or password." << std::endl;}

  my_file.close();
}

void Register(std::string name, std::string password) {
  std::ofstream my_file("RegistrationInfo.txt", std::ios::app);
  if (!my_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
  }

  my_file << name << ", " << password << std::endl;

  my_file.close();
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
