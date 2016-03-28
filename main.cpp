//Authors: Sebastian Grobelny Nicki Padar

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <climits>
#include <fstream>

#include "list.h"
#include "airport.h"
#include "plane.h"
#include "city.h"

using namespace std;

void calcAirportTraffic(const List<Airport> &cities, int index);
void calcDistance(const List<Airport> &cities, int index1, int index2, 
                  int *distance, int *passengers, bool display);
void cleanCities(List<Airport> &cities);
int findAirport(const List<Airport> &cities, const char *airport);
void readAirports(List<Airport> &cities);
void readCities(List<Airport> &cities);
void readPlanes(List<Plane> &planes);
void displayPlaneInformation(const List<Plane> &planes);
void addPlaneInformation(List<Plane> &planes);
void determineBestPlane(const List<Plane> &planes); 
void readAirlines(List<Airport> &cities);
void determineRoute(const List<Airport> &cities);

void determineRoute(const List<Airport> &cities)
{
  int b;
  char input[1000];
  List<Flight> local;
  cout << "\nPlease enter origin destination and an airline: ";
  cin.get(input, 1000);
  b = findRoute(cities, local, input);

  if (b == 1)
  {
    cout << local;
    cout << "\n";
  } //if

  else //else
  {
    cout << "No route found.";
    cout << "\n";
  } //else
} //determineRoute

void addPlaneInformation(List<Plane> &planes)
{
  Plane local;
  local.getPlane();
  ofstream outf("planes.dat", ios::app | ios::binary);
  outf.write((char*) &local, sizeof(Plane));
  planes += local;
  outf.close();
}  // addPlaneInformation()


void calcDistance(const List<Airport> &cities)
{
  char airport1[80], airport2[80];
  int index1, index2, distance, passengers;
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> airport1 >> airport2;
  index1 = findAirport(cities, airport1);
  index2 = findAirport(cities, airport2);

  if (index1 >= 0 && index2 >= 0)
    calcDistance(cities, index1, index2, &distance, &passengers, true);
}  // calcDistance())


void determineAirportTraffic(const List<Airport> &cities)
{
  char airport[80];
  int index;
  cout << "\nPlease enter an airport abbreviation (XXX): ";
  cin >> airport;
  index = findAirport(cities, airport);

  if (index >= 0 && index >= 0)
    calcAirportTraffic(cities, index);
}  // determinAirportTraffic()


void determineBestPlane(const List<Airport> &cities, const List<Plane> &planes)
{
  char airport1[80], airport2[80];
  int index1, index2, distance, passengers, minIndex = -1, minCost = INT_MAX, 
    minTrips, trips, cost;
  cout << "\nPlease enter two airport abbreviations (XXX XXX): ";
  cin >> airport1 >> airport2;
  index1 = findAirport(cities, airport1);
  index2 = findAirport(cities, airport2);

  if (index1 >= 0 && index2 >= 0)
  {
    calcDistance(cities, index1, index2, &distance, &passengers, false);
      
    for (int i = 0; i < planes.getCount(); i++)
    {
       cost = planes[i].calcCost(distance, passengers, &trips);
       
       if (trips > 0 && cost < minCost)
       {
         minTrips = trips;
         minCost = cost;
         minIndex = i;
       }  // if lower cost
    }  // for each plane
    
    if (minIndex == -1)
      cout << "No planes available\n";
    else // else found a plane
    {
      cout << "Passengers Miles  Trips Name      Cost\n";
      cout << left << setw(11) << passengers << setw(7) << distance << setw(6) 
        << minTrips << setw(10) << planes[minIndex].getName() << '$' << minCost 
        << endl;
    } // else found a plane
  }   // if valid inputs  
}  //  determineBestPlane()


void displayPlaneInformation(const List<Plane> &planes)
{
  cout << "\nPlane Information\n";
  cout << "Name        Pass. Range Speed Fuel   MPG   $/mi  Price * 10^6\n";
  
  for (int i = 1; i < planes.getCount(); i++)
    cout << planes[i];
  cout << planes[0];

}  // displayPlaneInformation()


