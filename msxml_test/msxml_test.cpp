// msxml_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#pragma warning(disable:4189)
#include <fmt/core.h>
#pragma warning(default:4189)

int main(int argc, const char* argv[]) {
	if (argc > 0) {
		fmt::print("Hello from {}\n", argv[0]);
	}
	return 0;
}
