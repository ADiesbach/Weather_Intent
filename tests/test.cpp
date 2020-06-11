#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../findIntent.cpp"

TEST_CASE("Test general weather questions", "[classic]")
{
  REQUIRE(generateResponse("what is the weather today") == "INTENT: Get weather On Day: 11");
  REQUIRE(generateResponse("give me weather tomorrow") == "INTENT: Get weather On Day: 12");
  REQUIRE(generateResponse("tell me weather on the 15") == "INTENT: Get weather On Day: 15");
  REQUIRE(generateResponse("weather in paris") == "INTENT: Get weather On Day: 11 Location: paris");
  REQUIRE(generateResponse("what is the weather in lisbon tomorrow") == "INTENT: Get weather On Day: 12 Location: lisbon");

}


TEST_CASE("Test yes/no weather questions", "[classic]")
{
  REQUIRE(generateResponse("Is it rainy today") == "INTENT: Get [YES/NO] if rainy On Day: 11");
  REQUIRE(generateResponse("Is it sunny in prague today") == "INTENT: Get [YES/NO] if sunny On Day: 11 Location: prague");
  REQUIRE(generateResponse("Will there be a storm in berlin tomorrow") == "INTENT: Get [YES/NO] if storm On Day: 12 Location: berlin");
  REQUIRE(generateResponse("Will there be snow on the 23") == "INTENT: Get [YES/NO] if snow On Day: 23");


}

TEST_CASE("Test fact", "[classic]")
{
  REQUIRE(generateResponse("give me a fact please") == "INTENT: Fact");
}


TEST_CASE("No input", "[classic]")
{
  REQUIRE(generateResponse(" ") == "INTENT: ");
  REQUIRE(generateResponse("flflflflf") == "INTENT: ");
}
