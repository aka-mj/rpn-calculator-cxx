#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "rpn.hxx"

TEST_CASE("Test eval", "[eval]") {
	SECTION("Test evalRPN") {
		SECTION("Happy path") {
			auto result = evalRPN("1 2 +");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(3.0, 1e-6));
			REQUIRE(result.second == "");

			result = evalRPN("1 2 -");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(-1.0, 1e-6));
			REQUIRE(result.second == "");

			result = evalRPN("1 2 *");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(2.0, 1e-6));
			REQUIRE(result.second == "");

			result = evalRPN("1 2 /");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(0.5, 1e-6));
			REQUIRE(result.second == "");

			result = evalRPN("1 2 + 3 *");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(9.0, 1e-6));
			REQUIRE(result.second == "");

			result = evalRPN("1 2 + 3 /");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(1.0, 1e-6));
			REQUIRE(result.second == "");

			result = evalRPN("1 2 + 3 4 + *");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(21.0, 1e-6));
			REQUIRE(result.second == "");

			result = evalRPN("1 2 + 3 4 + /");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(0.428571, 1e-6));
			REQUIRE(result.second == "");
		}

		SECTION("Error cases") {
			auto result = evalRPN("1");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(1.0, 1e-6));
			REQUIRE(result.second == "");

			result = evalRPN("1 +");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(0.0, 1e-6));
			REQUIRE(result.second == "not enough values for the operation +");

			result = evalRPN("1 2");
			REQUIRE_THAT(result.first, Catch::Matchers::WithinAbs(0.0, 1e-6));
			REQUIRE(result.second == "Invalid expression");
		}
	}
}
