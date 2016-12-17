# Logger

A simple C++ logger, originally developed for the [aci-comm](https://github.com/UniTN-Mechatronics/aci-comm) project.
Require at least C++11. Tested on MacOS, OSX, Linux.

This version of Logger is NOT threadsafe.

## Usage
```C++
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
```

## Compile example
```bash
g++ -std=c++11 main.cpp -o log
```
