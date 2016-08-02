#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "appstate.h"
#include "locations.h"
#include "weather.h"
#include "env.h"

string Env::DbPath = "test.db";
string Env::Server = "june15-thoitietvietnam.dvnguyen.com";


TEST_CASE("Test Locations", "[locations]")
{
  Locations locationsService;
  REQUIRE ( 0 == locationsService.getDataVersion());
  locationsService.fetchLocations();

  // 2: the locations data version defined in locationsdata.json
  REQUIRE ( 2 == locationsService.getDataVersion());
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

  REQUIRE ( 0 != appState.getState("CURRENT_LOCATION").compare("Ha Noi"));

  appState.setState("CURRENT_LOCATION", "Ha Noi");

  REQUIRE ( 0 == appState.getState("CURRENT_LOCATION").compare("Ha Noi"));

  appState.setState("CURRENT_LOCATION", "Hải Phòng");

  REQUIRE ( 0 == appState.getState("CURRENT_LOCATION").compare("Hải Phòng"));
}


TEST_CASE("Test Weather api", "[weather]")
{
  AppState appState;
  Weather weather;

  string currentLocation = appState.getState("CURRENT_LOCATION");
  weather.fetchData(currentLocation);

  cout << weather.condition(currentLocation);
  REQUIRE ( weather.condition(currentLocation).size() > 0);

  cout << weather.temperature(currentLocation);
  REQUIRE (weather.temperature(currentLocation).size() > 0);
}
