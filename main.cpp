#include "logger.hpp"

int
main() {
	// Create Logger instance 
	// with iostream 
	as::Logger lg(std::cout);

	// Log somenthing
	lg.log(lg.timer.time(), "Hello", 23, "World", 67.8976f, 2, "beep beep");

	return 0;
}