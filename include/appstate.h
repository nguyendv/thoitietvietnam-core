#pragma once

#include <string>
using namespace std;

class AppState
{
public:
  AppState(const char* dbPath);

  bool initialized();

  /*
   * Init the database
   */
  void initDb();
private:

  bool intiazlized_;
  const char* dbPath_;
};
