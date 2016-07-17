#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test the setup", "[setup]"){
  REQUIRE( 1+2 == 3);
}
