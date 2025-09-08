//TODO: Make setters and Getters

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
      cout << left << setw(10) << style << Num_Of_Bedrooms << Num_Of_Bathrooms << Num_Of_Cars_Garage << Year_Built << Finished_Square_Footage << Price << Tax << endl;
    }
    void ReadFile();

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
    v
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


int main() {
  HouseInfo fv;
  fv.print();

  return 0;

}
