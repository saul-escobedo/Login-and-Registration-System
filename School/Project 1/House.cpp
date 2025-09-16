/*
Group #2
Group Members: Saul Escobedo, Kirah Douglas, Luna Espino
Project 1: Classes
*/

#include <ios>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;


class HouseInfo {
  private:
    string style;
    int Num_Of_Bedrooms, Num_Of_Bathrooms, Num_Of_Cars_Garage, Year_Built, Finished_Square_Footage;
    double Price, Tax;
    void static sortByPrice(HouseInfo houses[], int arraySize);



  public:
    HouseInfo( string style = "", int Num_Of_Bedrooms = 0, int Num_Of_Bathrooms = 0, int Num_Of_Cars_Garage = 0, int Year_Built= 0, int Finished_Square_Footage = 0, double Price = 0.0, double Tax = 0.0);
    //setters and getrer
    void print() {
      cout << left << setw(15) << style << setw(10) << Num_Of_Bedrooms << setw(10) << Num_Of_Bathrooms << setw(10) << Num_Of_Cars_Garage << setw(10) << Year_Built << setw(10) << Finished_Square_Footage << setw(10) << Price << setw(10) << Tax << endl;
    }
    void static loadHouse(HouseInfo houses[], int arrayZise, string file);
    void static searchByPriceLinear(HouseInfo houses[], int arraySize, string file, double target);
    void static searchByPriceBinary(HouseInfo houses[], int arraySize, double target);
    void static sortByTaxBubble(HouseInfo houses[], int arraySize);
    void static sortByTaxInsertion(HouseInfo houses[], int arraySize);


    //Setters
    void setStyle(string sty) {style = sty;}
    void setNum_Bedrooms(int bedrooms) {Num_Of_Bedrooms = bedrooms;}
    void setNum_Batrooms(int bathrooms) {Num_Of_Bathrooms = bathrooms;}
    void setNum_Cars(int cars) {Num_Of_Cars_Garage = cars;}
    void setYear(int year) {Year_Built = year;}
    void setSqrFoot(int sqFoot) {Finished_Square_Footage = sqFoot;}
    void setPrice(double price) {Price = price;}
    void setTax(double tax) {Tax = tax;}
    //Getters
    string getStyle() {return style;}
    int getBedrooms() {return Num_Of_Bedrooms;}
    int getBathrooms() {return Num_Of_Bathrooms;}
    int getCars() {return Num_Of_Cars_Garage;}
    int getYear() {return Year_Built;}
    int getFootage() {return Finished_Square_Footage;}
    double getPrice() {return Price;}
    double getTax() {return Tax;}
};

HouseInfo::HouseInfo(
  string style,
  int Num_Of_Bedrooms,
  int Num_Of_Bathrooms,
  int Num_Of_Cars_Garage,
  int Year_Built,
  int Finished_Square_Footage,
  double Price,
  double Tax)
{
  this->style = style;
  this->Num_Of_Bedrooms = Num_Of_Bedrooms;
  this->Num_Of_Bathrooms = Num_Of_Bathrooms;
  this->Num_Of_Cars_Garage = Num_Of_Cars_Garage;
  this->Year_Built = Year_Built;
  this->Finished_Square_Footage = Finished_Square_Footage;
  this->Price = Price;
  this->Tax = Tax;
}

void HouseInfo::loadHouse(HouseInfo *houses, int arrayZise, string file) {
  string line;

  ifstream MyFile(file);
  if(!MyFile.is_open()) {
    cout << "<><> Error Opening File <><> \n";
  }

  int i =0;
  while(getline(MyFile, line)) {
    istringstream iss(line);
    string var1;
    int var2, var3, var4, var5, var6;
    double var7, var8;

    iss >> var1 >> var2 >> var3 >> var4 >> var5 >> var6 >> var7 >> var8;

    houses[i].style = var1;
    houses[i].Num_Of_Bedrooms = var2;
    houses[i].Num_Of_Bathrooms = var3;
    houses[i].Num_Of_Cars_Garage = var4;
    houses[i].Year_Built = var5;
    houses[i].Finished_Square_Footage = var6;
    houses[i].Price = var7;
    houses[i].Tax = var8;

    i++;

    if(arrayZise == i) {break;}
  }
}

void HouseInfo::searchByPriceLinear(HouseInfo *houses, int arraySize, string file, double target) {
  bool found = false;
  double tolerance = 10000;     //e.g. +- 5,000

  for (int i = 0; i < arraySize; ++i) {
    if (std::abs(houses[i].getPrice() - target) <= tolerance) {
        houses[i].print();
        found = true;
    }

  }
  if (!found) {
    cout << "No house found with price <> " << target << " <>\n";
  }

}

