# pragma once
#include <string>
using namespace std;

struct Location{
  int Id;
  string Name;
};

const string LOCATION_DATA = ""; // TODO: write me

namespace locations{
  Location current();

  class Persistent{
    public:
      static Persistent* getInstance();
    private:
      Persistent();
      void init();
      static Persistent* instance_;
  };
};
