// Reverse polish notation calculator
// Usage: rpncalc <expression>
// Example: rpncalc "2 3 + 4 *"
// Output: 20
// Example: rpncalc "2 3 4 + *"
// Output: 14
//
// Author: Michael John
// Email: michael @ aka.ninja

#include <utility>
#include <string>

#include <fmt/core.h>
#include "rpn.hxx"

int main(int argc, char** argv) {
	// Check if the expression is provided
	if (argc != 2) {
		fmt::print(stderr, "Usage: {} <expression>\n", argv[0]);
		exit(1);
	}

	// Evaluate the expression
	std::pair<double, std::string> result = evalRPN(argv[1]);
	if (!result.second.empty()) {
		fmt::print(stderr, "Error: {}\n", result.second);
		exit(1);
	}
	fmt::print("{}\n", result.first);
	return 0;
}
