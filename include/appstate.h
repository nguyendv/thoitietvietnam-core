#pragma once

#include <string>
using namespace std;

class AppState
{
public:
  AppState();

  bool initialized();

  /*
   * Init the database
   * Called ONLY ONCE in the lifetime
   */
  void initDb();
private:

  bool intiazlized_;
  string dbPath_;
};
