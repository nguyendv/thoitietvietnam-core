#include "locations.h"
#include "env.h"

#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Exception.h"
#include "SQLiteCpp/Statement.h"

#include <cassert>

Locations::Locations() : dbPath_(Env::DbPath), version_(0)
{
  assert (dbPath_.size() > 0 );
  try
  {
    SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);
    
    db.exec("CREATE TABLE IF NOT EXISTS locations (data TEXT);");
  }
  catch (SQLite::Exception& ex)
  {
    printf("%s\n", ex.what());
  }
}

bool Locations::fetchLocations()
{
  assert (dbPath_.size() > 0);

  bool ret = true;

  try
  {
    SQLite::Database db(dbPath_, SQLite::OPEN_READWRITE);

    SQLite::Statement query(db, "SELECT json_extract(data, '$.version') FROM locations; ");

    if(query.executeStep())
    {
      version_ = query.getColumn(0);
    }

    if (version_ == 0)
    {
      // TODO: use http client to get /locations
    }
    else
    {
      // TODO: use http client to get /locations/version
      // TODO: compare version_ with the newly fetch result
      // TODO: if lesser, use http client to get /locations
    }
  }
  catch (SQLite::Exception& e)
  {
    printf("%s\n", e.what());
    ret = false;
  }

  return ret;
}





