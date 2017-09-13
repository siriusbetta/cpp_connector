#define CATCH_CONFIG_MAIN
#include <../include/Catch/include/catch.hpp>

unsigned int Factorial( unsigned int number)
{
	return number <= 1 ? number : Factorial(number - 1) * number;
}


TEST_CASE( "Factorial are computed", "[factorial]")
{

	REQUIRE( Factorial(1) == 1 );
	REQUIRE( Factorial(2) == 2 );
	REQUIRE( Factorial(3) == 6 );
	REQUIRE( Factorial(10) == 3628800);

}
