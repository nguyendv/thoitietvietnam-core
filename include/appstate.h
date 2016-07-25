#pragma once

#include <string>
using namespace std;

class AppState
{
public:
  AppState();

  /*
   * Init the database
   */
  void initDb();

  void setState(const string& key, const string& value);

  string getState(const string& key);
private:
  string dbPath_;
};
