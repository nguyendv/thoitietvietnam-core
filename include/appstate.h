#pragma once

#include <string>
using namespace std;

int getCurrentLocation();
void setCurrentLocation(int id);
void onCurrentLocationChange(int newId);

struct AppState{
  AppState();

  int currLocationId; // Location state. For example: {id: 1, name: 'Hanoi'}
  void onCurrentLocationChange(int newLocationID);   
};

