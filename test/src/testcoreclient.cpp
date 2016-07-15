#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "coreclient.h"

TEST_CASE("Test the setup", "[setup]"){
  REQUIRE( add(1,2) == 3);
}
