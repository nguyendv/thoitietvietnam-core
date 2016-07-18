#include "appstate.h"
#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Exception.h"
#include "SQLiteCpp/Statement.h"

#include <iostream>

AppState::AppState(const char* dbPath) :dbPath_(dbPath)
{
  // TODO: find the 'initialized' value in the AppStates table
  try
  {
    SQLite::Database db(dbPath_, SQLite::OPEN_READONLY); 

    SQLite::Statement query(db, "SELECT json_extract(data, '$.initialized') FROM appstates WHERE json_extract(data, '$.initialized') is not null;");

    if (query.executeStep())
    {
      int boolInt = query.getColumn(0);
      std::cout << "OOOOOOOOOOOOO   " << boolInt << '\n';
      intiazlized_ = (boolInt != 0);
    }
  }
  catch (SQLite::Exception& e)
  {
    intiazlized_ = false;
  }

}

bool AppState::initialized()
{
      std::cout << "OOOOOOOOOOOOO   " << intiazlized_ << '\n';
  return intiazlized_;
}

void AppState::initDb()
{
  try
  {
    SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
  
    db.exec ("CREATE TABLE IF NOT EXISTS appstates (data TEXT);"); 

    // TODO: download data the first time if necessary
   
    // Init the 'initialized' state to 'true' 
    SQLite::Statement query(db, "INSERT INTO appstates VALUES (json('{\"initialized\": 1}'));");

    query.exec();


    intiazlized_ = true;
  }
  catch (SQLite::Exception& e)
  {
    printf("%s\n", e.what());
  }
}


