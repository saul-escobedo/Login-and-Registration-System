//FIXME: Try implementing  2D array for name and password assossiatied with the name.
// Vector is better ; it can change in size.

#include <fstream>
#include <ios>
#include <iostream>
#include <string>               // Use to_string & getline()
#include <sstream>

void Display();
void Register(std::string name, int password);
void Login(std::string name, int password);

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
  std::string new_Name;
	int new_Password;

    std::ifstream my_file("RegistrationInfo.txt");
    if (!my_file.is_open()) {
        std::cout << "Error opening file.";
    }
    std::string line;

    while (std::getline(my_file, line)) {
        int count = 0; // Count # of loops to know what is name and password.
        std::istringstream iss(line);

        std::string word;
            iss >> name >> password;
            std::cout << "Name: " << name << std::endl;
            std::cout << "Password: " << password << std::endl;
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
