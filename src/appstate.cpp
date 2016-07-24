#include "appstate.h"
#include "env.h"

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Exception.h"
#include "SQLiteCpp/Statement.h"

#include <iostream>
#include <cassert>

#include "locations.h"


AppState::AppState() :dbPath_(Env::DbPath)
{
  assert (dbPath_.size() > 0);
  try
  {
    SQLite::Database db(dbPath_, SQLite::OPEN_READONLY); 

    SQLite::Statement query(db, "SELECT json_extract(data, '$.initialized') FROM appstates WHERE json_extract(data, '$.initialized') is not null;");

    if (query.executeStep())
    {
      int boolInt = query.getColumn(0);
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
  return intiazlized_;
}

void AppState::initDb()
{
  assert (dbPath_.size() > 0);
  try
  {
    SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
  
    db.exec ("CREATE TABLE IF NOT EXISTS appstates (data TEXT);"); 

    // Try to fetch the locations data 
    Locations locations;
    if (locations.fetchLocations() <= 0)
    {
      return;
    }

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

