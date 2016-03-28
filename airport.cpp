//Authors: Sebastian Grobelny Nicki Padar
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include "city.h"
#include "airport.h"
#include "list.h"

using namespace std;

Airport::Airport()
{
} //Airport()

Airport::~Airport()
{
} //~Airport()

Flight::Flight()  
{
} //Flight()

Flight::~Flight()
{
} //~Flight()

void readFlight(const int flightcount, char *temp, Airport &rhs)
{
   char *ptr, *ptr2;
   Flight local;

   for (int i = flightcount ; i != 0; i--)
   {
     ptr = strtok(temp, " ");
     local.airlinename = new char[strlen(ptr) + 1];
     strcpy(local.airlinename, ptr);
     ptr2 = strtok(NULL, " ");
     strcpy(local.destination, ptr2);
     local.flightnumber = i;
     rhs.flights += local;
     temp = strtok(NULL, "\n");
   } //for  
} //readFlight

int airportCompare(Airport &rhs, const char *ptr)
{
  return strcmp(rhs.airport, ptr);
} //airportCompare()

int constAirportCompare( const Airport &rhs, char *ptr)
{
 int a;
 a = strcmp(rhs.airport, ptr);
 return a;
} //const AirportCompare

bool Flight::operator< (const Flight& rhs)
{
  return (flightnumber < rhs.flightnumber) == 1;
} //operator<

bool Airport::operator< (const Airport &rhs)
{
  return (population < rhs.population) == 1;
} //operator<

ostream& operator << (ostream& os, const Airport& rhs)
{
  os << rhs.airport << ":" << " " << rhs.flights << endl;
  return os;
} //operator<<

ostream& operator << (ostream& os, const Flight& rhs)
{
  os << rhs.airlinename[0] << rhs.airlinename[1]; 
  os << "-" << rhs.destination << " ";
  return os;
} //operator<<

int findRoute( const List<Airport> &cities, List<Flight> &local, char* input)
{
 const char* error = "Error.";
 char *ptr, *dest, *air;
 int flightcount = 0;
 ptr = strtok(input, " ");
 dest = strtok(NULL, " ");
 air = strtok(NULL, "\n");
 Flight variable, variable2;

 for (int a = 0; a < cities.getCount(); a++)
 {

  if (strcmp(cities[a].airport, ptr) == 0)
  {
   strcpy(variable.destination , cities[a].airport);
   variable.airlinename = new char(strlen(air));
   strcpy(variable.airlinename, air);
   variable.flightnumber = flightcount;
   flightcount++; local += variable;
   strcpy(ptr, findAirline(cities[a].flights, air));
   a = -1;

  if (strcmp(ptr, dest) == 0)
  {
    strcpy(variable.destination, ptr);
    strcpy(variable.airlinename, air);
    variable.flightnumber = flightcount;
    local += variable; return 1;
  } //if

  if (strcmp(error, ptr) == 0) return 0;
  } //if
  } //for
  return 0;
} //findRoute

const char* findAirline(const List<Flight> &flights, char* air)
{
 const char* error = "Error";
 int k;

 for (int i = flights.getCount() - 1; i > -1; i--)
 {
  k = strncmp(flights[i].airlinename, air, strlen(air) - 1);

  if (k == 0)
    return flights[i].destination;   
 } //for

  return error;
} //findAirline

int airlineCompare(const Flight &rhs, char* air)
{
  int b;
  b = strcmp(rhs.airlinename, air);
  return b;
} //airlineCompare
