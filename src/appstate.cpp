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
  
    db.exec ("CREATE TABLE IF NOT EXISTS appstates (key TEXT, value TEXT);"); 
  }
  catch (SQLite::Exception& e)
  {
    printf("%s\n", e.what());
  }
}

void AppState::setState(const string& key, const string& value)
{
  SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE);

  SQLite::Statement selectQuery(db, "SELECT value FROM appstates WHERE key = ?;");

  selectQuery.bind(1, key);

  if (selectQuery.executeStep() )
  {
    db.exec("DELETE FROM appstates WHERE key = \"" + key + "\"" );
  }
  
  SQLite::Statement insertQuery(db, "INSERT INTO appstates VALUES(?, ?);");

  insertQuery.bind(1, key);
  insertQuery.bind(2, value);

  insertQuery.exec();
}

string AppState::getState(const string& key)
{
  SQLite::Database db(dbPath_, SQLite::OPEN_READONLY);

  SQLite::Statement selectQuery(db, "SELECT value FROM appstates WHERE key = ?;");

  selectQuery.bind(1, key);

  if (selectQuery.executeStep())
  {
    return selectQuery.getColumn(0);
  }

  assert(false); // Should not go to here!
  return ""; // Should not go to here!
}