void HouseInfo::searchByPriceBinary(HouseInfo *houses, int arraySize, double target) {
  sortByPrice(houses, arraySize);
  int low = 0, high = arraySize - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (houses[mid].getPrice() == target) {
      return houses[mid].print();
    }
    if (houses[mid].getPrice() < target) {
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
}

void HouseInfo::sortByPrice(HouseInfo *houses, int arraySize) {
  bool swapped;
  for (int i = 0; i < arraySize - 1; i++) {
    swapped = false;
    for (int j = 0; j < arraySize - i - 1; j++) {
      if (houses[j].getPrice() > houses[j + 1].getPrice()) {
        HouseInfo temp = houses[j];
        houses[j] = houses[j + 1];
        houses[j + 1] = temp;
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }                   //Sorts by Price
}

void HouseInfo::sortByTaxBubble(HouseInfo *houses, int arraySize) {
  bool swapped;
  for (int i = 0; i < arraySize - 1; i++) {
    swapped = false;
    for (int j = 0; j < arraySize - i - 1; j++) {
      if (houses[j].getTax() > houses[j + 1].getTax()) {
        HouseInfo temp = houses[j];
        houses[j] = houses[j + 1];
        houses[j + 1] = temp;
        swapped = true;
      }
    }
    if (!swapped) {
      break;
    }
  }               //Sorts Houses by Bubble Sort
}

void HouseInfo::sortByTaxInsertion(HouseInfo *houses, int arraySize) {
  int i = 0, j = 0;
  HouseInfo temp;           //temp variable used for swap

  for (i = 1; i < arraySize; ++i) {
    j = i;
    while (j > 0 && houses[j].getTax() < houses[j - 1].getTax()) {
      temp = houses[j];
      houses[j] = houses[j - 1];
      houses[j - 1] = temp;
      --j;

    }

  }           // Sorts Houses By Insertion Sort
}

int main() {
  int choice;
  const int SIZE = 7;
  HouseInfo Houses[SIZE];

  HouseInfo::loadHouse(Houses, SIZE, "HouseInfo.txt");    //Loads all houses once


  cout << "<><> What would you like to do <><>\n\n";
  cout << "1. Print all available houses\n";
  cout << "2. Search for a house by PRICE using LINEAR\n";
  cout << "3. Search for a house by PRICE using BINARY\n";
  cout << "4. Print sorted houses by TAX using BUBBLE sort\n";
  cout << "5. Print sorted houses by TAX using INSERTION sort\n";
  cout << "Enter Choice: ";
  cin >> choice;

  switch (choice) {
  case 1:
    cout << left << setw(15) << "House Style" << setw(10) << "Bed Rms" << setw(10) << "Bath Rms" << setw(10) << "Garage"<< setw(10) << "Year" << setw(10) << "Area" << setw(10) << "Price" << setw(10) << "Tax Paid" << endl;
    for (int i = 0; i < SIZE; i++) {
      Houses[i].print();
    }
    break;
  case 2:
    double userPrice;
    cout << "Enter the price you want to search for: ";
    cin >> userPrice;
    HouseInfo::searchByPriceLinear(Houses, SIZE, "HouseInfo.txt", userPrice);
    break;
  case 3:
    cout << "Enter the price you want to search for: ";
    cin >> userPrice;
    HouseInfo::searchByPriceBinary(Houses, SIZE, userPrice);
    break;
  case 4:
    HouseInfo::sortByTaxBubble(Houses, SIZE);
    cout << left << setw(15) << "House Style" << setw(10) << "Bed Rms" << setw(10) << "Bath Rms" << setw(10) << "Garage"<< setw(10) << "Year" << setw(10) << "Area" << setw(10) << "Price" << setw(10) << "Tax Paid" << endl;
    for (int i = 0; i < SIZE; i++) {
      Houses[i].print();
    }
    break;
  case 5:
    HouseInfo::sortByTaxInsertion(Houses, SIZE);
    cout << left << setw(15) << "House Style" << setw(10) << "Bed Rms" << setw(10) << "Bath Rms" << setw(10) << "Garage"<< setw(10) << "Year" << setw(10) << "Area" << setw(10) << "Price" << setw(10) << "Tax Paid" << endl;
    for (int i = 0; i < SIZE; i++) {
      Houses[i].print();
    }
    break;
  default:
    cout << "Not a valid choice." << endl;
  }



  return 0;

}
