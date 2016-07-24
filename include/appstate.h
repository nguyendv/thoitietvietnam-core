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
private:
  string dbPath_;
};
