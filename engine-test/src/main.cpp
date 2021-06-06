#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "engine.h"

using namespace engine;
using namespace std;

int main(int argc, char* argv[])
{
	// My code here

	// catch code
	int result = Catch::Session().run(argc, argv);

	// stop program
	cin.get();

	return (result < 0xff ? result : 0xff);
}
