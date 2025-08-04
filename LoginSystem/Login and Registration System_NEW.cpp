// Fix Login Option.
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string> // Use to_string & getline()

void Display();
void Register(std::string name, std::string password);
void Login(std::string name, std::string password);
void clearScreen() { std::cout << "\033[2J"; }

int main() {

  Display();

  return 0;
}

void Display() {
  int choice;
  std::string name, password;

  std::cout << "1.  Login\n";
  std::cout << "2.  Register\n";
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
