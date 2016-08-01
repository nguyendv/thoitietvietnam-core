#include "weather.h"
#include "env.h"
#include "httpclient/client.h"

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"

#include "json.hpp"

#include <cassert>

#include <iostream>

using json = nlohmann::json;

Weather::Weather()
  : server_(Env::Server),
    dbPath_(Env::DbPath)
{
  assert (dbPath_.size() > 0);

  SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  
  db.exec("CREATE TABLE IF NOT EXISTS weather (location TEXT, data TEXT);");
}

void Weather::fetchData(const string& location)
{
  http::Client client(server_);

  http::Response res = client.get("/api/weather/" + location);

  string data = res.body();

  updateDb(location, data);
}

void Weather::updateDb(const string& location, const string& data)
{
  SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE);

  SQLite::Statement selectQuery(db, "SELECT data FROM weather WHERE location= ?;");

  selectQuery.bind(1, location);

  if (selectQuery.executeStep() )
  {
    db.exec("DELETE FROM weather WHERE location= \"" + location+ "\"" );
  }
  
  SQLite::Statement insertQuery(db, "INSERT INTO weather VALUES(?, ?);");

  insertQuery.bind(1, location);
  insertQuery.bind(2, data);

  insertQuery.exec();
}

string Weather::getCurerntCondition(const string& location)
{
  SQLite::Database db(dbPath_, SQLite::OPEN_READONLY);

  SQLite::Statement selectQuery(db, "SELECT data FROM weather WHERE location= ?;");

  selectQuery.bind(1, location);

  if (selectQuery.executeStep())
  {
    string data = selectQuery.getColumn(0);
    json jsondata = json::parse(data); 
    return jsondata["weather"].get<string>();
  }

  return "";
}
