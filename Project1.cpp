#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//Struct creation for cars
struct CarType {
  enum {MAX_CHAR_LEN=100};
  char CarName[MAX_CHAR_LEN];
  double MPG;
  int Cylinders;
  double Displacement;
  double Horsepower;
  double Weight;
  double Acceleration;
  int Model;
  char Origin[MAX_CHAR_LEN];
  bool ValidEntry;
  CarType();
};

//Default constructor setting everything to 0
CarType::CarType() {
  MPG = 0.0;
  Cylinders = 0;
  Displacement = 0.0;
  Horsepower = 0.0;
  Weight = 0.0;
  Acceleration = 0.0;
  Model = 0;
  ValidEntry = false;
}

//Global const int that is the "max" number of cars that can be stroed
const int MAX_CARS = 500;

//Function reads car.txt into car and returns it
CarType readCarData(ifstream &inFile) {
    CarType car; 
    inFile.get(car.CarName, CarType::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile >> car.MPG;
    inFile.ignore(100,';');
    inFile >> car.Displacement;
    inFile.ignore(100,';');
    inFile >> car.Cylinders;
    inFile.ignore(100,';');
    inFile >> car.Horsepower;
    inFile.ignore(100,';');
    inFile >> car.Weight;
    inFile.ignore(100,';');
    inFile >> car.Acceleration;
    inFile.ignore(100,';');
    inFile >> car.Model;
    inFile.ignore(100,';');
    inFile.get(car.Origin, CarType::MAX_CHAR_LEN, '\n');
    inFile.ignore(100,'\n');
    // If we reached the end of the file while reading, then the entry is not valid
    car.ValidEntry = !inFile.eof();
    return car;
}

//Validates Ints
int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}

//Validates Doubles
double readDouble(const char prompt[]){
    double temp = 0.0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}

//Prints data of specific cars
void printCars(CarType carList, int carNum) {
  if(carList.ValidEntry == true) {
    cout << "Car Number: " << carNum << endl;
    cout << "Name: " << carList.CarName << endl;
    cout << "MPG: " << carList.MPG << endl;
    cout << "Cylinders: " << carList.Cylinders << endl;
    cout << "Displacment: " << carList.Displacement << endl;
    cout << "Horsepower: " << carList.Horsepower << endl;
    cout << "Weight: " << carList.Weight << endl;
    cout << "Acceleration: " << carList.Acceleration << endl;
    cout << "Model: " << carList.Model << endl;
    cout << "Origin: " << carList.Origin << endl;
    cout << endl;
  } 
}

//Prints by origin
void printCarsByOrigin(CarType *carList,char userOrigin[]) {
  for(int i = 0; i < 500; i++) {
    if(strcmp(carList[i].Origin,userOrigin) == 0) {
      printCars(carList[i],i);
    }
  }
}

//Removes cars
void removeCar(CarType *carList) {
  int carNum = 0;
  carNum = readInt("What car would you like to remove?: ");
  cout << endl;
  carList[carNum].ValidEntry = false;
  cout << "Done! Car " << carNum << " has been removed.\n" << endl;
}

//Adds cars
void addCars(CarType *carList) {
  bool isCarAdded = false;
  for(int i = 0; i < 500; i++) {
    int tempInt = 0;
    double tempDouble = 0.0;
    //Looping for adding car data
    if(carList[i].ValidEntry == false) {
      cout << "You are modifiying car #" << i << endl;
      cout << "Name: ";
      cin >> carList[i].CarName;
      tempDouble = readDouble("\nMPG: ");
      carList[i].MPG = tempDouble;
      tempInt = readInt("\nCylinders: ");
      carList[i].Cylinders = tempInt;
      tempDouble = readDouble("\nDisplacement: ");
      carList[i].Displacement = tempDouble;
      tempDouble = readDouble("\nHorsepower: ");
      carList[i].Horsepower = tempDouble;
      tempDouble = readDouble("\nWeight: ");
      carList[i].Weight = tempDouble;
      tempDouble = readDouble("\nAcceleration: ");
      carList[i].Acceleration = tempDouble;
      tempInt = readInt("\nModel: ");
      carList[i].Model = tempInt;
      cout << "\nOrigin: ";
      cin >> carList[i].Origin;
      carList[i].ValidEntry = true;
      isCarAdded = true;

      break;
    }
  }
  if(isCarAdded == false) {
    cout << "Sorry! The array is full already" << endl;
  }
}
//Prints menu and returns selection
int menu() {
  int menuChoice = 0;
  cout << "Welcome to our Car Database!" << endl;
  cout << "Please choose from the following options: (1, 2, etc)" << endl;
  cout << "1) View a Car" << endl;
  cout << "2) View Cars By Origin" << endl;
  cout << "3) Add a Car" << endl;
  cout << "4) Remove a Car" << endl;
  cout << "5) Quit" << endl;
  cout << "Input: ";
  cin >> menuChoice;
  cout << endl;
  //Return user choice 
  return menuChoice;
}


int main() {
  //Delcaring Variables
  ifstream carFile("cars.txt");
  CarType carList[500];
  int menuSelect = 0;
  int carChoice = 0;
  int counter = 0;
  char userOrigin[100];

  //Reading data into carList from the cars.txt file
  while(carFile.peek() != EOF) {
        carList[counter] = readCarData(carFile);
        counter++;
  }  

  menuSelect = menu();
  //Menu prompt and decision "tree"
  while(menuSelect != 5) {
    switch(menuSelect) {
      //Viewing specific cars
      case 1:
        cout << "Car Number? (0-499): ";
        cin >> carChoice;
        cout << endl;
        printCars(carList[carChoice],carChoice);
        break;
      //Viewing all cars by certain Origin
      case 2:
        cout << "What Origin? (Japan,US,Europe): ";
        cin >> userOrigin;
        cout << endl;
        printCarsByOrigin(carList,userOrigin);
        break;
      //Adding a car to the list
      case 3:
        addCars(carList);
        break;
      //Removing car from list
      case 4:
        removeCar(carList);
        break;
      //Quit
      case 5:
        break;
      //Safety
      default :
        cout << "Invalid Selection! Please Try Again" << endl;
        break;
  }
  menuSelect = menu();
}
}