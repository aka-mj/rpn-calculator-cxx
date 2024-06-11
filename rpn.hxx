#ifndef RPN_HXX
#define RPN_HXX

#include <utility>
#include <string>
#include <stack>
#include <sstream>
#include <stdexcept>

#include <fmt/core.h>

auto performOperation(double a, double b, const std::string& op) -> double {
	if (op == "+") {
		return a + b;
	} else if (op == "-") {
		return a - b;
	} else if (op == "*") {
		return a * b;
	} else if (op == "/") {
		if (b == 0) {
			fmt::print(stderr, "Error: Division by zero\n");
			exit(1);
		}
		return a / b;
	}
	return 0;
}

// Evaluate the expression in reverse polish notation
// Returns a pair of double and string
// The double is the result of the expression
// The string is an error message if any
auto evalRPN(const std::string& expression) -> std::pair<double, std::string> {
	std::stack<double> stack;
	std::istringstream iss(expression);
	std::string token;
	while (iss >> token) {
		if (token == "+" || token == "-" || token == "*" || token == "/") {
			if (stack.size() < 2) {
				return {0, "not enough values for the operation " + token};
			}

			auto b = stack.top();
			stack.pop();
			auto a = stack.top();
			stack.pop();

			stack.push(performOperation(a, b, token));
			continue;
		} else {
			// convert token to float and push to stack
			try {
				stack.push(std::stod(token));
			} catch (const std::invalid_argument& e) {
				return {0, "Invalid token: " + token};
			} catch (const std::out_of_range& e) {
				return {0, "Number out of range"};
			} catch (const std::exception& e) {
				return {0, "unable to handle token: " + token};
			}
		}
	}

	if (stack.size() != 1) {
		return {0, "Invalid expression"};
	}
	return {stack.top(), ""};
}

#endif // RPN_HXX

