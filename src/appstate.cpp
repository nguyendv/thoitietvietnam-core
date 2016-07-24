#include "appstate.h"
#include "env.h"

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Exception.h"
#include "SQLiteCpp/Statement.h"

#include <iostream>
#include <cassert>



AppState::AppState() :dbPath_(Env::DbPath)
{
  initDb();
}

void AppState::initDb()
{
  assert (dbPath_.size() > 0);
  try
  {
    SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
  
    db.exec ("CREATE TABLE IF NOT EXISTS appstates (data TEXT);"); 
  }
  catch (SQLite::Exception& e)
  {
    printf("%s\n", e.what());
  }
}