int getChoice()
{
  int choice;

  do
  {
    cout << "\nFlight Simulator Menu\n";
    cout << "0. Done.\n";
    cout << "1. Determine distance and passengers between two airports.\n";
    cout << "2. Determine all traffic from one airport.\n";
    cout << "3. Display planes information.\n";
    cout << "4. Add plane information.\n";
    cout << "5. Determine best plane between two airports.\n";
    cout << "6. Show airline flights.\n";
    cout << "7. Determine route between two airports.\n\n";

    cout << "Your choice (0 - 7): ";
    cin >> choice;
    cin.ignore(1000, '\n');
   
    if  (choice < 0 || choice > 7)
      cout << "Your choice must be between 0 and 5. Please try again.\n";
  } while(choice < 0 || choice > 7);
   
  return choice;
}  // getChoice()  


void readPlanes(List<Plane> &planes)
{
  Plane local;
  ifstream inf("planes.dat", ios::binary);

  if (! inf)
    return;

  while (inf.read((char*) &local, sizeof(Plane)))
  {
    planes += local;
  } //while

  inf.close();
} // readPlane()



void run(const List<Airport> &cities, List<Plane> &planes)
{
  int choice;

  do
  {
    choice = getChoice();
    
    switch(choice)
    {
      case 1 : calcDistance(cities); break;
      case 2 : determineAirportTraffic(cities); break;
      case 3 : displayPlaneInformation(planes); break;
      case 4 : addPlaneInformation(planes); break;
      case 5 : determineBestPlane(cities, planes); break;
      case 6 : cout << cities; break;
      case 7 : determineRoute(cities); break;
    }  // switch
  } while(choice != 0);
}  // run())

void calcAirportTraffic(const List<Airport> &cities, int index)
{
  int total = 0;
  
  for (int i = 0; i < cities.getCount(); i++)
    if (i != index)
      total += cities[index].showTraffic(cities[i]);
  
  cout << "Total passengers: " << total << endl;
}  // calcAirportTraffic()


void calcDistance(const List<Airport> &cities, int index1, int index2, 
                  int *distance, int *passengers, bool display)
{
  cities[index1].calcDistance( &cities[index2], distance, passengers,
    display);
}  // calcDistance()

void cleanCities(List<Airport> &cities)
{
  int i = 0;
  
  while (i < cities.getCount())
  {
    if (!cities[i].hasAirport())
      cities -= cities[i];
    else // city has an airport
      i++;
  }  // while more in array
}  // cleanCities())


int findAirport(const List<Airport> &cities, const char *airport)
{
  Airport city;
  
  city.setAirport(airport);
  
  for (int i = 0; i < cities.getCount(); i++)
    if (cities[i] == city)
      return i;
  
  cout << airport << " is not a valid airport.\n";
  return -1;
}  // findAirport()


void readAirports(List<Airport> &cities)
{
  char line[1000], state2[80];
  Airport city;
  ifstream inf("airportLL.txt");

  while (inf.getline(line, 1000))
  {
    if (isalpha(line[0]))
      strcpy(state2, strtok(line, "\n"));
    
    if (line[0] == '[')
    {
      city.readAirport(line, state2);
      
      for (int i = 0; i < cities.getCount(); i++)
        if (cities[i] == city)
        {
          cities[i].copyLocation(&city);
          break;
        }  // if found a matching name
      
      city.deallocate();
    }  // if an airport line
  }  // while
}  // readAirports()


void readCities(List<Airport> &cities)
{
  ifstream inf("citypopulations.csv");
  Airport city;
  
  while(!inf.eof())
  {
    inf >> city;
    cities += city;
  } // while more in file
  
  inf.close();
}  // readCities()

void readAirlines(List<Airport> &cities) 
{
  int flightnum, k, s = 0;
  char line[1000], *ptr, *temp;

  ifstream inf("airlines-1.txt");

  for (int i = 0; !inf.eof(); i++)
  { 
    inf.getline(line, 1000);

    for (int a = 0; i > 8; a++) 
    {
      inf.getline(line, 1000);
      ptr = strtok(line, " ");
      flightnum = atoi(strtok(NULL, " "));
      temp = strtok(NULL, "\n");

      for (int c = 0; c < cities.getCount(); c++)
      {
          k = airportCompare(cities[c], ptr); //compare airport and origin

          if (k == 0) //if airport and origin same
          { 
            s++;
            readFlight(flightnum, temp, cities[c]); //store flight info 
            break;
          } //if
      } //for

      if (s == cities.getCount() - 1)
        i = 0;
    } //for
  } //for
} //readAirlines

int main(int argc, char** argv) 
{
  List<Airport> cities;
  List<Plane> planes;
  readCities(cities);
  readAirports(cities);
  cleanCities(cities);
  readPlanes(planes);
  readAirlines(cities);
  run(cities, planes);
  return 0;
} // main())

