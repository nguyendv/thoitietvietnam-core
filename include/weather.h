#pragma once

#include <string>
using namespace std;

class Weather 
{
public: 
  Weather();
  void fetchData(const string& location);
  string condition(const string& location);
  string temperature(const string& location);

private:
  string server_;
  string dbPath_;

  void updateDb(const string& location, const string& data);
};
