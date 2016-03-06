#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/light_matrix.hpp"
#include "../src/colored_light_matrix.hpp"

TEST_CASE("light matrix emits correctly", "[light matrix]")
{
    LightMatrix lm(40, 40);

    lm.emitLight(20, 20, 99);
    REQUIRE(lm.brightness(20, 20) == 99);
    lm.emitLight(20, 20, 150);
    REQUIRE(lm.brightness(20, 20) == 150);
    lm.emitLight(20, 20, 0);
    REQUIRE(lm.brightness(20, 20) == 0);
}

TEST_CASE("colored light matrix emits correctly", "[light matrix]")
{
    ColoredLightMatrix lm(40, 40);

    lm.emitLight(20, 20, 99, Color::kRed);
    REQUIRE(lm.brightness(20, 20, Color::kRed) == 99);
    REQUIRE(lm.brightness(20, 20, Color::kGreen) == 0);
    REQUIRE(lm.brightness(20, 20, Color::kBlue) == 0);
    lm.emitLight(20, 20, 150, Color::kRed);
    REQUIRE(lm.brightness(20, 20, Color::kRed) == 150);
    lm.emitLight(20, 20, 0, Color::kRed);
    REQUIRE(lm.brightness(20, 20, Color::kRed) == 0);
}
