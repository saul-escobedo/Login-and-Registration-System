//FIXME: Try implementing  2D array for name and password assossiatied with the name.
// Vector is better ; it can change in size.

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>               // Use to_string & getline()
#include <sstream>

void Display();
void Register(std::string name, int password);
void Login(std::string name, int password);
void clearScreen() { std::cout << "\033[2J";}

int main() {

    Display();

    return 0;
}

void Display() {
    int choice;
    int password;
    std::string name;

    std::cout << "1.  Login\n";
    std::cout << "2.  Register\n";
    std::cout << "Welcome, please enter your choice: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter your password: ";
        std::cin >> password;
        Login(name, password);
        break;
    case 2:
        std::cout << "Enter your name: ";
        std::cin >> name;
        std::cout << "Enter your password: ";
        std::cin >> password;
        Register(name, password);
        break;

    default:
        std::cout << "That is not a valid choice." << std::endl;
    }
}

void Login(std::string name, int password) {
  std::string file_Name;
	int file_Password;

    std::ifstream my_file("RegistrationInfo.txt");
    if (!my_file.is_open()) {
        std::cout << "Error opening file.";
    }
    std::string line;

    while (std::getline(my_file, line)) {
      std::istringstream iss(line);

      std::string word;

      iss >> file_Name >> file_Password;
      size_t commaPos = line.find(',');
      if (commaPos != std::string::npos) {
        file_Name = line.substr(0, commaPos);
      }
      if (name != file_Name || password != file_Password) {
        std::cout << "Error. Incorrect name or password." << std::endl;
      }
      else {
        clearScreen();
        std::cout << "Welcome back " << name << "!" << std::endl;
      }
    }
    my_file.close();
}

void Register(std::string name, int password) {
    std::ofstream my_file("RegistrationInfo.txt", std::ios::app);
    if (!my_file.is_open()) {
        std::cout << "Error opening file" << std::endl;
    }

    my_file << name << ", " << password << std::endl;

    my_file.close();
}
