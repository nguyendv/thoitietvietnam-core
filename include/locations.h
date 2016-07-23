# pragma once
#include <string>
using namespace std;

class Locations
{
  public:
    Locations();
    bool fetchLocations();
  private:

    unsigned int version_;
    string dbPath_;
};

