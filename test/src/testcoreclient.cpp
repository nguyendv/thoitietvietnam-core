#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "appstate.h"
#include "env.h"

string Env::DbPath = "test.db";

TEST_CASE("Test AppState", "[appstate]"){
  
  AppState appState;
  REQUIRE( !appState.initialized());

  appState.initDb();
  REQUIRE( appState.initialized());
}
