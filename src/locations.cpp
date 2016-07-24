#include "locations.h"
#include "env.h"

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Exception.h"
#include "SQLiteCpp/Statement.h"

#include "httpclient/client.h"
#include "httpclient/exception.h"

#include <cassert>

Locations::Locations() 
  : dbPath_(Env::DbPath), 
    version_(0),
    server_(Env::Server)
{
  assert (dbPath_.size() > 0 );
  SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    
  db.exec("CREATE TABLE IF NOT EXISTS locations (data TEXT);");

  // TODO: examine to see if it's efficient to fetch location every time
  fetchLocations();
}

int Locations::fetchLocations()
{
  assert (dbPath_.size() > 0);
  assert (server_.size() > 0);

  try
  {
    SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE);

    SQLite::Statement query(db, "SELECT json_extract(data, '$.version') FROM locations; ");

    if(query.executeStep())
    {
      version_ = query.getColumn(0);
    }

    http::Client c(server_);
    int server_data_version = std::stoi(c.get("/api/locations/version").body());
    if (version_ < server_data_version)
      fetchLocationTable();
    version_ = server_data_version;
  }
  catch (SQLite::Exception& sqliteEx)
  {
    printf("%s\n", sqliteEx.what());
  }
  catch (const http::Exception httpEx)
  {
    printf("%s\n", httpEx.what());
  }

  return version_;
}

void Locations::fetchLocationTable()
{
  SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE);

  http::Client c(server_);
  http::Response res = c.get("/api/locations");

  db.exec("DELETE FROM locations;");

  SQLite::Statement insertQuery(db, "INSERT INTO locations VALUES (?);");
  insertQuery.bind(1, res.body());
  insertQuery.exec();
}
