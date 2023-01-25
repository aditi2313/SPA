
#include "TNode.h"
#include <exception>

#include "catch.hpp"
using namespace std;
void require(bool b) {
    REQUIRE(b);
}

TEST_CASE("1st Test") {

    TNode T;
	
	
	throw new std::exception();
    require(1 == 1);
}


