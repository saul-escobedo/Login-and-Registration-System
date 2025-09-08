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


  public:
    HouseInfo( string style = "", int Num_Of_Bedrooms = 0, int Num_Of_Bathrooms = 0, int Num_Of_Cars_Garage = 0, int Year_Built= 0, int Finished_Square_Footage = 0, double Price = 0.0, double Tax = 0.0);
    //setters and getrer
    void print() {
      cout << left << setw(15) << style << setw(10) << Num_Of_Bedrooms << setw(10) << Num_Of_Bathrooms << setw(10) << Num_Of_Cars_Garage << setw(10) << Year_Built << setw(10) << Finished_Square_Footage << setw(10) << Price << setw(10) << Tax << endl;
    }
    void ReadFile();
    void static loadHouse(HouseInfo houses[], int arrayZise, string file);

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

HouseInfo::HouseInfo(string style, int Num_Of_Bedrooms, int Num_Of_Bathrooms, int Num_Of_Cars_Garage, int Year_Built, int Finished_Square_Footage, double Price, double Tax)
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

void HouseInfo::ReadFile() {
  string line;

  ifstream MyFile("HouseInfo.txt",ios::out);
  if(!MyFile.is_open()) {
    cout << "<><> Error Opening File <><> \n";
  }

  while(getline(MyFile, line)) {
    istringstream iss(line);
    string var1;
    int var2, var3, var4, var5, var6;
    double var7, var8;

    iss >> var1 >> var2 >> var3 >> var4 >> var5 >> var6 >> var7 >> var8;
  }

}

void HouseInfo::loadHouse(HouseInfo *houses, int arrayZise, string file) {
  string line;

  ifstream MyFile(file, ios::out);
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
    houses[i].print();

    i++;

    if(arrayZise == i) {break;}
  }
}

int main() {
  HouseInfo Houses[7];

  cout << left << setw(15) << "House Style" << setw(10) << "Bed Rms" << setw(10) << "Bath Rms" << setw(10) << "Garage"<< setw(10) << "Year" << setw(10) << "Area" << setw(10) << "Price" << setw(10) << "Tax Paid" << endl;
  HouseInfo::loadHouse(Houses, 7, "HouseInfo.txt");

  return 0;

}
