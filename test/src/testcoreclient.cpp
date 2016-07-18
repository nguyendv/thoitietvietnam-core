#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "appstate.h"

TEST_CASE("Test AppState", "[appstate]"){
  AppState appState("test.db");
  REQUIRE( !appState.initialized());

  appState.initDb();
  REQUIRE( appState.initialized());
}
