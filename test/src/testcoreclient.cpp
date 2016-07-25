#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "appstate.h"
#include "locations.h"
#include "env.h"

string Env::DbPath = "test.db";
string Env::Server = "127.0.0.1:5000";


TEST_CASE("Test Locations", "[locations]")
{
  Locations locationsService;
  REQUIRE ( 0 == locationsService.getDataVersion());
  locationsService.fetchLocations();

  // 1: the locations data version defined in locationsdata.json
  REQUIRE ( 1 == locationsService.getDataVersion());
}


TEST_CASE("Test location suggestions", "[locations][suggestions]")
{
  Locations locationsService;

  string query1 = "hd";
  string suggestions1 = locationsService.getSuggestions(query1);
  REQUIRE (suggestions1.find("Hải Dương") != string::npos);

  string query2 = "dn";
  string suggestions2 = locationsService.getSuggestions(query2);
  REQUIRE (suggestions2.find("Đồng Nai") != string::npos);

  string query3 = "sa";
  string suggestions3 = locationsService.getSuggestions(query3);
  REQUIRE (suggestions3.find("Sài Gòn") != string::npos);
}


TEST_CASE("Test AppState", "[appstate]"){
  AppState appState;

  REQUIRE ( 0 != appState.getState("city").compare("Ha Noi"));

  appState.setState("city", "Ha Noi");

  REQUIRE ( 0 == appState.getState("city").compare("Ha Noi"));

  appState.setState("city", "Hai Phong");

  REQUIRE ( 0 == appState.getState("city").compare("Hai Phong"));
}
