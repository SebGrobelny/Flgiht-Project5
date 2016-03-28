//Authors: Sebastian Grobelny Nicki Padar
#ifndef AIRPORT_H
  #define AIRPORT_H

#include <fstream>
#include <iostream>
#include "city.h"
#include "list.h"

using namespace std;

class Flight;

class Airport: public City
{
public:
  List<Flight> flights;
  Airport();
  ~Airport();
  friend void readFlight(int flightcount, char *temp, Airport &rhs);
  friend int airportCompare(Airport &rhs, const char *ptr);
  friend int constAirportCompare( const Airport &rhs, char *ptr);
  bool operator< (const Airport &rhs);
  friend ostream& operator << (ostream& os, const Airport& rhs);
  friend ostream& operator << (ostream& os, const Flight& rhs);
  friend int findRoute(const List<Airport> &cities, 
                       List<Flight> &local, char* input);
}; //Airport

class Flight
{
  int flightnumber;
  char *airlinename;
  char destination[4];
public:
  Flight();
  ~Flight();
  friend class Airport; 
  bool operator< (const Flight &rhs);
  friend void readFlight(const int flightcount, char *temp, Airport &rhs);
  friend ostream& operator << (ostream& os, const Flight& rhs);
  friend const char* findAirline( const List<Flight> &flights, char* air);
  friend int findRoute(const List<Airport> &cities, 
                       List<Flight> &local, char* input);
  friend int airlineCompare(const Flight &rhs, char* air);

}; //Flight

#endif
