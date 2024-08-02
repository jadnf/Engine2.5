#include "EAssert.h"
#include <iostream>

void CustomAssert(const std::string& expression, const std::string& filename, int line) {
	std::cerr << "Assertion Failed: (" << expression << "), file: " << filename << ", Line: " << line << std::endl;
	std::abort();
}