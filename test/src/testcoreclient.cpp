#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "appstate.h"
#include "locations.h"
#include "env.h"

string Env::DbPath = "test.db";
string Env::Server = "127.0.0.1:5000";

TEST_CASE("Test AppState", "[appstate]"){
  
  AppState appState;
  REQUIRE( !appState.initialized());

  appState.initDb();
  REQUIRE( appState.initialized());
}

TEST_CASE("Test Locations", "[locations]")
{
  Locations locationsService;

  // 1: the locationsdata.json version
  REQUIRE( 1 == locationsService.fetchLocations());
}
