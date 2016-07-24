#include "locations.h"
#include "env.h"

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Exception.h"
#include "SQLiteCpp/Statement.h"

#include "httpclient/client.h"
#include "httpclient/exception.h"

#include <cassert>
#include <cstdlib>

Locations::Locations() 
  : dbPath_(Env::DbPath), 
    server_(Env::Server)
{
  assert (dbPath_.size() > 0 );
  SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    
  db.exec("CREATE TABLE IF NOT EXISTS locations (data TEXT);");
}

void Locations::fetchLocations()
{
  assert (dbPath_.size() > 0);
  assert (server_.size() > 0);

  try
  {
    int localDataVersion = getDataVersion();

    http::Client c(server_);
    int serverDataVersion = atoi(c.get("/api/locations/version")
        .body().c_str());
    if (localDataVersion < serverDataVersion)
      updateLocationTable();
  }
  catch (SQLite::Exception& sqliteEx)
  {
    printf("%s\n", sqliteEx.what());
  }
  catch (const http::Exception httpEx)
  {
    printf("%s\n", httpEx.what());
  }
}

void Locations::updateLocationTable()
{
  SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE);

  http::Client c(server_);
  http::Response res = c.get("/api/locations");

  db.exec("DELETE FROM locations;");

  SQLite::Statement insertQuery(db, "INSERT INTO locations VALUES (?);");
  insertQuery.bind(1, res.body());
  insertQuery.exec();
}

int Locations::getDataVersion()
{
    SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE);

    SQLite::Statement query(db, "SELECT json_extract(data, '$.version') FROM locations; ");

    int ret = 0;

    if(query.executeStep())
    {
      ret = query.getColumn(0);
    }

    return ret;
}
